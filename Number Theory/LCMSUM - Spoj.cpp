#include <bits/stdc++.h>
using namespace std;
#define ll              long long int

// LCM Sum - Spoj
// https://www.spoj.com/problems/LCMSUM/

const ll SZ = 1e6 + 5;
vector<ll> phi(SZ + 1);
void _phi() {
    phi[0] = 0;
    phi[1] = 1;
    for (ll i = 2 ; i <= SZ ; i++)
        phi[i] = i - 1;

    for (ll i = 2 ; i <= SZ ; i++)
        for (ll j = 2 * i ; j <= SZ ; j += i)
              phi[j] -= phi[i];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin) ;
		freopen("output.txt", "w", stdout) ;
	#endif 
    vector<ll> res(SZ);
    for(ll i = 1 ; i < SZ ; i++) {
        for(ll j = i ; j < SZ ; j += i)
            res[j] += phi[i] * i;
    }
	ll t;
	cin >> t;
	while(t--) {	
        ll x;
        cin >> x;
        cout << (x * (res[x] - 1))/2 + x << endl;
    }
    return 0;
}
