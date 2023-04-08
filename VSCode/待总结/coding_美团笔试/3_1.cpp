#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

vector<vector<int>> minAs;
vector<vector<int>> maxAs;

void back_trace(int n,int m,int s,vector<int> &a, int start, int &ans, int price) {
    if(start>=n) {
        ans = min(ans, price);
    }

    for(int i=1;i<=m;i++) {
        if(start+i>n)
            break;
        
        // 装[start, start+i)
        int minA,maxA;
        if(minAs[start][start+i]!=-1)
            minA= minAs[start][start+i];
        else {
            minA = *min_element(a.begin()+start, a.begin()+start+i);
            minAs[start][start+i]=minA;
        }
        if(maxAs[start][start+i]!=-1)
            maxA=maxAs[start][start+i];
        else {
            maxA=*max_element(a.begin()+start, a.begin()+start+i);
            maxAs[start][start+i]=maxA;
        }
        int newPrice=i*((minA+maxA)/2)+s;
        back_trace(n,m,s,a,start+i,ans,price+newPrice);
    }
}

int main() {
    int n,m,s;
    cin>>n>>m>>s;
    minAs.assign(n,vector<int>(n+1, -1));
    maxAs.assign(n,vector<int>(n+1, -1));
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }

    int ans=2147483647;
    back_trace(n,m,s,a,0, ans,0);

    cout<<ans<<endl;

    return 0;
}