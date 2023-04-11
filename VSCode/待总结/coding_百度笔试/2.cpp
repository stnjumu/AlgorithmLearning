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
    
    int t_last=-1, k_last=-1;
    for(int i=0;i<m;i++) {
        int t,k;
        cin>>t>>k;
        if(t_last==t && k<=k_last)
            continue;
        if(t_last!=-1&& t_last!=t && k<=k_last) {
            reverse(h.begin(),h.begin()+k);
            t_last=t;
            k_last=k;
            continue;
        }
        t_last=t;
        k_last=k;

        if(t==1) {
            // 小明，前k个从小到大排序；
            sort(h.begin(), h.begin()+k);
        }
        else {
            sort(h.begin(), h.begin()+k, greater<int>());
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