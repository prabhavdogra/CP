#include <bits/stdc++.h>
#define ll long long int
using namespace std; 

const ll MOD = 1e9 + 7;
const ll MOD2 = static_cast<ll>(MOD) * MOD;

struct matrix
{
	vector<vector<ll>> mat;
	ll n_rows, n_cols;

	matrix() {}

	matrix(vector<vector<ll>> values): mat(values), n_rows(values.size()),
		n_cols(values[0].size()) {}

	static matrix identity_matrix(ll n)
	{
		vector<vector<ll>> values(n, vector<ll>(n, 0));
		for(ll i = 0; i < n ; i++)
			values[i][i] = 1;
		return values;
	}

	matrix operator*(const matrix &other) const 
	{
		ll n = n_rows, m = other.n_cols;
		vector<vector<ll>> result(n_rows, vector<ll>(n_cols, 0));
		for(ll i = 0; i < n; i++)
			for(ll j = 0; j < m; j++) {
				ll tmp = 0;
				for(ll k = 0; k < n_cols; k++) {
					tmp += mat[i][k] * 1ll * other.mat[k][j];
					while(tmp >= MOD2)
						tmp -= MOD2;
				}
				result[i][j] = tmp % MOD;
			}

		return move(matrix(move(result)));
	}
	
	inline bool is_square() const {
		return n_rows == n_cols;
	}
};

matrix pw(matrix a,ll p){
	matrix result = matrix::identity_matrix(a.n_cols);
	while (p > 0) {
		if (p & 1)
			result = a * result;
		a = a * a;
		p >>= 1;
	}
	return result;
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
