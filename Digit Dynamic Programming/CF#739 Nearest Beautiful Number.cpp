#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/contest/1560/problem/F2

map<char, int> taken;

string helper(string s, string ans, int id, int k, int tight) {
    if(ans.size() == s.size())
        return ans;

    string res = "9999999999999";
    if(!taken.size()) {
        taken[s[0]]++;
        res = min(res, helper(s, ans + s[0], id + 1, k, 1));
        taken[s[0]]--;
        if(!taken[s[0]])
            taken.erase(s[0]);
        if(s[0] != '9') {
            taken[(char)(s[id] + 1)]++;
            res = min(res, helper(s, ans + (char)(s[0] + 1), id + 1, k, 0));
            taken[(char)(s[id] + 1)]--;
            if(!taken[(char)(s[id] + 1)])
                taken.erase((char)(s[id] + 1));
        }
        return res;
    }

    if(tight) {
        if(taken.lower_bound(s[id]) != taken.end()) {
            char c = (*taken.lower_bound(s[id])).first;
            if(c == s[id])
                res = min(res, helper(s, ans + c, id + 1, k, 1));
            c = (*taken.upper_bound(s[id])).first;
            if(taken.upper_bound(s[id]) != taken.end())
                res = min(res, helper(s, ans + c, id + 1, k, 0));
            if(taken.size() != k) {
                taken[s[id]]++;
                res = min(res, helper(s, ans + s[id], id + 1, k, 1));
                taken[s[id]]--;
                if(!taken[s[id]])
                    taken.erase(s[id]);
            }
            if(taken.size() != k && s[id] != '9') {
                taken[(char)(s[id] + 1)]++;
                res = min(res, helper(s, ans + (char)(s[id] + 1), id + 1, k, 0));
                taken[(char)(s[id] + 1)]--;
                if(!taken[(char)(s[id] + 1)])
                    taken.erase((char)(s[id] + 1));
            }
        }
        else {
            if(taken.size() != k) {
                taken[s[id]]++;
                res = min(res, helper(s, ans + s[id], id + 1, k, 1));
                taken[s[id]]--;
                if(!taken[s[id]])
                    taken.erase(s[id]);
                if(s[id] != '9') {
                    taken[(char)(s[id] + 1)]++;
                    res = min(res, helper(s, ans + (char)(s[id] + 1), id + 1, k, 0));
                    taken[(char)(s[id] + 1)]--;
                    if(!taken[(char)(s[id] + 1)])
                        taken.erase((char)(s[id] + 1));
                }
            }
        }
    }
    else {
        if(taken.size() != k) {
            taken['0']++;
            char c = '0';
            while(ans.size() != s.size())
                ans += c;
            res = min(ans, res);
            taken['0']--;
            if(!taken['0'])
                taken.erase('0');
        }
        else {
            char c = (*taken.begin()).first;
            while(ans.size() != s.size())
                ans += c;
            res = min(ans, res);
        }
    }
    return res;
}

void solve() {
    taken.clear();
    int k;
    string s;
    cin >> s >> k;
    int n = s.length();
    string ans = helper(s, "", 0, k, 1);
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}
