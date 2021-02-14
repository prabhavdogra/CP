#include <bits/stdc++.h>
using namespace std;
#define ll              long long int

// Part 1 - 2B
// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B

const int32_t maxn = 1e5;

template<typename NODE,typename UPDATE>
struct segtree{
	bool built=false,lazy[4*maxn];
	NODE zero=NODE(),t[4*maxn];
	UPDATE noop=UPDATE(),upds[4*maxn];
	int32_t tl[4*maxn],tr[4*maxn];
	inline void pushdown(int32_t v)
	{
		if(lazy[v]){
			apply(v*2,upds[v]);
			apply(v*2+1,upds[v]);
			lazy[v]=0;
			upds[v]=noop;
		}
	}
	inline void apply(int32_t v,UPDATE &val)
	{
		if(tl[v]!=tr[v]){
			lazy[v]=1;
			upds[v].combine(val,tl[v],tr[v]);
		}
		val.apply(t[v],tl[v],tr[v]);
	}
	template<typename T>
	void build(T &a, int32_t v, int32_t l, int32_t r) {
		tl[v]=l;
		tr[v]=r;
		if (l == r) {
			t[v]=a[l];
			return;
		} else {
			int32_t tm = (l + r) / 2;
			build(a, v*2, l, tm);
			build(a, v*2+1, tm+1, r);
			t[v].merge(t[v*2],t[v*2+1]);
		}
	}
	NODE query(int32_t v, ll l, ll r) {
		if (l > tr[v] || r < tl[v])
			return zero;
		if (l <= tl[v] && tr[v] <= r) {
			return t[v];
		}
		pushdown(v);
		NODE a,b,ans;
		a=query(v*2, l, r);
		b=query(v*2+1, l, r);
		ans.merge(a,b);
		return ans;
	}
	void rupd(int32_t v, ll l, ll r, UPDATE &val)
	{
		if(l > tr[v] || r < tl[v])
			return;
		if(l <= tl[v] && tr[v] <= r)
		{
			apply(v,val);
			return;
		}
		pushdown(v);
		rupd(v*2,l,r,val);
		rupd(v*2+1,l,r,val);
		t[v].merge(t[v*2],t[v*2+1]);
	}
	template<typename T>
	ll descent_right(ll l, T x, int32_t v, NODE &prev) {
		if (l > tr[v]) // node is completely out of range
			return leng;
		if(l <= tl[v]){ // node is completely in range
			NODE cur;
			cur.merge(prev,t[v]);
			if (!cur.check(x)){ // go further right than this node
				swap(prev,cur); // merging this node's contribution
				return leng;
			}
			if (tl[v]==tr[v]) {
				return tr[v];
			}
		}
		pushdown(v);
		ll ans=descent_right(l, x, v*2, prev); // trying to find in left child
		if(ans!=leng)return ans; // found in left child
		return descent_right(l, x, v*2+1, prev); // finding in right child
	}
	template<typename T>
	ll descent_left(ll r, T x, int32_t v, NODE &prev) {
		if (r < tl[v]) // node is completely out of range
			return -1;
		if(r >= tr[v]){ // node is completely in range
			NODE cur;
			cur.merge(t[v],prev);
			if (!cur.check(x)){ // go further left than this node
				swap(cur,prev); // merging this node's contribution
				return -1;
			}
			if (tl[v]==tr[v]) {
				return tl[v];
			}
		}
		pushdown(v);
		ll ans=descent_left(r, x, v*2+1, prev); // trying to find in right child
		if(ans!=-1)return ans; // found in right child
		return descent_left(r, x, v*2, prev); // finding in left child
	}
	
	ll leng=maxn;
	void clear(){
		fill(t,t+4*leng,zero);
		fill(lazy,lazy+4*leng,false);
		fill(upds,upds+4*leng,noop);
		built = false;
	}
	template<typename T>
	void build(T &a){
		build(a,1,0,leng-1);
		built=true;
	}
	template<typename T>
	ll descent_right(ll l, T x){ // minimum r such that [l...r].check(x) == true, returns segtree.leng if not found
		NODE prev=zero;
		return descent_right(l,x,1,prev);
	}
	template<typename T>
	ll descent_left(ll r, T x){ // maximum l such that [l...r].check(x) == true, returns -1 if not found
		NODE prev=zero;
		return descent_left(r,x,1,prev);
	}
	NODE query(ll l,ll r){
		if(!built)build(t);
		return query(1,l,r);
	}
	void rupd(ll l,ll r,UPDATE val){
		if(!built)build(t);
		rupd(1,l,r,val);
	}
};

#define node node1
#define update update1
struct node{
	ll v = 0;
	node(){}
	node(ll val){
		v = val;
	}
	void merge(node &l,node &r) {
		v = l.v + r.v;
	}
	bool check(ll x){
		if(x <= v) return true;
		return false;
	}
};
struct update 
{
	ll v = 0;
	update(){}
	update(ll val){
		v = val;
	}
	void combine(update &other,int32_t tl,int32_t tr){
	}
	void apply(node &x,int32_t tl,int32_t tr){
		x.v = !x.v ;
	}
};

segtree<node,update> t;
#undef node
#undef update

void solve() {
	ll n, m;
	cin >> n >> m;
	t.leng = n;
	t.clear();
	vector<ll> v(n);
	for(ll i = 0 ; i < n ; i++) cin >> v[i];
	t.build(v);
	while(m--) {
		// for(ll i = 0 ; i < n ; i++) cout << t.query(i, i).v << " "; cout << endl;
		ll a, b, c;
		cin >> a >> b;
		if(a == 1) {
			t.rupd(b, b, c);
		}
		else {
			cout << t.descent_right(0, b + 1) << endl;
		}
	}
}

int main() 
{   
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE
		// freopen("input.txt", "r", stdin) ;
		// freopen("output.txt", "w", stdout) ;
	#endif 
	solve();
	return 0;
}
