#include<iostream>
#include<vector>
#include<algorithm>
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

void solve() {
    int n,m;
    cin>>n>>m;
    vector<int> h(n);
    for(int i=0;i<n;i++) {
        cin>>h[i];
    }
    
    vector<int> ts;
    vector<int> ks;
    for(int i=0;i<m;i++) {
        int t,k;
        cin>>t>>k;
        
        if(ts.empty()) {
            ts.push_back(t);
            ks.push_back(k);
        }
        else {
            while(!ts.empty() && k>=ks.back()) {
                ts.pop_back();
                ks.pop_back();
            }
            ts.push_back(t);
            ks.push_back(k);
        }
    }

    for(int i=0;i<ts.size();i++) {
        if(ts[i]==1) {
            // 小明，前k个从小到大排序；
            sort(h.begin(), h.begin()+ks[i]);
        }
        else {
            sort(h.begin(), h.begin()+ks[i], greater<int>());
        }
    }

    printVector(h);

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