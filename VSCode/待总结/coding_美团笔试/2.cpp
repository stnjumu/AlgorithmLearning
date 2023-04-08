#include<vector>
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

int n;
int x,y;
int maxLenx=0;
int maxLeny=0;

void bfs(int x, int y,vector<vector<int>> &edges,vector<int> &found1, vector<int> &found2) {
    // bfs x, not use (x,y)
    queue<int> q;
    q.push(x);
    found1[y]=1; // 不遍历y；
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto &edge:edges) {
            if(edge[0]==node &&found1[edge[1]]==0) {
                found1[edge[1]]=found1[edge[0]]+1;
                q.push(edge[1]);
                maxLenx=max(maxLenx, found1[edge[1]]);
            }
            if(edge[1]==node && found1[edge[0]]==0) {
                found1[edge[0]]=found1[edge[1]]+1;
                q.push(edge[0]);
                maxLenx=max(maxLenx, found1[edge[0]]);
            }
        }
    }

    q.push(y);
    found2[x]=1;
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto &edge:edges) {
            if(edge[0]==node &&found2[edge[1]]==0) {
                found2[edge[1]]=found2[edge[0]]+1;
                q.push(edge[1]);
                maxLeny=max(maxLeny, found2[edge[1]]);
            }
            if(edge[1]==node && found2[edge[0]]==0) {
                found2[edge[0]]=found2[edge[1]]+1;
                q.push(edge[0]);
                maxLeny=max(maxLeny, found2[edge[0]]);
            }
        }
    }
    return;
}

int main() {
    cin>>n;
    vector<vector<int>> edges;
    vector<int> found1,found2;
    found1.assign(n,0);
    found2.assign(n,0);

    for(int i=1;i<n;i++) {
        int pi;
        cin>>pi;
        
        edges.push_back({pi,i+1});
    }
    cin>>x>>y;

    bfs(x,y, edges, found1,found2);
    cout<<maxLenx+maxLeny+1<<endl;

    return 0;
}