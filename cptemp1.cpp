#ifdef prabhav_
	// #define TERMINAL
	#include "Headers/debug.cpp"
#else
	#define d(...) 0
	#pragma GCC optimize("O3")
	#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma")
#endif
#include <bits/stdc++.h>
using namespace std; 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define int long long int
#define vi vector<int>
#define pii pair<int, int>
#define ld long double
#define forp(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define sz(a) (int)a.size()
#define endl '\n'
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define uniq(a) (a).erase(unique(all(a)), (a).end())
#define fix(f, n) fixed << setprecision(n) << f
#define setbits(x) __builtin_popcount(x)
#define setbitsll(x) __builtin_popcountll(x)
#define MSB(n) (32 - __builtin_clz(n))
#define pb push_back
#define ff first
#define ss second
constexpr int64_t INF = 2e18;
constexpr int64_t M = 1e9 + 7;
int ceil(int a, int b) { return (a + b - 1) / b; }


void prabhav() {
	int n, temp, ans = 0;
	cin >> n ;

}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T = 1;
	cin >> T;
	while (T--) {
		prabhav();
	}
	return 0;
}
