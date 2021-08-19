#include <bits/stdc++.h>
using namespace std;
#define int long long int
// https://www.codechef.com/AUG21B/problems/CDIGLNUM/
// (Partially AC)

string s;
vector<int> f(11, 1);
map<pair<pair<int, int>, pair<int, int>>, int> dp;

int rec(int n, int p, int len, int tight) {
    if(n == s.length())
        return (f[len] <= p);
    if(dp.count({{n, p}, {len, tight}}))
        return dp[{{n, p}, {len, tight}}];
    int ans = 0;
    if(p == -1) {
        ans += rec(n + 1, p, len, 0);
        if(tight) {
            for(int i = 1; i < (s[n] - '0'); i++)
                ans += rec(n + 1, i, len + 1, 0);
            ans += rec(n + 1, (s[n] - '0'), len + 1, 1);
        }
        else {
            for(int i = 1; i < 11; i++)
                ans += rec(n + 1, i, len + 1, tight);
        }
    }
    else if(tight) {
        for(int i = 1; i < (s[n] - '0'); i++)
            ans += rec(n + 1, p * i, len + 1, 0ll);
        ans += rec(n + 1, p * (s[n] - '0'), len + 1, 1ll);
    }
    else {
        for(int i = 1; i < 11; i++)
            ans += rec(n + 1, p * i, len + 1, 0ll);
    }
    return dp[{{n, p}, {len, tight}}] = ans;
}

void solve() {
    dp.clear();
    cin >> s;
	  for(int i = 1; i < 11; i++)
		    f[i] = f[i - 1] * i;
	  cout << rec(0ll, -1ll, 0ll, 1ll) << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
      solve();
    return 0;
}
