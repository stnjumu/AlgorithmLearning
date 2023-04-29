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

// 拓扑排序，BFS/DFS即可
// 击败9%, 95%
vector<int> ansFindOrder;
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

    return 0;
}