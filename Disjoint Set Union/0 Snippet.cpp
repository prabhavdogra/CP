#include <bits/stdc++.h>
using namespace std;
#define int              long long int

const int SZ = 2e5 + 5; // Remember
vector<int> parent(SZ), len(SZ), mx(SZ), mn(SZ);

void clear(int n) {
    for(int i = 0; i < n; i++) {
        parent[i] = i;
        len[i] = 1;
        mx[i] = i;
        mn[i] = i;
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
        mx[a] = max(mx[a], mx[b]);
        mn[a] = min(mn[a], mn[b]);
    }
}

// 0 Based Indexing
// Set, the size and initialize by
// clear(SIZE)

signed main() {   
    ios::sync_with_stdio(0); cin.tie(0);
    
    clear(SZ);

    return 0;
}
