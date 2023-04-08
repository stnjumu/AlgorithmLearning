#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    int ans=0;
    int dpi=0;
    if(s[0]=='E')
        dpi=1;
    else
        dpi=0;
    for(int i=1;i<n;i++) {
        if(s[i]=='E') {
            dpi++;
        }
        else {
            dpi--;
        }
        ans = max(ans, dpi);
        if(dpi<0) {
            dpi=0;
        }
    }
    cout<<ans<<endl;

    return 0;
}