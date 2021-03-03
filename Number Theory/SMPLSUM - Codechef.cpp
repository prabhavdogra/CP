#include <bits/stdc++.h>
using namespace std;
#define ll              long long int

// Simple Sum - Codechef
// https://www.codechef.com/problems/SMPLSUM

ll poww(ll x, ll n) { 
    if(n == 0) return 1 ; 
    ll u = poww(x, n >> 1);
    u = (u * u);
    if(n&1) 
        u = (u * x) ;	
    return u;
}

ll MAXN;
vector<int> isPrime;
vector<ll> prime;
vector<ll> SPF; // Smallest Prime Factor;
void sieve() {
    SPF.resize(MAXN) ;
    isPrime.resize(MAXN, true) ;
    prime.clear();
    isPrime[0] = isPrime[1] = false;
    for(int i = 2 ; i < MAXN ; i++) {
        if(isPrime[i]) {
            prime.push_back(i);
            SPF[i] = i;
        }
        for(ll j = 0 ; j < prime.size() && i*prime[j] < MAXN && prime[j] <= SPF[i] ; j++) {
            isPrime[i*prime[j]] = false;
            SPF[i*prime[j]] = prime[j];
        }
    }
}

void solve(ll n) {
    ll ans = 1;
    while(n > 1) {
        ll c = 0;
        ll x = SPF[n];
        while(n % x == 0) {
            n /= x;
            c++;
        }
        ll temp = 0;
        if(c == 1) temp = x * (x - 1) + 1;
        else temp = (poww(x, 2 * c + 1) + 1)/(x + 1);
        ans *= temp;
    }
    cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE
		// freopen("input.txt", "r", stdin) ;
		// freopen("output.txt", "w", stdout) ;
	#endif
    MAXN = 1e7 + 5;
    sieve() ;
	ll t;
	cin >> t;
	while(t--) {	
        ll x;
        cin >> x;
        solve(x);
    }
    return 0;
}
