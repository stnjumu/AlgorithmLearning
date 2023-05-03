#include"DataStructure/Array.h"
#include<stack>
using namespace std;

// * 邻接表表示的图
// 即vector<vector<int>> graph; graph[i]表示节点i的邻接节点；(不容易表示有权图)

// 剑指 Offer II 110. 所有路径
// n个节点的DAG图，找出0->n-1的所有路径；dfs
// 击败95%, 91%
void dfsAllPathsSourceTarget(vector<vector<int>> &graph, vector<int> &path, int start, int end, vector<vector<int>> &ans) {
    // start即当前path下一步可能要走的点，end即目标节点；
    // 出口
    if(start==end) {
        // 最终节点
        path.push_back(end);
        ans.push_back(path);
        path.pop_back();
        return;
    }

    path.push_back(start);
    for(int node: graph[start]) {
        dfsAllPathsSourceTarget(graph, path, node, end, ans);
    }
    path.pop_back();
}
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    assert(graph.size()>=2);

    vector<int> path;
    vector<vector<int>> ans;
    dfsAllPathsSourceTarget(graph, path, 0, graph.size()-1, ans);
    return ans;
}

// * 边表示的图
// 即vector<vector<int>> edges; edges[i]若只有两个值，表示边edges[i][0]->edges[i][1]；可以有三个值(很少用)，边edges[i][0]->edges[i][1]和边权重edges[i][2]

// 207. 课程表
// 判断是否是DAG
// 思路1：DFS判环，无环就行；击败9%, 97%;
bool DFSCanFinish(int course , vector<int> &color, vector<vector<int>> &prerequisites) {
    color[course]=1; // 开始遍历；
    for(vector<int> &edge: prerequisites) {
        if(edge[0]==course) {
            if(color[edge[1]]==1) // 有回边
                return false;
            else if(color[edge[1]] == 0) { // 没有遍历过；
                if(DFSCanFinish(edge[1], color, prerequisites)==false)
                    return false;
            }
            // else 2, 已经遍历过；
        }
    }
    color[course]=2;
    return true;
}
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> color(numCourses, 0);
    bool flag = true;
    // DFS判断环
    for(int i=0;i<numCourses;++i) {
        if(color[i]==0) {
            flag = DFSCanFinish(i, color, prerequisites);
            if(flag == false)
                return false;
        }
    }
    return true;
}

// DAG的拓扑排序，BFS/DFS即可
// 击败9%, 95%
vector<int> ansFindOrder;
// 已实现，DFS后序入栈即可；
bool DFSFindOrder(int course , vector<int> &color, vector<vector<int>> &prerequisites) {
    color[course]=1; // 开始遍历；
    // 前序处理 ...

    for(vector<int> &edge: prerequisites) {
        if(edge[0]==course) {
            if(color[edge[1]]==1) // 有回边
                return false;
            else if(color[edge[1]] == 0) { // 没有遍历过；
                if(DFSFindOrder(edge[1], color, prerequisites)==false)
                    return false;
            }
            // else 2, 已经遍历过；
        }
    }

    color[course]=2;
    // 后序处理:
    ansFindOrder.push_back(course);

    return true;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    ansFindOrder.clear();
    vector<int> color(numCourses, 0);
    bool flag = true;
    // DFS判断环
    for(int i=0;i<numCourses;++i) {
        if(color[i]==0) {
            flag = DFSFindOrder(i, color, prerequisites);
            if(flag == false)
                return {};
        }
    }
    return ansFindOrder;
}

// * 邻接矩阵表示的图
// 即n*n的矩阵vector<vector<int/bool>> graph; graph[i][j]若为bool则表示i->j的边是否存在， 若为int则可表示i->j的边权重；

// Dijkstra算法，非负权值图的单源最短路径
// 输入邻接矩阵表示的无向图G, G[i][j]表示i到j的距离(0, 100)之间，INF=5000, 若距离==INT则表示没有路径；也有用-1表示没有路径的；
// 输入源节点s, 目标节点t, 求s->t的最短路径长度和最短路径(下标表示即可)；若不存在返回{-1, {}}
// 实现：遍历法获取未访问的节点中距离s最近的节点，O(n)；
// Dijkstra最坏情况需访问所有节点，每次O(n)选取未访问节点中距离s最近节点，共O(n^2)
// 可选优化：优先队列(二叉堆实现，二项堆实现，斐波那契堆实现)， 每次选最近需要涉及一次优先队列的获取最小和删除最小，k次更新key；
//      以二叉堆为例， 获取最小O(1), 删除最小O(logn), k次更新key，k*O(logn); n*k约为m级别(所有边)
//      n*(1+logn+k*logn) = O(nlogn+ nklogn) = O((n+m)logn)
// 边比较少时使用优先队列优化较好；
const int INF_SSSP = 5000;
pair<int, vector<int> > dijkstraGetSSSP_adjacenyMatrix(vector<vector<int>> G, int s, int t) {
    // G[i][j]==INF_SSSP表示无路径；
    // G为n*n方阵，n>=2, G[i][j]>0, s, t为节点下标，in [0, n)
    int n = G.size();
    assert(n==G[0].size());
    if(s==t)
        return {0, {s}};

    vector<bool> visit(n, false); // 是否访问过
    vector<int> dist(n, INF_SSSP); // 仅经过所有visit过的节点，所有节点到s的最短路径长度，初始化为无穷大；
    vector<int> prev(n, -1); // 求得的最短路径中，prev[i]表示i由prev[i]达到，即prev[i]->i，用于反向得到最短路径；
    
    dist[s]=0; // 起始点；下面第一轮循环一定选中s

    while(visit[t]==false) {
        // 贪心地选择距离s最近的未访问节点；
        int node = -1;
        for(int i=0;i<n;i++) {
            // * 下面判断条件很重要；
            if(visit[i]==false && dist[i]<INF_SSSP && (node==-1 || dist[node]>dist[i])) {
                node = i;
            }
        }
        if(node == -1) {
            // 没有可达节点
            return {-1, {}};
        }

        // 选中node, 更新node相连的未访问的节点的dist
        visit[node]=true;
        for(int j=0;j<n;j++) {
            // node -> j
            if(G[node][j]<INF_SSSP && visit[j]==false && dist[j]>dist[node]+G[node][j]) { // 有路径, 未选中，路径可更新；
                dist[j] = dist[node]+G[node][j];
                prev[j]=node;
            }
        }
    }
    
    // 反向获取路径；要求s,t不重合；
    vector<int> path;
    path.push_back(t);
    int back=t;
    while(prev[back]!=-1) {
        path.push_back(prev[back]);
        back = prev[back];
    }
    // 翻转路径即为解；
    reverse(path.begin(), path.end());

    return {dist[t], path};
}

int main() {
    cout<<"课程表"<<endl;
    vector<vector<int>> prerequisites{{1,0}};
    cout<<canFinish(2, prerequisites)<<endl;

    prerequisites.assign({{1,0}, {0,1}});
    cout<<canFinish(2, prerequisites)<<endl;

    prerequisites.assign({{1,4},{2,4},{3,1},{3,2}});
    cout<<canFinish(5, prerequisites)<<endl;
    
    prerequisites.assign({{1,0}});
    printVector(findOrder(2, prerequisites));

    prerequisites.assign({{1,0}, {0,1}});
    printVector(findOrder(2, prerequisites));

    prerequisites.assign({{1,4},{2,4},{3,1},{3,2}});
    printVector(findOrder(5, prerequisites));

    cout<<"所有路径"<<endl;
    vector<vector<int>> graph{{1,2},{3},{3},{}};
    printVectorVector(allPathsSourceTarget(graph));

    cout<<"dijkstra求最短路径"<<endl;
    graph.assign({
        {0,5,2,INF_SSSP,INF_SSSP,INF_SSSP,INF_SSSP},
        {5,0,INF_SSSP,1,6,INF_SSSP,INF_SSSP},
        {2,INF_SSSP,0,6,INF_SSSP,8,INF_SSSP},
        {INF_SSSP,1,6,0,1,2,INF_SSSP},
        {INF_SSSP,6,INF_SSSP,1,0,INF_SSSP,7},
        {INF_SSSP,INF_SSSP,8,2,INF_SSSP,0,3},
        {INF_SSSP,INF_SSSP,INF_SSSP,INF_SSSP,7,3,0}
    });
    pair<int, vector<int>> distPath= dijkstraGetSSSP_adjacenyMatrix(graph, 0, 6);
    cout<< distPath.first<<endl; // 11
    printVector(distPath.second); // 0 1 3 5 6

    distPath= dijkstraGetSSSP_adjacenyMatrix(graph, 0, 4);
    cout<< distPath.first<<endl; // 7
    printVector(distPath.second); // 0 1 3 4

    return 0;
}