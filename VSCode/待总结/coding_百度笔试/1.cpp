#include<iostream>

using namespace std;

long long getSum(int x) {
    long long sum =0;
    while(x!=0) {
        sum+=x%10;
        x/=10;
    }
    return sum;
}

void solve() {

    int L, R;
    cin >> L >> R;
    
    long long ans=0;
    for(int x=L;x<=R;x++) {
        long long sum = getSum(x);
        if(ans<sum*x) {
            ans =sum*x;
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