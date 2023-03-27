#pragma once

#include"TreeNode.h"
// 判断二叉搜索树
// 思路1：沿中序遍历进行判断，遍历到的值只能递增；(已实现)
// 思路2：前序遍历每个节点，由根可得左右子树所有节点的一个范围；进行判断；
class Solution98 {
public:
	bool InOrderSubnet(TreeNode* r, vector<int>& now) {
		// now只记录一个值，即上一次遍历到的值；等价于一个int + bool，只要是不好判断什么是否遍历到第一个中序值；
		if (r == NULL)
			return true;
		if (InOrderSubnet(r->left, now) == false)
			return false;
		cout << r->val << endl;
		if (now.empty())
		{
			now.push_back(r->val);
		}
		else
		{
			if (now[0] >= r->val) {
				cout << now[0] << ">=" << r->val << endl;
				return false;
			}
			else
			{
				cout << now[0] << "<" << r->val << endl;
				now[0] = r->val;
			}
		}
		if (InOrderSubnet(r->right, now) == false)
			return false;
		return true;
	}
	bool isValidBST(TreeNode* root) {
		if (root == NULL)
			return true;
		vector<int> mem;
		return InOrderSubnet(root, mem);
	}
};