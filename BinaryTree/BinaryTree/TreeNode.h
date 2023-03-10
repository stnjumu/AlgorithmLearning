#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 构造二叉树，拓展层次序：[1, -1, 2, 3] 
TreeNode *vectorInt2BinaryTree(vector<int> nums);
void printInOrder(TreeNode *root, string name = "BinaryTree");
// C++语法：默认参数可以在声明或定义时给定默认值，但不能同时在声明和定义时都给定默认值；
// 如果在声明和定义之间使用该函数的默认参数，则需要在声明中给定默认值，否则编译不通过；
// https://blog.csdn.net/kanglongyao/article/details/47184593
