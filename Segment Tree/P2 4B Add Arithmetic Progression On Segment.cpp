#include <bits/stdc++.h>
using namespace std; 
namespace atcoder {

template <class NODE,
          NODE (*operation)(NODE, NODE),
          NODE (*initialization)(),
          class UPDATE,
          NODE (*apply)(UPDATE, NODE),
          UPDATE (*combine)(UPDATE, UPDATE),
          UPDATE (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
    explicit lazy_segtree(int n) : lazy_segtree(vector<NODE>(n, initialization())) {}
    explicit lazy_segtree(const vector<NODE>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = vector<NODE>(2 * size, initialization());
        lz = vector<UPDATE>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, NODE x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    NODE query(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    NODE query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return initialization();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        NODE sml = initialization(), smr = initialization();
        while (l < r) {
            if (l & 1) sml = operation(sml, d[l++]);
            if (r & 1) smr = operation(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return operation(sml, smr);
    }

    NODE all_query() { return d[1]; }

    void rupd(int p, UPDATE f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void rupd(int l, int r, UPDATE f) {
        r++;
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(NODE)> int descent_right(int l) {
        return descent_right(l, [](NODE x) { return g(x); });
    }
    template <class G> int descent_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(initialization()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        NODE sm = initialization();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(operation(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(operation(sm, d[l]))) {
                        sm = operation(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = operation(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(NODE)> int descent_left(int r) {
        r++;
        return descent_left(r, [](NODE x) { return g(x); }) - 1;
    }
    template <class G> int descent_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(initialization()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        NODE sm = initialization();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(operation(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(operation(d[r], sm))) {
                        sm = operation(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = operation(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    vector<NODE> d;
    vector<UPDATE> lz;

    void update(int k) { d[k] = operation(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, UPDATE f) {
        d[k] = apply(f, d[k]);
        if (k < size) lz[k] = combine(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

} using namespace atcoder;
#define int long long int

using NODE = pair<int, int>;
using UPDATE = int;

NODE initialization() { return NODE(0, 0); }
NODE operation(NODE l, NODE r) {
    return NODE(l.first + r.first, l.second + r.second);
}
NODE apply(UPDATE l, NODE r) {
    return NODE(r.first + l * r.second, r.second);
}
UPDATE id() { return UPDATE(0); }
UPDATE combine(UPDATE cur, UPDATE prev) { 
    return cur + prev;
}

using NODE2 = int;
using UPDATE2 = int;

NODE2 initialization2() { return NODE2(0); }
NODE2 operation2(NODE2 l, NODE2 r) {
    return NODE2(l + r);
}
NODE2 apply2(UPDATE2 l, NODE2 r) {
    return NODE2(l + r);
}
UPDATE2 id2() { return UPDATE2(0); }
UPDATE2 combine2(UPDATE2 cur, UPDATE2 prev) { 
    return cur + prev;
}

signed main() {   
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> v(n, pair<int, int>{0, 0});
    for(int i = 0; i < n; i++)
        v[i].second = i + 1;
	lazy_segtree<NODE, operation, initialization, UPDATE, apply, combine, id> st(v);
    lazy_segtree<NODE2, operation2, initialization2, UPDATE2, apply2, combine2, id2> st2(n);
    while(q--) {
        int type, l, r, a, d, node;
        cin >> type;
        if(type == 1) {
            cin >> l >> r >> a >> d;
            st.rupd(l - 1, r - 1, UPDATE(d));
            st2.rupd(l - 1, r - 1, UPDATE(a - d * l));
        }
        else {
            cin >> node;
            int val = st.query(node - 1, node - 1).first;
            val += st2.query(node - 1, node - 1);
            cout << val << '\n';
        }
    }
    return 0;
}
