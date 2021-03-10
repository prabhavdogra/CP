#include <bits/stdc++.h>
using namespace std;
#define ll              long long int

// CF Edu #81 - Same GCDs 
// https://codeforces.com/contest/1295/problem/D

ll phi(ll n) {
    ll result = n;
    for(ll i = 2 ; i * i <= n ; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result/i;
        }
    }
    if(n > 1) 
        result -= result / n;
    return result;
}

int main() 
{   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin) ;
        freopen("output.txt", "w", stdout) ;
    #endif 
    ll a, m;
    cin >> a >> m;
    cout << phi(m/__gcd(a, m)) << endl;
    return 0;
}
