#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<numeric>
#include<iomanip>
#include<cctype>
#include<limits>
using namespace std;


const int N = 101;
int n;
int a[N];
long long ans;

void back_trace(int start,long long sum1,long long sum2) {
    if(start>=n) {
        if(ans>abs(sum1-sum2))
            ans = abs(sum1-sum2);
        return;
    }

    back_trace(start+1, sum1+a[start], sum2);
    back_trace(start+1, sum1, sum2+a[start]);
}
void solve() {

    cin>> n;
    for(int i=0;i<n;i++)
        cin>> a[i];
    
    long long sum1=0,sum2=0;
    ans = LLONG_MAX;
    back_trace(0,sum1,sum2);
    cout<< ans<<endl;

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