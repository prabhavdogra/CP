#include <bits/stdc++.h>
#define int long long int
using namespace std;

// https://www.codechef.com/problems/ODDBITS

// {len, sm, tight, parity}
int dp[35][41][2][3], n;

int rec(string &s, int len, int sm, int tight, int parity) {
    if(len == s.size())
        return sm;
    if(dp[len][sm][tight][parity] != -1)
        return dp[len][sm][tight][parity];

    int ans = 0;
    if(parity == 2) {
        if(tight) {
            ans += rec(s, len + 1, sm, !tight, 2);
            ans += rec(s, len + 1, sm + 1, tight, 0);
        }
        else {
            ans += rec(s, len + 1, sm + 1, tight, 0);
            ans += rec(s, len + 1, sm, tight, 2);
        }
    }
    else if(tight) {
        if(s[len] == '0')
            ans += rec(s, len + 1, sm, tight, !parity);
        else {
            ans += rec(s, len + 1, sm, !tight, !parity);
            ans += rec(s, len + 1, sm + (parity == 1), tight, !parity);
        }
    }
    else {
        ans += rec(s, len + 1, sm + (parity == 1), tight, !parity);
        ans += rec(s, len + 1, sm, tight, !parity);
    }
    return dp[len][sm][tight][parity] = ans;
}

int check(int val) {
    memset(dp, -1, sizeof(dp));
    string s = "";
	while (val != 0)
		s += to_string(val % 2), val /= 2;
	reverse(s.begin(), s.end());
    return rec(s, 0, 0, 1, 2);
}

void prabhav() {
    cin >> n;
    int start = 1, end = n;
    while (start < end) {
        int mid = start + (end - start)/2;
        if (check(mid) >= n)
            end = mid;
        else
            start = mid + 1;
    }
    cout << start << "\n";
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		prabhav();
	return 0;
}
