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

int n;
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

bool isPrime(int n) {
    if(n==2||n==3||n==5||n==7)
        return true;
    for(int i=2;i<=n/2;i++) {
        if(n%i==0)
            return false;
    }
    return true;
}
void solve() {

    cin >> n ;
    if(n>3) {
        // 特殊情况：前3想为3 2 1, 后面4-n一定满足条件；
        cout<<"3 2 1 ";
        for(int i=4;i<=n;i++) {
            cout<<i<<" ";
        }
        cout<<endl;
        return;
    }

    // 下面代码会超时；
    unordered_set<int> primes;
    for(int i=2;i<=2*n;i++) {
        if(isPrime(i)) {
            primes.insert(i);
        }
    }
    // for(int prime:primes)
    //     cout<<prime<<" ";
    
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        a[i]=i+1;
    }
    
    do {
        bool isAns = true;
        for(int i=0;i<n;i++) {
            if(primes.find(a[i]+i+1)!=primes.end()) {
                isAns = false;
                break;
            }
        }
        if(isAns) {
            printVector(a);
            return;
        }
    } while(next_permutation(a.begin(),a.end()));

    cout<< -1 <<endl;
    return;
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