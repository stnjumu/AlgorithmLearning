#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
        cout<<a[i]<<endl;
    }

    return 0;
}