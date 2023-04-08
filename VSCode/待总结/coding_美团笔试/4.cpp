#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>

using namespace std;

void getMinDist(int n,int m,vector<vector<int>> &boomPos, vector<vector<int>> &minDist) {
    int k=boomPos.size();
    
    for(int i=0;i<k;i++) {
        vector<int> pos=boomPos[i];
        queue<vector<int>> q;
        q.push(pos);
        minDist[pos[0]][pos[1]]=0;

        while(!q.empty()) {
            vector<int> pos_new=q.front();
            int x=pos_new[0],y=pos_new[1];
            q.pop();

            int dst = minDist[x][y];
            // 上
            if(x-1>0) {
                if(dst+1<minDist[x-1][y]) {
                    minDist[x-1][y] = dst+1;
                    q.push({x-1,y});
                }
            }
            if(x+1<=n) {
                if(dst+1<minDist[x+1][y]) {
                    minDist[x+1][y] = dst+1;
                    q.push({x+1,y});
                }
            }
            if(y-1>0) {
                if(dst+1<minDist[x][y-1]) {
                    minDist[x][y-1] = dst+1;
                    q.push({x,y-1});
                }
            }
            if(y+1<=m) {
                if(dst+1<minDist[x][y+1]) {
                    minDist[x][y+1] = dst+1;
                    q.push({x,y+1});
                }
            }
            // if(x+1<=n) {
            //     minDist[x+1][y] = min(minDist[x+1][y], dst+1);
            //     q.push({x+1,y});
            // }
            // if(y-1>0) {
            //     minDist[x][y-1] = min(minDist[x][y-1], dst+1);
            //     q.push({x,y-1});
            // }
            // if(y+1<=n) {
            //     minDist[x][y+1] = min(minDist[x][y+1], dst+1);
            //     q.push({x,y+1});
            // }
        }
    }
}

void back_trace(int n,int m,int x1,int y1,int x2,int y2, vector<vector<int>> &minDist, int &ans, int dist,vector<vector<int>> &flag) {
    if(x2==x1&&y2==y1) {
        ans=max(ans, dist);
    }

    if(x1-1>0 && !flag[x1-1][y1]) {
        flag[x1-1][y1]=1;
        back_trace(n,m,x1-1,y1,x2,y2,minDist, ans, min(minDist[x1-1][y1],dist),flag);
    }
    if(x1+1<=n && !flag[x1+1][y1]) {
        flag[x1+1][y1]=1;
        back_trace(n,m,x1+1,y1,x2,y2,minDist, ans, min(minDist[x1+1][y1],dist),flag);
    }
    if(y1-1>0 && !flag[x1][y1-1]) {
        flag[x1][y1-1]=1;
        back_trace(n,m,x1,y1-1,x2,y2,minDist, ans, min(minDist[x1][y1-1],dist),flag);
    }
    if(y1+1<=m &&!flag[x1][y1+1]) {
        flag[x1][y1-1]=1;
        back_trace(n,m,x1,y1+1,x2,y2,minDist, ans, min(minDist[x1][y1+1],dist),flag);
    }
    // if(x1-1>0 && minDist[x1-1][y1]<=dist) {
    //     back_trace(n,m,x1-1,y1,x2,y2,minDist, ans, minDist[x1-1][y1]);
    // }
    // if(x1+1<=n && minDist[x1+1][y1]<=dist) {
    //     back_trace(n,m,x1+1,y1,x2,y2,minDist, ans, minDist[x1+1][y1]);
    // }
    // if(y1-1>0 && minDist[x1][y1-1]<=dist) {
    //     back_trace(n,m,x1,y1-1,x2,y2,minDist, ans, minDist[x1][y1-1]);
    // }
    // if(y1+1<=m && minDist[x1][y1+1]<=dist) {
    //     back_trace(n,m,x1,y1+1,x2,y2,minDist, ans, minDist[x1][y1+1]);
    // }
}

int main() {
    int n,m,k;
    cin>>n>>m>>k;

    vector<vector<int>> boomPos(k, vector<int>(2));
    for(int i=0;i<k;i++) {
        cin>>boomPos[i][0]>>boomPos[i][1];
    }

    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;

    vector<vector<int>> minDist(n+1, vector<int>(m+1, 5000));
    getMinDist(n,m,boomPos, minDist);

    for(vector<int> row: minDist) {
        for(int n1: row)
            cout<<n1<<" ";
        cout<<endl;
    }
    int ans=0;
    vector<vector<int>> flag(n+1, vector<int>(m+1, 0));
    back_trace(n,m,x1,y1,x2,y2,minDist, ans, 5000,flag);

    cout<<ans<<endl;

    return 0;
}