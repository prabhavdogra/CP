#include<bits/stdc++.h>
using namespace std;
namespace atcoder {

template <class NODE,
          NODE (*operation)(const NODE&, const NODE&),
          NODE (*initialization)(),
          class UPDATE,
          NODE& (*apply)(UPDATE&, NODE&),
          UPDATE (*combine)(const UPDATE&, const UPDATE&),
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
        return descent_left(r, [](NODE x) { return g(x); }) - 1;
    }
    template <class G> int descent_left(int r, G g) {
        r++;
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

using NODE = vector<vector<int>>;
using UPDATE = int;
int mod;
 
vector<vector<int>> ID{{1, 0}, {0, 1}};
 
NODE initialization() { return NODE(ID); }
NODE operation(const NODE &l, const NODE &r) {
    vector<vector<int>> c(2, vector<int> (2, 0));
    c[0][0] = (l[0][0] * r[0][0] + l[0][1] * r[1][0]) % mod;
    c[0][1] = (l[0][0] * r[0][1] + l[0][1] * r[1][1]) % mod;
    c[1][0] = (l[1][0] * r[0][0] + l[1][1] * r[1][0]) % mod;
    c[1][1] = (l[1][0] * r[0][1] + l[1][1] * r[1][1]) % mod;
    return c;
}
NODE& apply(UPDATE &l, NODE &r) {
    return r;
}
UPDATE id() { return UPDATE(0); }
UPDATE combine(const UPDATE &cur, const UPDATE &prev) { 
    return cur;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> mod >> n >> q;
	vector<vector<vector<int>>> a(n, ID);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                cin >> a[i][j][k];
	lazy_segtree<NODE, operation, initialization, UPDATE, apply, combine, id> st(a);
    while(q--) {
        int left, right;
        cin >> left >> right;
        auto ans = st.query(left - 1, right - 1);
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                cout << ans[i][j] << " \n"[j == 1];
        cout << '\n';
    }
    return 0;
}