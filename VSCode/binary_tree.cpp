#include"DataStructure/BinaryTree.h"

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
}