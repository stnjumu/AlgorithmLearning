#include"DataStructure/BinaryTree.h"

int main() {
    TreeNode * root = vectorIntLayerOrder2BinaryTree({3,9, 20, -1, -1, 15, 7});
    printInOrder(root);
    vector<vector<int>> ans = getlevelOrder(root);
    for(auto row: ans) {
        for(auto n:row) {
            cout<< n<<" ";
        }
        cout<<endl;
    }
}