#include <bits/stdc++.h>
using namespace std;

template<typename NODE, class S>
struct mergeTree {
    int32_t sz;
    vector<NODE> t;
    mergeTree() {}
    mergeTree(vector<NODE> &a) {
        sz = a.size();
        t.resize(4 * sz);
        build(a, 1, 1, sz);
    }
    void build(vector<NODE> &a, int32_t u, int32_t l, int32_t r) {
        if(l == r) {
            t[u].apply(a[l - 1]);
            return;
        }
        int mid = (l + r) >> 1;
        build(a, 2 * u, l, mid);
        build(a, 2 * u + 1, mid + 1, r);
        t[u].merge(t[u << 1], t[(u << 1) + 1]);
    }
    template <int (*f)(NODE&, S)> 
    int query(int32_t l, int32_t r, S k) {
        return queryHelper<f>(1, 1, sz, l + 1, r + 1, k);
    }
    template <int (*f)(NODE&, S)> 
    int queryHelper(int32_t u, int32_t l, int32_t r, int32_t ql, int32_t qr, S k) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return f(t[u], k);
        int mid = (l + r) >> 1;
        int left = queryHelper<f>(u << 1, l, mid, ql, qr, k);
        int right = queryHelper<f>((u << 1) + 1, mid + 1, r, ql, qr, k);
        return left + right;
    }
};

using S = int;
struct NODE1 {
    vector<S> cur;
    void apply(NODE1 x) {
        cur = x.cur;
    }
    void merge(NODE1 &l, NODE1 &r) {
        int32_t i = 0, j = 0;
        while (i < l.cur.size() && j < r.cur.size())
            if (l.cur[i] <= r.cur[j]) cur.push_back(l.cur[i]), i++;
            else cur.push_back(r.cur[j]), j++;
        while (i < l.cur.size()) cur.push_back(l.cur[i]), i++;
        while (j < r.cur.size()) cur.push_back(r.cur[j]), j++;
    }
};

int f(NODE1 &a, S k) { 
    return a.cur.end() - upper_bound(a.cur.begin(), a.cur.end(), k); 
}

struct distinctRangeQuery {
    int n;
    vector<NODE1> b;
    mergeTree<NODE1, S> st;
    distinctRangeQuery(vector<int> &a) {
        n = a.size();
        b.resize(n);
        map<int, vector<int>> m;
        for(int i = 0; i < n; i++)
            m[a[i]].push_back(i);
        for(auto &[id, vec]: m) {
            reverse(vec.begin(), vec.end());
            int last = 1e9;
            for(auto it: vec) {
                b[it].cur.push_back(last);
                last = it;
            }
        }
        st = mergeTree<NODE1, S> (b);
    }
    int getDistinct(int l, int r) {
        return st.query<f>(l, r, r);
    }
};

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, l, r;
    cin >> n;
    vector<int> a(n);
    distinctRangeQuery t(a);
    t.getDistinct(l, r);
    return 0;
}
