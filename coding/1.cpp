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

const int N=200001;
int n;
int a[N];

void solve() {
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }

    int ans=INT_MAX;

    for(int i=0;i<n-1;i++) {
        int times;
        if(i==0) {
            times = (a[1]+1)/2;
            if(a[0]-times>0)
                times = a[0];
        }
        else {
            times = (a[i+1]+1)/2;
            if(a[i]-times>0)
                times += (a[i]-times+1)/2;
        }
        if(times < ans)
            ans=times;
    }

    // 杀死怪物不连续
    // 杀死怪物包含第一个
    if(n>2) {
        int times = a[0];
        times += (*min_element(a+2, a+n)+1)/2;
        if(times<ans) {
            ans=times;
        }
    }

    // 杀死怪物不包含第一个
    if(n>3) {
        sort(a+1, a+n);
        int times = (a[1]+1)/2+(a[2]+1)/2;
        if(times<ans) {
            ans=times;
        }
    }
    cout<<ans<<endl;
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