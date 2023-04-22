#include"DataStructure/BinaryTree.h"
#include"DataStructure/Array.h"
#include<iostream>
#include<unordered_map>
using namespace std;

// 102. BFS返回层次序的每层；
// 思路1：两个队列 (我的实现)
// ! 思路2：每次只遍历队列中LayerSize个元素 (已实现)，我称为分层BFS;
vector<vector<int>> getLevelOrder_EachLevel(TreeNode* root) {
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；
    
    vector<vector<int>> ans;
    queue<TreeNode*> q1, q2;
    q1.push(root);
    while(!q1.empty() || !q2.empty()) {
        vector<int> layer;
        if(!q1.empty()) {
            assert(q2.empty());

            while(!q1.empty()) {
                TreeNode *temp = q1.front();
                layer.push_back(temp->val);
                if(temp->left!=NULL)
                    q2.push(temp->left);
                if(temp->right!=NULL)
                    q2.push(temp->right);
                q1.pop();
            }
        }
        else { // 一定要用else, 因为遍历s1时会使s2不为空；从而出错；
            assert(!q2.empty());

            while(!q2.empty()) {
                TreeNode *temp = q2.front();
                layer.push_back(temp->val);
                if(temp->left!=NULL)
                    q1.push(temp->left);
                if(temp->right!=NULL)
                    q1.push(temp->right);
                q2.pop();
            }
        }
        ans.push_back(layer);
    }
    return ans;
}
vector<vector<int>> getLevelOrder_EachLevel2(TreeNode* root) {
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；
    
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0; // 仅记录深度，本函数中没用；
    while(!q.empty()) {
        int layerSize = q.size();
        // 仅遍历当前层
        vector<int> layer;
        for(int i=0;i<layerSize;i++) {
            TreeNode* temp = q.front();
            q.pop();

            layer.push_back(temp->val);
            if(temp->left!=NULL)    
                q.push(temp->left);
            if(temp->right!=NULL)
                q.push(temp->right);
        }
        depth++;
        ans.push_back(layer);
    }
    return ans;
}
// 103. BFS返回锯齿形的层次序每层
// 思路1：两个栈 (我的实现)
// 思路2：同102思路2，
// 思路2.1: reverse深度为奇数的层的返回值即可；
// 思路2.2：利用双端队列deque, 深度为奇数的layer倒着遍历deque,倒着插；
vector<vector<int>> getZigZagLevelOrder(TreeNode* root) {
    // 已实现的法1：相对从左到右的顺序，需要改动两处：
    // 1. 把queue换成stack即可；
    // 2. s2将子网压入s1的顺序应该是先右子树，后左子树；(随便给个样例测试下就能发现)
    // 法2：把深度(从0开始)为奇数的layer reverse一下即可；
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；
    
    vector<vector<int>> ans;
    stack<TreeNode*> s1, s2; // 改动1
    s1.push(root);
    while(!s1.empty() || !s2.empty()) {
        vector<int> layer;
        if(!s1.empty()) {
            assert(s2.empty());

            while(!s1.empty()) {
                TreeNode *temp = s1.top();
                layer.push_back(temp->val);
                if(temp->left!=NULL)
                    s2.push(temp->left);
                if(temp->right!=NULL)
                    s2.push(temp->right);
                s1.pop();
            }
        }
        else { // 一定要用else, 因为遍历s1时会使s2不为空；从而出错；
            assert(!s2.empty());

            while(!s2.empty()) {
                TreeNode *temp = s2.top();
                layer.push_back(temp->val);
                if(temp->right!=NULL)  // 改动2，左右交换顺序；
                    s1.push(temp->right);
                if(temp->left!=NULL)
                    s1.push(temp->left);
                s2.pop();
            }
        }
        ans.push_back(layer);
    }
    return ans;
}
// 107. 层次序遍历2，按深度倒序返回，即ans中按照从低到顶，从左到右的顺序；将102.的结果reverse一下即可；
// 199. 二叉树的右视图：返回每层的最右边的值；分层BFS,但每层只返回最后一个节点的值即可；

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

// 94. 二叉树的中序遍历
vector<int> ansInorderTraversal;
void inorderTraversalSubtree(TreeNode* root) {
    if(root==NULL) {
        return;
    }
    inorderTraversalSubtree(root->left);
    ansInorderTraversal.push_back(root->val);
    inorderTraversalSubtree(root->right);
}
vector<int> inorderTraversal(TreeNode* root) {
    ansInorderTraversal.clear();
    inorderTraversalSubtree(root);
    return ansInorderTraversal;
}

// 101. 对称二叉树
// 击败36%, 45%
bool isSymmetricSubtree(TreeNode* leftSubtree, TreeNode* rightSubtree) {
    if(leftSubtree==NULL && rightSubtree==NULL) // 2个NULL
        return true;
    if(leftSubtree==NULL || rightSubtree==NULL) // 1个NULL
        return false;
    // 都不是NULL
    if(leftSubtree->val!=rightSubtree->val) {
        return false;
    }
    // 递归
    return isSymmetricSubtree(leftSubtree->left, rightSubtree->right) && isSymmetricSubtree(leftSubtree->right, rightSubtree->left);
}
bool isSymmetric(TreeNode* root) {
    return isSymmetricSubtree(root->left, root->right);
}

// 104. 二叉树的最大深度
// 击败93%, 89%
int ansMaxDepth;
void dfsMaxDepth(TreeNode* subtree, int depth) {
    if(subtree==NULL) {
        if(ansMaxDepth<depth)
            ansMaxDepth = depth;
        return;
    }

    dfsMaxDepth(subtree->left, depth+1);
    dfsMaxDepth(subtree->right, depth+1);
}
int maxDepth(TreeNode* root) {
    ansMaxDepth=0;
    dfsMaxDepth(root, 0);
    return ansMaxDepth;
}

// 114. 二叉树展开为链表
// 思路：跟着先序遍历的递归顺序构建新的Tree, 只需一个指针指向上一个节点，然后跟着先序顺序一次挂到上一个指针的右边即可；
// 注意：需要先用局部变量存了当前节点的左右子树指针后，才能把当前节点的left, right设为NULL；
// 击败89%, 51%
TreeNode *lastNode;
void preOrderFlatten(TreeNode* subtree) {
    if(lastNode == NULL)
        lastNode = subtree;
    else
        lastNode = lastNode->right=subtree;

    TreeNode *leftNode = subtree->left, *rightNode=subtree->right;
    lastNode->left=NULL;
    lastNode->right=NULL;
    if(leftNode!=NULL)
        preOrderFlatten(leftNode);
    if(rightNode!=NULL)
    preOrderFlatten(rightNode);
}
void flatten(TreeNode* root) {
    if(root==NULL)
        return;
    lastNode=NULL;
    preOrderFlatten(root);
}

// ! 124. 二叉树中的最大路径和
// 击败5%, 5%
// TODO: 改进：getG和GetSMax两者可以合到同一个dfs中去；
unordered_map<TreeNode*, int> G_maxPathSum;
int ans_maxPathSum;
void dfsGetG(TreeNode* subtree) {
    if(subtree==NULL)
        return;
    
    dfsGetG(subtree->left);
    dfsGetG(subtree->right);
    G_maxPathSum[subtree]=max({0, G_maxPathSum[subtree->left]+subtree->val, G_maxPathSum[subtree->right]+subtree->val});
}
void dfsGetSMax(TreeNode* subtree) {
    if(subtree==NULL)
        return;
    
    int ans = subtree->val + max(G_maxPathSum[subtree->left], 0) + max(G_maxPathSum[subtree->right], 0);
    if(ans>ans_maxPathSum)
        ans_maxPathSum=ans;

    dfsGetSMax(subtree->left);
    dfsGetSMax(subtree->right);
}
int maxPathSum(TreeNode* root) {
    G_maxPathSum.clear();
    G_maxPathSum[NULL]=0;
    dfsGetG(root);

    // ans_maxPathSum = 0; // 如果包含空路径； 
    ans_maxPathSum = INT_MIN; // 此题不包含空路径，即路径必须有一个节点；
    dfsGetSMax(root);
    return ans_maxPathSum;
}
// 改进；还是击败5%,5%
void dfsGetGAndSMax(TreeNode* subtree) {
    if(subtree==NULL)
        return;
    
    dfsGetGAndSMax(subtree->left);
    dfsGetGAndSMax(subtree->right);

    G_maxPathSum[subtree]=max({0, G_maxPathSum[subtree->left]+subtree->val, G_maxPathSum[subtree->right]+subtree->val});
    int ans = subtree->val + max(G_maxPathSum[subtree->left], 0) + max(G_maxPathSum[subtree->right], 0);
    if(ans>ans_maxPathSum)
        ans_maxPathSum=ans;
}
int maxPathSum2(TreeNode* root) {
    G_maxPathSum.clear();
    G_maxPathSum[NULL]=0;
    // ans_maxPathSum = 0; // 如果包含空路径； 
    ans_maxPathSum = INT_MIN; // 此题不包含空路径，即路径必须有一个节点；
    dfsGetGAndSMax(root);
    return ans_maxPathSum;
}
// 改进2；每个节点的Gain可以用返回值存，不用hashmap了
// 击败59%, 63%
int dfsGetGainAndAns(TreeNode* subtree) {
    if(subtree==NULL)
        return 0;
    
    int GainLeft = dfsGetGainAndAns(subtree->left);
    int GainRight = dfsGetGainAndAns(subtree->right);

    int GainRoot = max(0, max(GainLeft+subtree->val, GainRight+subtree->val));
    int ans = subtree->val + GainLeft + GainRight;
    if(ans>ans_maxPathSum)
        ans_maxPathSum=ans;
    return GainRoot;
}
int maxPathSum3(TreeNode* root) {
    ans_maxPathSum = INT_MIN; // 此题不包含空路径，即路径必须有一个节点；
    dfsGetGainAndAns(root);
    return ans_maxPathSum;
}

// 226. 翻转二叉树
// 递归，击败100%, 13%
TreeNode* invertTree(TreeNode* root) {
    if(root) {
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        swap(root->left, root->right);
    }
    return root;
}

// 236. 二叉树的最近公共祖先
// 思路：DFS判断节点所在子树中是否有P和Q，后序第一个同时有P,Q的节点就是解；
// 击败68%, 15%
// 可选优化，将pair<hasP, hasQ> 优化成一个即可，因为需要的只是hasP&&hasQ;
TreeNode* ansLowestCommonAncestor;
pair<bool, bool> DFSHasPQ(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL)
        return {false, false};
    bool hasP=false, hasQ=false;
    pair<bool, bool> hasPQ = DFSHasPQ(root->left, p, q);
    hasP = hasPQ.first;
    hasQ = hasPQ.second;
    hasPQ = DFSHasPQ(root->right, p, q);
    hasP = hasP || hasPQ.first;
    hasQ = hasQ || hasPQ.second;

    if(root == p)
        hasP = true;
    if(root == q)
        hasQ = true;

    // DFS后序中的第一个同时满足hasP == hasQ == true的节点就是解
    if(ansLowestCommonAncestor == NULL && hasP && hasQ)
        ansLowestCommonAncestor = root;
    
    return {hasP, hasQ};
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    ansLowestCommonAncestor = NULL;
    DFSHasPQ(root, p, q);
    return ansLowestCommonAncestor;
}

// 337. 打家劫舍III
// 击败99%, 85%
pair<int, int> robSubtree(TreeNode* root) {
    // 递归出口
    if(root==NULL) {
        return {0,0};
    }

    pair<int, int> maxLeftRobOrNot = robSubtree(root->left);
    pair<int, int> maxRightRobOrNot = robSubtree(root->right);
    pair<int, int> maxRootRobOrNot; // first表示偷root, second表示不偷root;
    // 偷root, 则不偷两个孩子；
    maxRootRobOrNot.first = maxLeftRobOrNot.second + maxRightRobOrNot.second + root->val;
    // 不偷root, 则可偷可不偷孩子；
    // ! 注意不一定两个孩子都偷是最大的；
    maxRootRobOrNot.second = max(maxLeftRobOrNot.first, maxLeftRobOrNot.second) + max(maxRightRobOrNot.first, maxRightRobOrNot.second);
    return maxRootRobOrNot;
}
int rob(TreeNode* root) {
    pair<int, int> maxRootRobOrNot = robSubtree(root);
    return max(maxRootRobOrNot.first, maxRootRobOrNot.second);
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
    cout<<endl;
    deleteBinaryTree(root);

    cout<<"二叉树的中序遍历"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,-1,2,3});
    printLevelOrder(root, true);
    printVector(inorderTraversal(root));
    deleteBinaryTree(root);

    cout<<"对称二叉树"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,2,2,3,4,4,3});
    printLevelOrder(root, true);
    cout<<isSymmetric(root)<<endl;
    deleteBinaryTree(root);
    
    root = vectorIntLayerOrder2BinaryTree({1,2,2,-1,3,-1,3});
    printLevelOrder(root, true);
    cout<<isSymmetric(root)<<endl;
    deleteBinaryTree(root);

    cout<<"二叉树的最大深度"<<endl;
    root = vectorIntLayerOrder2BinaryTree({3,9,20,-1,-1,15,7});
    printLevelOrder(root, true);
    cout<<maxDepth(root)<<endl;
    deleteBinaryTree(root);

    cout<<"从前序与中序遍历序列构造二叉树"<<endl;
    vector<int> preorder{3,9,20,15,7}, inorder{9,3,15,20,7};
    root = buildTree(preorder, inorder);
    printLevelOrder(root, true);
    deleteBinaryTree(root);
    
    preorder.assign({-1}); 
    inorder.assign({-1});
    root = buildTree(preorder, inorder); // ! 注意vectorIntLayerOrder2BinaryTree构建不支持-1做为节点；
    // printLevelOrder(root, true);
    printLevelOrder(root, false); // ! 注意我的printLevelOrderExpand不支持-1;
    deleteBinaryTree(root);

    cout<<"二叉树展开为链表"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,2,5,3,4,-1,6});
    printLevelOrder(root, true);
    flatten(root);
    printLevelOrder(root, true);
    deleteBinaryTree(root);

    cout<<"二叉树中的最大路径和"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,2,3});
    printLevelOrder(root, true);
    cout<<maxPathSum3(root)<<endl;
    deleteBinaryTree(root);

    root = vectorIntLayerOrder2BinaryTree({-10,9,20,-1,-1,15,7}); // 注意其中-1是特殊空结点标志；
    printLevelOrder(root, true);
    cout<<maxPathSum3(root)<<endl;
    deleteBinaryTree(root);

    root = vectorIntLayerOrder2BinaryTree({-3});
    printLevelOrder(root, true);
    cout<<maxPathSum3(root)<<endl;
    deleteBinaryTree(root);

    root = vectorIntLayerOrder2BinaryTree({3,5,1,6,2,0,8,-1,-1,7,4});
    printLevelOrder(root, true);
    cout<< lowestCommonAncestor(root, root->left, root->right)->val<<endl; // 5, 1的最近祖先为3
    cout<< lowestCommonAncestor(root, root->left, root->left->right->right)->val<<endl; // 5, 4的最近祖先是5
    deleteBinaryTree(root);

    cout<<"二叉树的序列化和反序列化"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,2,3,-1,-1,4,5});
    BinaryTreeCodec btcc;
    string ser = btcc.serialize(root);
    cout<<"序列化后: "<< ser<<endl;
    TreeNode *newRoot = btcc.deserialize(ser);
    printLevelOrderWithNullNum(newRoot, true, btcc.nullNum);
    deleteBinaryTree(root);
    deleteBinaryTree(newRoot);

    cout<<"打家劫舍III"<<endl;
    root = vectorIntLayerOrder2BinaryTree({3,2,3,-1,3,-1,1});
    cout<< rob(root)<<endl;
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({3,4,5,1,3,-1,1});
    cout<< rob(root)<<endl;
    deleteBinaryTree(root);

    return 0;
}