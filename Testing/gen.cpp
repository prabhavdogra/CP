#include <bits/stdc++.h>
#define int long long int
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rndm(int mn_element, int mx_element) {
    int ran = rng();
    return abs(ran) % (mx_element + 1 - mn_element) + mn_element;
}

vector<int> generateArray(int n, int mn_element, int mx_element) {
    vector<int> randomArray(n);
    for(int i = 0; i < n; i++)
        randomArray[i] = rndm(mn_element, mx_element);
    for(auto it: randomArray)  
        cout << it << " ";
    cout << '\n';
    return randomArray;
}

vector<int> generatePermutation(int n) {
    vector<int> randomPermutation(n);
    iota(randomPermutation.begin(), randomPermutation.end(), 1);
    random_shuffle(randomPermutation.begin(), randomPermutation.end());
    for(auto it: randomPermutation)
        cout << it << " ";
    cout << '\n';
    return randomPermutation;
}

set<int> generateSet(int n, int mn_element, int mx_element) {
    set<int> randomSet;
    while(randomSet.size() != n)
        randomSet.insert(rndm(mn_element, mx_element));
    for(auto it: randomSet)  
        cout << it << " ";
    cout << '\n';
    return randomSet;
}

void generate() {
    // Array size
    int min_size = 2;
    int max_size = 5;
    int n = rndm(min_size, max_size);
    cout << n << '\n';
    // Array Elements
    int mn_element = 1;
    int mx_element = 10;

    // Generate Array
    // auto randomArray = generateArray(n, mn_element, mx_element);

    // Generate Permutation
    // auto randomPermutation = generatePermutation(n);

    // Generate Set
    // auto randomSet = generateSet(n, mn_element, mx_element);
}

int32_t main(int32_t argc, char* argv[]){
    srand(atoi(argv[1]));
    // freopen("../input.txt", "w", stdout);
    int testcases = 1;
    cout << testcases << '\n';
    while(testcases--) {
        // generate();
        
    }
    return 0;
}
