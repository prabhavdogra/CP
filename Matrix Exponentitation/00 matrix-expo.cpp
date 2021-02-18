#include <bits/stdc++.h>
#define ll long long int
using namespace std; 
#define M 1000000007

ll mod(ll x) {
	if(x < 0) x += M;
	return x % M;
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
	
	return 0;
}
