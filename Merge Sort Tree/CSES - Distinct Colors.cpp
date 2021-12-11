#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1139/

template<typename NODE, class S>
struct mergeTree {
    int32_t sz;
    vector<NODE> t;
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

int f(NODE1 &a, S k) { return a.cur.end() - upper_bound(a.cur.begin(), a.cur.end(), k); }

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, x, y;
    cin >> n;
    vector<int> col(n);
    for(auto &it: col)
        cin >> it;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    vector<int> a(n), u(n), v(n);
    int timer = 0;
    auto dfs = [&] (const auto &self, int node, int parent) -> void {
        u[node] = v[node] = timer;
        a[timer] = col[node];
        for(auto &child: adj[node]) {
            if(child != parent) {
                timer++;
                self(self, child, node);
                v[node] = timer;
            }
        }
        return;
    };
    dfs(dfs, 0, 0);
    vector<NODE1> b(n);
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
    mergeTree<NODE1, S> st(b);
    for(int i = 0; i < n; i++)
        cout << st.query<f>(u[i], v[i], v[i]) << " ";
    cout << '\n';
    return 0;
}
