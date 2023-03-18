#include"DataStructure/BinaryTree.h"
#include<iostream>
using namespace std;

void back_trace_paths(vector<string> &ans, TreeNode* root, string &path) { // dfs
    // 遍历此节点
    int old_length = path.length();
    if(!path.empty())
        path.append("->");
    path.append(to_string(root->val));

    if(root->left == NULL && root->right == NULL) { // ! 结束条件和一般二叉树的dfs都不同，不能用root==NULL，路径的终点应为左右子节点都为NULL；
        ans.push_back(path);
    }
    else {
        if(root->left!=NULL)
            back_trace_paths(ans, root->left, path);
        if(root->right!=NULL)
            back_trace_paths(ans, root->right, path);
    }
    // back trace; 删除遍历本节点append的数字；
    // ! 如果path是引用或全局变量(随遍历位置动态变化的)，则需要erase; 但如果每层新构造一个string，则不需要删除；
    path.erase(old_length); // 等价于path.erase(path.begin()+old_length, path.end()); 删除到只剩old_length个字符；
}
// 257. 二叉树的所有路径
vector<string> getBinaryTreePaths(TreeNode* root) {
    if(root==NULL) {
        return {};
    }
    vector<string> ans;
    string path;
    back_trace_paths(ans, root, path);
    return ans;
}

int main() {
    TreeNode * root = vectorIntLayerOrder2BinaryTree({3,9, 20, -1, -1, 15, 7});
    printInOrder(root);
    printLevelOrder(root, true);
    printLevelOrder(root, false);
    vector<vector<int>> ans = getLevelOrder_EachLevel2(root);
    cout<<"层次序"<<endl;
    for(auto row: ans) {
        for(auto n:row) {
            cout<< n<<" ";
        }
        cout<<endl;
    }
    cout<<"锯齿层次序"<<endl;
    ans = getZigZagLevelOrder(root);
    for(auto row: ans) {
        for(auto n:row) {
            cout<< n<<" ";
        }
        cout<<endl;
    }
    deleteBinaryTree(root); // 注意root不是NULL，但已不能使用；

    root = vectorIntLayerOrder2BinaryTree({1,2,3,-1,5});
    printLevelOrder(root, true);
    vector<string> paths = getBinaryTreePaths(root);
    for(string s: paths) {
        cout<<"\""<< s <<"\",";
    }
    deleteBinaryTree(root);
}