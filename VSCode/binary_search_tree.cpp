#include"DataStructure/Array.h"
#include"DataStructure/BinaryTree.h"
#include<numeric>

// 96. 不同的二叉搜索树
int numTrees(int n) { // n>=1
    // dp, dp[n]表示解，dp[n]=\sum_i (dp[i-1]*dp[n-i]); 以i为根，左子树个数*右子树个数；
    vector<int> dp(n+1,0);
    dp[0]=1; // 利于计算；
    dp[1]=1; // 选1为根，左右都是空，只有一种，但dp[0]*dp[0]=1; 也可以并到循环中；
    for(int i=2;i<=n;++i) {
        for(int j=1;j<=i;++j) {
            dp[i]+=dp[j-1]*dp[i-j];
        }
    }
    return dp[n];
}

// 538. 把二叉搜索树转换为累加树
// 思路1：使用O(n)额外空间存每个节点，求后缀和后再次遍历，击败38%, 5%;
void dfsInOrder(TreeNode* bstRoot, vector<int> &out) {
    if(bstRoot==NULL)
        return;
    
    dfsInOrder(bstRoot->left, out);
    out.push_back(bstRoot->val);
    dfsInOrder(bstRoot->right, out);
}
void dfsInOrderChangeNode(TreeNode* bstRoot, vector<int> &in, int &start) {
    // 还可反中序遍历，即先右子树再根，再左子树，得到的是反序的中序遍历；
    if(bstRoot==NULL)
        return;
    
    dfsInOrderChangeNode(bstRoot->left, in, start);
    assert(start<in.size());
    bstRoot->val = in[start];
    start++;
    dfsInOrderChangeNode(bstRoot->right, in, start);
}
TreeNode* convertBST(TreeNode* root) {
    vector<int> inOrderNums;
    dfsInOrder(root, inOrderNums);
    // printVector(inOrderNums);
    // inOrderNums为以root为根的BST的中序遍历，应为升序数组；
    // 所求即升序数组的后缀和；
    for(int i=int(inOrderNums.size())-2;i>=0;--i) {
        inOrderNums[i]+=inOrderNums[i+1];
    }
    // printVector(inOrderNums);
    int start = 0;
    dfsInOrderChangeNode(root, inOrderNums, start);
    return root;
}
// 改进但不好理解：反中序遍历得到降序序列，求前缀和后再中序遍历更改节点，每次更改使用队尾元素替换，再pop_back();
// 进一步可得到标答1：反中序遍历，遍历顺序即降序，所以可以直接用一个整型存前缀和后更改当前节点；可以在一次遍历结束；
// 但反中序遍历如果使用栈的话，需要O(n)的额外栈空间，所以仍为O(n), O(n);
// 击败61%, 47%
int partialSum;
void dfsReverseInOrder(TreeNode* bstRoot) {
    if(bstRoot == NULL)
        return;
    
    dfsReverseInOrder(bstRoot->right);
    partialSum += bstRoot->val;
    bstRoot->val = partialSum;
    dfsReverseInOrder(bstRoot->left);
}
TreeNode* convertBST2(TreeNode* root) {
    partialSum = 0;
    dfsReverseInOrder(root);
    return root;
}
// TODO: 最优：Morris 遍历, O(n), O(1);
// Morris遍历是迭代式O(n)时间，O(1)空间的中序遍历；非常强；

int main() {
    cout<< "不同的二叉搜索树"<<endl;
    cout<<numTrees(3)<<endl;
    cout<<numTrees(1)<<endl;

    cout<<"把二叉搜索树转换为累加树"<<endl;
    TreeNode *root = vectorIntLayerOrder2BinaryTree({4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8});
    printInOrder(root);
    printReverseInOrder(root);
    printLevelOrder(convertBST2(root));
    deleteBinaryTree(root);

    return 0;
}