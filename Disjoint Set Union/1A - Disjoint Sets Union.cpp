#include <bits/stdc++.h>
using namespace std;
#define int              long long int

// Codeforce Edu - 1A
// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A

const int SZ = 2e5 + 5; // Remember
vector<int> parent(SZ), len(SZ);

void clear(int n) {
    for(int i = 0; i < n; i++) {
        parent[i] = i;
        len[i] = 1;
    }
}

int getParent(int u) {
    if(parent[u] == u)
        return u;
    return parent[u] = getParent(parent[u]);
}

void unionSets(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a != b) {
        if (len[a] < len[b])
            swap(a, b);
        parent[b] = a;
        len[a] += len[b];
    }
}

// 0 Based Indexing
// Set, the size and initialize by
// clear(SIZE)

signed main() {   
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, u, v;
    cin >> n >> m;
    clear(n);
    while(m--) {
        string a;
        cin >> a >> u >> v;
        if(a == "union") {
            unionSets(u - 1, v - 1);
        }
        else {
            if(getParent(u - 1) == getParent(v - 1))
                cout << "YES\n";
            else 
                cout << "NO\n";
        }
    }
    return 0;
}
