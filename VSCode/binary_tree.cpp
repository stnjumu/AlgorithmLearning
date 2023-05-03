#include"DataStructure/BinaryTree.h"
#include"DataStructure/Array.h"
#include<iostream>
#include<unordered_map>
using namespace std;

/*
常用方法有
1. 后序遍历 (递归)
    要求Tree的一些值或性质，抽象成dfs(root)函数，后序遍历是先dfs(left), dfs(right), 再递推root;
    注意递归出口即可；一般任务可递归到NULL, 而有些特殊任务只能递归到叶子节点，否则可能这条路径形成两个解，见112. 路径总和, 113. 路径总和II, 437. 路径总和III
        注意递归到叶子节点有时也要考虑root==NULL情况，只是不是解而已；
*/

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
// 思路3: 分层遍历BFS+2个栈；奇数层(从0开始)先遍历左子，偶数层先遍历右子，压入临时栈中，一层遍历完后swap两个栈即可；

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
// * 注意：需要先用局部变量存了当前节点的左右子树指针后，才能把当前节点的left, right设为NULL；
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

// ! 124. 二叉树中的最大路径和 (任意路径)
// 击败5%, 5%
// TODO: 改进：getG和GetSMax两者可以合到同一个dfs中去；
// 分析：可以先定义单向路径sp, 双向路径dp, sp(root)表示以root为端点向下的路径；dp(root)表示root子树中经过root的路径；
// 注：这里的单向路径和双向路径是我自己为解释此题定义，非通用称呼；
// 显然有dp(root) = sp(left) + sp(right) + root.val
// max{dp(root)} = max{sp(left)} + max{sp(right)} + root.val
// 所求即for all node in Tree, max{max{dp(root)}};
// 所有节点的max{sp(node)}可以在一次后序遍历过程中求得，而max(dp(root))在获得max{sp(left)}, max{sp(right)}后可以马上得到，由此可知所有node的max{dp(node)}在一次后序遍历中可得；
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
// ! 不可以将pair<hasP, hasQ> 优化成一个，虽然需要的只是hasP&&hasQ; 
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
// 想要优化的版本, 但并没有改进； 击败68%, 15%, 
pair<bool, bool> DFSHasPQ_better(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL)
        return {false, false};
    if(ansLowestCommonAncestor!=NULL) {
        // 已有解，之后所有都不需要遍历了；
        return {true, true};
    }

    bool hasP=false, hasQ=false;
    pair<bool, bool> hasPQ = DFSHasPQ_better(root->left, p, q);
    hasP = hasPQ.first;
    hasQ = hasPQ.second;
    
    if(ansLowestCommonAncestor!=NULL) {
        // 已有解，之后所有都不需要遍历了；
        return {true, true};
    }

    hasPQ = DFSHasPQ_better(root->right, p, q);
    hasP = hasP || hasPQ.first;
    hasQ = hasQ || hasPQ.second;

    if(ansLowestCommonAncestor!=NULL) {
        // 已有解，之后所有都不需要遍历了；
        return {true, true};
    }

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
// * 求二叉树中两个节点间的最短路径 (需要返回长度和路径)
// 如果可以的话，可以构造一个无向图然后用dfs求；
// 如果只能在二叉树上求的话，只能使用类似于二叉树的最近公共祖先的方法了
vector<TreeNode*> pathSSSP_partP; // p->祖先
vector<TreeNode*> pathSSSP_partQ; // q->祖先
pair<bool, bool> DFSHasPQAndGetPath(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL)
        return {false, false};
    bool hasP=false, hasQ=false;
    pair<bool, bool> hasPQ = DFSHasPQAndGetPath(root->left, p, q);
    hasP = hasPQ.first;
    hasQ = hasPQ.second;
    // TODO: 下面这种方法总感觉不太符合直觉，虽然它很正确；寻找有没有更好思路？
    // ! 如果没有下面这个判断，则最近祖先->整个树的root都会压入到两个vector中；
    if(!hasP || !hasQ) { // P, Q不同时在左子树中
        hasPQ = DFSHasPQAndGetPath(root->right, p, q);
        hasP = hasP || hasPQ.first;
        hasQ = hasQ || hasPQ.second;

        if(root == p)
            hasP = true;
        if(root == q)
            hasQ = true;
        
        // 插入到路径中, p->祖先, q->祖先
        if(hasP)
            pathSSSP_partP.push_back(root);
        if(hasQ)
            pathSSSP_partQ.push_back(root);
    }
    // else P, Q都在左子树中，可以不遍历右子树和root了；
    return {hasP, hasQ};
}
vector<TreeNode*> SSSPOnBinaryTree(TreeNode* root, TreeNode* p, TreeNode* q) {
    pathSSSP_partP.clear();
    pathSSSP_partQ.clear();
    DFSHasPQAndGetPath(root, p, q);
    pathSSSP_partP.pop_back(); // 祖先出现两次；
    // 反向插入尾部；
    while(!pathSSSP_partQ.empty()) {
        pathSSSP_partP.push_back(pathSSSP_partQ.back());
        pathSSSP_partQ.pop_back();
    }
    return pathSSSP_partP;
    // * pathSSSP_partP.size()即为路径长度；
}

// 337. 打家劫舍III
// 屋子成二叉树排列，不能同时偷相邻的两个屋子，问能偷的最大金额；
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
    // 返回值first表示偷root能得到的最大值，second表示不偷root能得到的最大值；
    return maxRootRobOrNot;
}
int rob(TreeNode* root) {
    pair<int, int> maxRootRobOrNot = robSubtree(root);
    return max(maxRootRobOrNot.first, maxRootRobOrNot.second);
}

// 112. 路径总和 (根到叶子节点的路径)
// 击败83%, 91%
bool dfsHasPathSum(TreeNode* subtree, int target) {
    // 出口
    // ! 下面有误；递归出口应该是叶子节点，而不是NULL; 反例root = [1,2], target = 1;
    // if(subtree==NULL) {
    //     if(target==0)
    //         return true;
    //     else
    //         return false;
    // }
    if(subtree == NULL) return false;
    if(subtree->left==NULL && subtree->right==NULL) {
        if(target==subtree->val) return true;
        else return false;
    }

    return dfsHasPathSum(subtree->left, target-subtree->val)
            || dfsHasPathSum(subtree->right, target-subtree->val);
}
bool hasPathSum(TreeNode* root, int targetSum) {
    if(root==NULL)
        return false;
    
    return dfsHasPathSum(root, targetSum);
}

// 113. 路径总和II (根到叶子节点的路径, 需要给出路径)
// 击败75%, 74%
void dfsPathSumII(TreeNode* subtree, int targetSum, vector<int> &path, int pathSum, vector<vector<int>> &ans) {
    // 出口
    if(subtree==NULL) return;
    if(subtree->left==NULL && subtree->right==NULL) { // 叶子节点
        if(pathSum+subtree->val==targetSum) {
            path.push_back(subtree->val);
            ans.push_back(path);
            path.pop_back();
        }
        return;
    }

    path.push_back(subtree->val);
    dfsPathSumII(subtree->left, targetSum, path, pathSum+subtree->val, ans);
    dfsPathSumII(subtree->right, targetSum, path, pathSum+subtree->val, ans);
    path.pop_back();
}
vector<vector<int>> pathSumII(TreeNode* root, int targetSum) {
    if(root == NULL)
        return {};
    
    vector<vector<int>> ans;
    vector<int> path;
    dfsPathSumII(root, targetSum, path, 0, ans);
    return ans;
}

// 437. 路径总和III
// 注意此题中路径只包括从祖先节点到子孙节点的路径；
int ans;
// ! BUG: 前序递归遍历, 下面写法有问题，见例子2，其实是因为此种遍历方法会导致每个节点做为起点遍历多次；
void preOrderPathSum(TreeNode* root, int targetSum, int pathSum) {
    // if(targetSum==pathSum) { // ! 使用此句有bug，会导致计数两次；因为到此层之前就和为targetSum, 会遍历左右子树，所以两次；
    if(root == NULL) {
        return;
    }
    if(targetSum==pathSum+root->val) {
        ans++;
        return;
    }

    // 节点有正有负，需要遍历到叶子，不能剪枝；
    // 延续之前
    preOrderPathSum(root->left, targetSum, pathSum+root->val);
    preOrderPathSum(root->right, targetSum, pathSum+root->val);

    // 从子节点开始
    preOrderPathSum(root->left, targetSum, 0);
    preOrderPathSum(root->right, targetSum, 0);
}
int pathSumERROR(TreeNode* root, int targetSum) {
    ans = 0;
    preOrderPathSum(root, targetSum, 0);
    return ans;
}
// 标答1
// O(n^2), 击败32%, 83%
int rootPathSum(TreeNode* subtree, long long targetSum) { // ! targetSum在迭代过程中可能超出int;
    int ans=0;
    if(subtree==NULL) return 0; // 出口
    if(targetSum==subtree->val) ans++; // 注意不能targetSum==0才统计，因为解的左右子树会统计两次；注意不能return;

    ans+=rootPathSum(subtree->left, targetSum-subtree->val);
    ans+=rootPathSum(subtree->right, targetSum-subtree->val);
    return ans;
}
int pathSum(TreeNode* root, int targetSum) {
    if(root == NULL) return 0; // 出口；
    // 统计树中解的个数，包含以下两部分：
    // 1. 统计以root为路径端点的路径中和为target的个数；
    int ans = rootPathSum(root, targetSum);
    
    // 2. 递归统计以其他节点为端点的路径中解的个数
    ans += pathSum(root->left, targetSum);
    ans += pathSum(root->right, targetSum);
    return ans;
}
// TODO: 标答2: O(n), 前缀和，融入整个DFS遍历过程，细节要求很多。

// 543. 二叉树的直径
// 击败95%, 64%
int ansDiameterOfBinaryTree;
int dfsPostOrderGetRootToLeafMaxLen(TreeNode* subtree) {
    // 返回子树根到叶子节点最长路径节点数；
    if(subtree==NULL)
        return 0;
    
    int leftLen = dfsPostOrderGetRootToLeafMaxLen(subtree->left);
    int rightLen = dfsPostOrderGetRootToLeafMaxLen(subtree->right);
    // Post Order
    // 子树的过根的最长路径= leftLen(节点数) + rightLen(节点数);
    if(leftLen + rightLen > ansDiameterOfBinaryTree)
        ansDiameterOfBinaryTree= leftLen+rightLen;
    return max(leftLen, rightLen)+1;
}
int diameterOfBinaryTree(TreeNode* root) {
    ansDiameterOfBinaryTree=0;
    dfsPostOrderGetRootToLeafMaxLen(root);
    return ansDiameterOfBinaryTree;
}

// 617. 合并二叉树
// 击败%9, %5;
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if(root1 == NULL && root2==NULL)
        return NULL;
    
    TreeNode *root = new TreeNode(0);
    // if(root1!=NULL)
    //     root->val += root1->val;
    // if(root2!=NULL)
    //     root->val += root2->val;
    root->val = (root1==NULL? 0: root1->val) + (root2==NULL?0:root2->val);
    
    // ! root1 或 root2可能为NULL
    // 使用?:操作符可以方便运算；
    root->left = mergeTrees(root1==NULL? NULL: root1->left, root2==NULL? NULL: root2->left);
    root->right = mergeTrees(root1==NULL? NULL: root1->right, root2==NULL? NULL: root2->right);
    return root;
}
// TODO: 要求使用root1和root2的节点进行合并，同时存在则delete其中的一个空间；
// ! 注：这种合并方式不是构造新树，需要和上层的回收树空间的代码进行配合，否则可能delete一处空间多次；

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

    cout<<"二叉树的最近公共祖先"<<endl;
    root = vectorIntLayerOrder2BinaryTree({3,5,1,6,2,0,8,-1,-1,7,4});
    printLevelOrder(root, true);
    cout<< lowestCommonAncestor(root, root->left, root->right)->val<<endl; // 5, 1的最近祖先为3
    cout<< lowestCommonAncestor(root, root->left, root->left->right->right)->val<<endl; // 5, 4的最近祖先是5
    deleteBinaryTree(root);

    cout<<"二叉树上最短路径"<<endl;
    root = vectorIntLayerOrder2BinaryTree({3,5,1,6,2,0,8,-1,-1,7,4});
    vector<TreeNode*> pathSSSP = SSSPOnBinaryTree(root, root->left->left, root->left->right->right); // 6, 7的最短路径：6, 5, 2, 4
    cout<<"最短路径= ";
    for(TreeNode* node: pathSSSP)
        cout<<node->val<<" ";
    cout<<endl;
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

    cout<<"路径总和"<<endl;
    root = vectorIntLayerOrder2BinaryTree({5,4,8,11,-1,13,4,7,2,-1,-1,-1,1});
    printBool(hasPathSum(root, 22));
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,2,3});
    printBool(hasPathSum(root, 5));
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,2});
    printBool(hasPathSum(root, 1));
    deleteBinaryTree(root);

    cout<<"路径总和II"<<endl;
    root = vectorIntLayerOrder2BinaryTree({5,4,8,11,-1,13,4,7,2,-1,-1,-1,5,1});
    printVectorVector(pathSumII(root, 22));
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,2,3});
    printVectorVector(pathSumII(root, 5));
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,2});
    printVectorVector(pathSumII(root, 1));
    deleteBinaryTree(root);


    cout<<"路径总和III"<<endl;
    root = vectorIntLayerOrder2BinaryTree({10,5,-3,3,2,INT_MIN,11,3,-2,INT_MIN,1}, INT_MIN);
    cout<<pathSumERROR(root, 8)<<endl;
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,-2,-3,1,3,-2,INT_MIN,-1}, INT_MIN);
    cout<<"Wrong Ans:"<<pathSumERROR(root, 3)<<", 应为1"<<endl;
    deleteBinaryTree(root);
    cout<<"路径总和III: 标答"<<endl;
    root = vectorIntLayerOrder2BinaryTree({10,5,-3,3,2,INT_MIN,11,3,-2,INT_MIN,1}, INT_MIN);
    cout<<pathSum(root, 8)<<endl;
    deleteBinaryTree(root);
    root = vectorIntLayerOrder2BinaryTree({1,-2,-3,1,3,-2,INT_MIN,-1}, INT_MIN);
    cout<<pathSum(root, 3)<<endl;
    deleteBinaryTree(root);

    cout<<"二叉树的直径"<<endl;
    root = vectorIntLayerOrder2BinaryTree({1,2,3,4,5});
    cout<<diameterOfBinaryTree(root)<<endl;

    cout<<"合并二叉树"<<endl;
    TreeNode *root1 = vectorIntLayerOrder2BinaryTree({1,3,2,5});
    TreeNode *root2 = vectorIntLayerOrder2BinaryTree({2,1,3,-1,4,-1,7});
    root = mergeTrees(root1,root2);
    printLevelOrder(root);
    deleteBinaryTree(root);
    deleteBinaryTree(root1);
    deleteBinaryTree(root2);

    return 0;
}