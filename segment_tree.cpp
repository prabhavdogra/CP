#include <bits/stdc++.h>
using namespace std;
#define ll              long long int

// Segment Tree - Balanced Tree for Range based queries and updates

// Update in O(logn) **
// Query in O(logn)
// Space Complexity - O(n)
// Alternate approach O(n) for Update and O(1) for Query using a basic Hash-type array

// Indexing in Segment Trees
//          1
//        /   \ 
//      2       3
//     / \     / \ 
//    4   5   6   7
//   / \     / \ 
//  8   9  12   13   
// Children Nodes indices are 2*i, 2*(i + 1)

// Example:
// A[]: 1 3 2 -5 6 4

//                 -5[0,5]
//               /         \ 
//         1[0,2]          -5[3,5]
//        /     \          /      \ 
//     1[0,1]   2[2,2]  -5[3,4]   4[5,5]
//   /    \              /     \ 
// 1[0,0] 3[1,1]      -5[3,3]  6[4,4]   

// Tree[]: -5, 1, -5, 1, 2, -5, 4, 1, 3, G, G, -5, 6
//                                       ↑  ↑
//                                      Garbage



// Segment Tree Implementation - Finding the minimum number in the query range
///---------------------------------MAIN CODE---------------------------------//


// Query in which we need to update a range of numbers
ll rangeUpdate(ll tree[], ll start, ll end, ll u_start, ll u_end, ll increment, ll index) {
    if(u_start > end || u_end < start) { // Index to be updated is Out of Bounds - No overlap
        return 0;
    }
    if(start == end) { // Leaf Node
        tree[index] += increment;
        return 0;
    }
    ll mid = (start + end)/2;
    rangeUpdate(tree, start, mid, u_start, u_end, increment, 2 * index);
    rangeUpdate(tree, mid + 1, end, u_start, u_end, increment, 2 * index + 1);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return 0;
}

// Segment Tree Update Query
ll updateNode(ll tree[], ll start, ll end, ll i, ll increment, ll index) { // i: index of value to be updated
    if(i > end || i < start) { // Index to be updated is Out of Bounds - No overlap
        return 0;
    }
    if(start == end) { // Leaf Node
        tree[index] += increment;
        return 0;
    }
    ll mid = (start + end)/2;
    updateNode(tree, start, mid, i, increment, 2 * index);
    updateNode(tree, mid + 1, end, i, increment, 2 * index + 1);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return 0;
}

// Segment Tree Query Function
ll query(ll tree[], ll start, ll end, ll q_start, ll q_end, ll index) {
    if(start >= q_start && end <= q_end) { // Complete overlap
        return tree[index];
    }
    else if(start > q_end || q_start > end ) { // No overlap
        return 1e18;
    }
    // Partial Overlap
    ll mid = (start + end)/2;
    ll leftMin = query(tree, start, mid, q_start, q_end, 2*index);
    ll rightMin = query(tree, mid + 1, end, q_start, q_end, 2*index + 1);
    return min(leftMin, rightMin);
}

// Constructing the Segment Tree
ll buildTree(ll a[], ll start, ll end, ll tree[], ll index) { // Bottom Up Recursion
    if(start == end) {
        tree[index] = a[end];
        return 0;
    }
    ll mid = (start + end)/2;
    buildTree(a, start, mid, tree, 2*index); // Left child
    buildTree(a, mid + 1, end, tree, 2*index + 1); // Right Child
    tree[index] = min(tree[2*index], tree[2*index + 1]);
    return 0;
}

// Test case:
//            n : 6
//          A[] : 1 3 2 -5 6 4 
//        Query : 0 2
//             -> 1  
//       Update : 0 10 
//             -> Increments the value at index 0 by 10
//      New A[] : 1 13 4 -5 6 4
// Range Update : 1 3 1
//             -> Increments number in the index range 1 to 3 by 1

// 6
// 1 3 2 -5 6 4
// 0 2
// 1 10
// 1 3 1

int main() {   
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin) ;
        freopen("output.txt", "w", stdout) ;
    #endif 
    ll n;
    cin >> n;
    ll a[n], tree[4*n + 1] = {0};
    for(ll i = 0 ; i < n ; i++) cin >> a[i];

    buildTree(a, 0, n - 1, tree, 1); // Building Segment Tree
    for(ll i = 1 ; i < 4*n + 1 ; i++) // Printing the tree (Array)
        cout << tree[i] << " ";
    cout << '\n';

    ll l, r; 
    cin >> l >> r;
    cout << query(tree, 0, n - 1, l, r, 1) << '\n'; // Query

    ll index, inc;
    cin >> index >> inc ;
    updateNode(tree, 0, n - 1, index, inc, 1); // increment element at index by inc
    // A[]: 1 13, 2, -5, 6, 4
    for(ll i = 1 ; i < 4*n + 1 ; i++) {  // Printing the tree (Array)
        cout << tree[i] << " ";
    }
    cout << '\n';

    ll u_start, u_end;
    cin >> u_start >> u_end >> inc;
    rangeUpdate(tree, 0, n - 1, u_start, u_end, inc, 1);
    // A[]: 1 14, 3, -4, 6, 4
    for(ll i = 1 ; i < 4*n + 1 ; i++) {  // Printing the tree (Array)
        cout << tree[i] << " ";
    }
    cout << '\n';
    return 0;
}
