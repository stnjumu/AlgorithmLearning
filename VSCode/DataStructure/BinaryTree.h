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

vector<vector<int>> getlevelOrder(TreeNode* root) {
    // BFS返回层次序的每层；
    if(root == NULL)
        return {}; // 注意不是{{}}，虽然两者输出一样，但{{}}的第一个vector不为空；
    
    vector<vector<int>> ans;
    queue<TreeNode*> s1, s2;
    s1.push(root);
    while(!s1.empty() || !s2.empty()) {
        vector<int> layer;
        if(!s1.empty()) {
            assert(s2.empty());

            while(!s1.empty()) {
                TreeNode *temp = s1.front();
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
                TreeNode *temp = s2.front();
                layer.push_back(temp->val);
                if(temp->left!=NULL)
                    s1.push(temp->left);
                if(temp->right!=NULL)
                    s1.push(temp->right);
                s2.pop();
            }
        }
        ans.push_back(layer);
    }
    return ans;
}

void printInOrderSubnet(TreeNode *r) {
	if (r==NULL)
		return;
	printInOrderSubnet(r->left);
	cout << r->val << " ";
	printInOrderSubnet(r->right);
}
void printInOrder(TreeNode *root, string name="binary tree") {
	cout << name << " = ";
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

// 二叉树遍历有前、中、后(前中后是说root的位置在前中后)和层次序；单一一种遍历序列都不能唯一确定一棵树；
// 中序和其他任何一种遍历的组合都可唯一确定一棵树；其中中序和层次序的组合稍微复杂点，其他简单；
// 利用扩充二叉树(以特殊标志null节点)，则扩充的前、后序也可
// https://blog.csdn.net/K346K346/article/details/106332304