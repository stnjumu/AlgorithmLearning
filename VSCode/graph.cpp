#include"DataStructure/Array.h"
#include<stack>
using namespace std;

// * 邻接表表示的图

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

    return 0;
}