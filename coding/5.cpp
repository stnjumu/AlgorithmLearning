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

int n;
const int N=100001;
vector<vector<int>> edges(N+1, vector<int>()); // edges[i] = {j1, j2, ...}表示无向边i-j1, i-j2
long long ans=0; // ! 注意结果输出一个数时，一定要用long long;
void dfs_Tree(int u, int par, int sub) {
    // 在不确定方向的Tree的某节点开始上dfs，确定到u距离
    int sub_subtree = u-sub-1;
    ans += sub_subtree;
    for (auto v : edges[u]) { // u-v
        if (v == par) {
            continue;
        }
        dfs_Tree(v, u, sub+sub_subtree);
    }
}
void solve() {
    cin>> n;
    edges.assign(n+1, vector<int>());

    for(int i=0;i<n-1;i++) {
        int u,v;
        cin>>u>>v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    ans =0;
    dfs_Tree(1,0,0);
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