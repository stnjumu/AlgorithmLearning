#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<assert.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BinaryTree {
public:

};

// 重点：分层BFS，见102.；

// BFS返回拓展层次序
vector<int> getLevelOrderExpand(TreeNode* root, bool removeLastNULL = true) {
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；

    vector<int> ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();
        if(temp!=NULL) {
            ans.push_back(temp->val);
            q.push(temp->left);
            q.push(temp->right);
        }
        else {
            ans.push_back(-1);
        }
    }
    while(ans.back()==-1)
        ans.pop_back();
    return ans;
}
// BFS返回层次序
vector<int> getLevelOrder(TreeNode* root) {
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；

    vector<int> ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();
        ans.push_back(temp->val);
        if(temp->left!=NULL)
            q.push(temp->left);
        if(temp->right!=NULL)
            q.push(temp->right);
    }
    return ans;
}
void printLevelOrder(TreeNode* root, bool expand = true, string name = "binary tree") {
    vector<int> out;
    if(expand) {
        out = getLevelOrderExpand(root);
    }
    else {
        out = getLevelOrder(root);
    }
    if(expand) {
        name = name + "\'" + " Expanded" + " LevelOrder = ";
    }
    else {
        name = name + "\'" + " LevelOrder = ";
    }
    for(auto n: out)
        cout<< n<<" ";
    cout<<endl;
}
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

void printInOrderSubnet(TreeNode *r) {
	if (r==NULL)
		return;
	printInOrderSubnet(r->left);
	cout << r->val << " ";
	printInOrderSubnet(r->right);
}
void printInOrder(TreeNode *root, string name="binary tree") {
	cout << name << "\' InOrder = ";
	printInOrderSubnet(root);
    cout<<endl;
}

// 构造二叉树，拓展层次序：[1, -1, 2, 3] 
TreeNode *vectorIntLayerOrder2BinaryTree(vector<int> nums) {
	int n = nums.size();
	if (n == 0)
		return NULL;

	// BFS构建
	int i = 0;
	queue<TreeNode*> s; // 先进先出
	TreeNode* root = new TreeNode(nums[0]);
    s.push(root);
	i++;
	while(i<n && !s.empty()) {
		TreeNode* temp = s.front();
		s.pop();

		if(nums[i]!=-1) {
			temp->left = new TreeNode(nums[i]);
			s.push(temp->left);
		}
		i++;
		if(i<n && nums[i]!=-1) {
			temp->right = new TreeNode(nums[i]);
			s.push(temp->right);
		}
		i++;
	}
    return root;
}

void deleteBinaryTree(TreeNode *root) {
    if(root == NULL)
        return;
    
    deleteBinaryTree(root->left);
    deleteBinaryTree(root->right);
    delete root;
}
// 二叉树遍历有前、中、后(前中后是说root的位置在前中后)和层次序；单一一种遍历序列都不能唯一确定一棵树；
// 中序和其他任何一种遍历的组合都可唯一确定一棵树；其中中序和层次序的组合稍微复杂点，其他简单；
// 利用扩充二叉树(以特殊标志null节点)，则扩充的前、后序也可
// https://blog.csdn.net/K346K346/article/details/106332304