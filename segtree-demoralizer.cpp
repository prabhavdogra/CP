#include <bits/stdc++.h>
using namespace std;
#define ll long long int


template<typename node,typename update>
struct segtree
{
	ll leng;
	vector<node> t;
	vector<update> u;
	vector<bool> lazy;
	node identity_element;
	update identity_transformation;
	segtree(ll l){
		leng = l;
		t.resize(4 * leng);
		u.resize(4 * leng);
		lazy.resize(4 * leng);
		identity_element = node();
		identity_transformation = update();
	}
	
	void pushdown(const int32_t &v, const int32_t &tl, const int32_t &tr){
		if(!lazy[v]) return;
		int32_t tm = (tl + tr) >> 1;
		apply(v<<1,tl,tm,u[v]);
		apply(v<<1|1,tm+1,tr,u[v]);
		u[v] = identity_transformation;
		lazy[v] = 0;
	}
	
	void apply(const int32_t &v, const int32_t &tl, const int32_t &tr, update upd){
		if(tl != tr){
			lazy[v] = 1;
			u[v].combine(upd,tl,tr);
		}
		upd.apply(t[v],tl,tr);
	}
	
	template<typename T>
	void build(const T &arr,const int32_t &v, const int32_t &tl, const int32_t &tr){
		if(tl == tr){
			t[v] = arr[tl];
			return;
		}
		int32_t tm = (tl + tr) >> 1;
		build(arr,v<<1,tl,tm);
		build(arr,v<<1|1,tm+1,tr);
		t[v].merge(t[v<<1],t[v<<1|1]);
	}
	
	node query(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r){
		if(l > tr || r < tl){
			return identity_element;
		}
		if(tl >= l && tr <= r){
			return t[v];
		}
		pushdown(v,tl,tr);
		int32_t tm = (tl + tr) >> 1;
		node a = query(v<<1,tl,tm,l,r),b = query(v<<1|1,tm+1,tr,l,r),ans;
		ans.merge(a,b);
		return ans;
	}
	
	// rupd = range update
	void rupd(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r,const update &upd){
		if(l > tr || r < tl){
			return;
		}
		if(tl >= l && tr <= r){
			apply(v,tl,tr,upd);
			return;
		}
		pushdown(v,tl,tr);
		int32_t tm = (tl + tr) >> 1;
		rupd(v<<1,tl,tm,l,r,upd);
		rupd(v<<1|1,tm+1,tr,l,r,upd);
		t[v].merge(t[v<<1],t[v<<1|1]);
	}
	
	public:
	template<typename T>
	void build(const T &arr){
		build(arr,1,0,leng-1);
	}
	node query(const int32_t &l,const int32_t &r){
		return query(1,0,leng-1,l,r);
	}
	void rupd(const int32_t &l,const int32_t &r,const update &upd){
		rupd(1,0,leng-1,l,r,upd);
	}
};
/*
KEYNOTES:
1. merge(X,identity_element) = X (for nodes other than leaf node)
2. identity_transformation.combine(X) = X (combining Identity element with update)
3. NOTE: older_update.combine(newer_update) (how updates will happen)
*/

// Example: In Addition the identity element is 0, 
//          i.e., -> a + 0 = a or 0 + a = a
// 			Also: min(x,INT_MAX) = x

// Structure of each node in the segment tree
struct node
{
	// Initialised with the identity element
	ll v = 0;
	// Add more variables if needed
	node() {} 
	node(ll val) { // Building the tree
		v = val;
	}
	// Merging l and r nodes for each segment
	void merge(const node &l,const node &r) { 
		v = l.v + r.v;
		// For maximum we'll do
		// v = max(l.v, r.v);
	}
};

// Example: In Addition the identity transformation is 0, 
//          i.e., -> old += new + 0;

struct update
{
	// Initialised with the identity transformation
	ll v = 0;
	// Add more variables if needed
	update() {}
	update(ll val){
		v = val;
	}
	// Updating a node which contains identity element
	void combine(update &other,const int32_t &tl,const int32_t &tr){
		v += other.v;
		// only required for range updates
	}
	// Updating a general node
	void apply(node &x, const int32_t &tl, const int32_t &tr) { 
		x.v += v;
	}
};



// segtree<node,update> s(100005);
// vector<int> v(100005); // take input in the vector
// s.build(v);

// Single element: s.rupd(index, index, value);
// Range Update: s.rupd(start, end, value);
// Query: s.query(start, end).v

// NOTE: All indexing is 0 based


int32_t main() {
	int n;
	cin >> n;
	segtree<node,update> s(n);
	vector<ll> v(n);
	for(ll i = 0 ; i < n ; i++)
		v[i] = {0};
	s.build(v);
	
	// Single element: s.rupd(index, index, value);
	// Range Update: s.rupd(start, end, value);
	// Query: s.query(start, end).v
	
	return 0;
}

