#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<cctype>
#include<limits>
#include<map>
#include<set>
using namespace std;

template<class T>
void printVector(vector<T> v) {
    for(auto n:v) {
        cout<<n<<" ";
    }
    cout<<endl;
    // for(auto n:v) {
    //     cout<<n<<endl;
    // }
}

int n;

void solve() {

    cin>> n;

    vector<int> binary;
    while(n!=0) {
        binary.push_back(n%2);
        n/=2;
    }
    
    // printVector(binary);

    for(int i=0;i<binary.size();i++) {
        if(binary[i]!=0) {
            cout<<char('a'+i);
        }
    }
    
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}