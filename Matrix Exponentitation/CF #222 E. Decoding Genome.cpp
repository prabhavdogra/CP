#include <bits/stdc++.h>
#define ll long long int
using namespace std; 

// B. Decoding Genome
// https://codeforces.com/problemset/problem/222/E

ll mod(ll x) {
	if(x < 0) x += 1000000007;
	return x % 1000000007;
}

vector <vector<ll>> matmul(vector<vector<ll>> &a, vector<vector<ll>> &b) {
	vector<vector<ll>> c(a.size(), vector<ll> (b[0].size(), 0));
	if(a[0].size() != b.size()) 
		return c;
	for(ll i = 0 ; i < a.size(); i++) {
		for(ll j = 0 ; j < b[0].size(); j++) {
			for(ll k = 0 ; k < b.size() ; k++) {
				c[i][j] += mod(a[i][k] * b[k][j]);
				c[i][j] = mod(c[i][j]);
			}
		}
	}
	return c;
}

vector<vector<ll>> matexp(vector<vector<ll>> m, ll n) {
	vector<vector<ll>> a(m.size(), vector<ll> (m.size(), 0));
	for(ll i = 0 ; i < m.size() ; i++)
	 	a[i][i] = 1;
	while(n > 0) {
		if(n % 2 == 1)
			a = matmul(m, a);
		m = matmul(m, m);
		n /= 2;
	} 
	return a;
}

void pr(vector<vector<ll>> a) {
	for(ll i = 0 ; i < a.size() ; i++) { 
		for(ll j = 0 ; j < a[0].size() ; j++) 
			cout << a[i][j] << " "; 
		cout << endl;
	}
}

int main() { 
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	ll n, m, k;
	cin >> n >> m >> k;
	vector<vector<ll>> a(m, vector<ll>(m, 1));
	for(ll i = 0 ; i < k ; i++) {
		char c1, c2;
		cin >> c1 >> c2;
		ll x, y;
		if(c1 <= 'Z' && c1 >= 'A') x = c1 - 'A' + 26;
		else x = c1 - 'a';
		if(c2 <= 'Z' && c2 >= 'A') y = c2 - 'A' + 26;
		else y = c2 - 'a';
		a[x][y] = 0;
	}
	vector <vector<ll>> c = matexp(a, n - 1);
	pr(c);
	ll ans = 0;
	for(ll i = 0 ; i < c.size() ; i++) 
		for(ll j = 0 ; j < c[0].size() ; j++) 
			ans = mod(ans + c[i][j]);
	cout << mod(ans) << endl;
	return 0;
}
