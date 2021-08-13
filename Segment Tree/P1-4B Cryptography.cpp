#include <bits/stdc++.h>
using namespace std; 

namespace atcoder {

template <class S, S (*operation)(const S&, const S&), S (*initialize)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(vector<S>(n, initialize())) {}
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }

    segtree(const vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = vector<S>(2 * size, initialize());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void upd(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S query(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= _n);
        S sml = initialize(), smr = initialize();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = operation(sml, d[l++]);
            if (r & 1) smr = operation(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return operation(sml, smr);
    }

    S all_query() { return d[1]; }

    template <bool (*f)(S)> int descent_right(int l) {
        return descent_right(l, [](S x) { return f(x); });
    }
    template <class F> int descent_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(initialize()));
        if (l == _n) return _n;
        l += size;
        S sm = initialize();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(operation(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(operation(sm, d[l]))) {
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

    template <bool (*f)(S)> int descent_left(int r) {
        r++;
        return descent_left(r, [](S x) { return f(x); }) - 1;
    }
    template <class F> int descent_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(initialize()));
        if (r == 0) return 0;
        r += size;
        S sm = initialize();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(operation(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(operation(d[r], sm))) {
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
    vector<S> d;

    void update(int k) { d[k] = operation(d[2 * k], d[2 * k + 1]); }
};

}
using namespace atcoder;

int mod;
vector<vector<int>> c(2, vector<int> (2, 0));
using S = vector<vector<int>>;

vector<vector<int>> ID{{1, 0}, {0, 1}};
S initialize() { 
    return ID; 
}
S operation(const S &l, const S &r) { 
    c[0][0] = (l[0][0] * r[0][0] + l[0][1] * r[1][0]) % mod;
    c[0][1] = (l[0][0] * r[0][1] + l[0][1] * r[1][1]) % mod;
    c[1][0] = (l[1][0] * r[0][0] + l[1][1] * r[1][0]) % mod;
    c[1][1] = (l[1][0] * r[0][1] + l[1][1] * r[1][1]) % mod;
    return c;
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
	segtree<S, operation, initialize> st(a);
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
