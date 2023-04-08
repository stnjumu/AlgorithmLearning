#include<iostream>
#include<string>
#include<vector>

using namespace std;

int count(string a, string b) {
    int n=a.size();
    int ans=0;
    for(int i=0;i<n;i++) {
        if(a[i]!=b[i])
            ans++;
    }
    return ans;
}

int main() {
    int n,m,a;
    cin>>n>>m>>a;

    vector<vector<string>> desks(n, vector<string>(m)); // n*m
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin>>desks[i][j];
        }
    }

    int ans=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            int newx = (i+1)%n;
            int newy = (j+1)%m;
            string newDesk = desks[newx][newy];
            ans+=count(desks[i][j], newDesk);
        }
    }

    cout<<ans<<endl;
    return 0;
}