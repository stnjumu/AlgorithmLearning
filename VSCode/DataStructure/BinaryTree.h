#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<assert.h>
#include<sstream>
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
// ! 本文件所有Expand都默认-1是特殊标志；标志这里是空子树；这导致本文件现有Expand函数不支持-1做为节点；
// 之后可以换成INT_MIN
vector<int> getLevelOrderExpand(TreeNode* root, bool removeLastNULL = true, int nullNum = -1) {
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
            ans.push_back(nullNum);
        }
    }
    while(ans.back()==nullNum)
        ans.pop_back();
    return ans;
}

// * BFS返回层次序
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
    cout<<name;
    for(auto n: out)
        cout<< n<<" ";
    cout<<endl;
}
void printLevelOrderWithNullNum(TreeNode* root, bool expand = true, int nullNum = -1, string name = "binary tree") {
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
    cout<<name;
    for(auto n: out)
        cout<< n<<" ";
    cout<<endl;
}

// * 中序遍历
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


// * 反中序遍历；
void printReverseInOrderSubnet(TreeNode* bstRoot) {
    if(bstRoot==NULL)
        return;
    
    printReverseInOrderSubnet(bstRoot->right);
    cout<< bstRoot->val<<" ";
    printReverseInOrderSubnet(bstRoot->left);
}
void printReverseInOrder(TreeNode *root, string name="binary tree") {
	cout << name << "\' ReverseInOrder = ";
	printReverseInOrderSubnet(root);
    cout<<endl;
}

// 构造二叉树，拓展层次序：[1, -1, 2, 3] 
TreeNode *vectorIntLayerOrder2BinaryTree(vector<int> nums, int nullNum = -1) {
	int n = nums.size();
	if (n == 0)
		return NULL;

	// BFS构建
	int i = 0;
	queue<TreeNode*> q; // 先进先出
	TreeNode* root = new TreeNode(nums[0]);
    q.push(root);
	i++;
	while(i<n && !q.empty()) {
		TreeNode* temp = q.front();
		q.pop();

		if(nums[i]!=nullNum) {
			temp->left = new TreeNode(nums[i]);
			q.push(temp->left);
		}
		i++;
		if(i<n && nums[i]!=nullNum) {
			temp->right = new TreeNode(nums[i]);
			q.push(temp->right);
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

// 105. 由前序和中序遍历序列构造二叉树；
// 击败47%, 63%
TreeNode* buildSubtreeByPreOrderAndInorder(vector<int> &preorder, int prestart, vector<int> &inorder, int instart, int len) {
    if(len==0)
        return NULL;
    
    // 前序第一个就是root;
    TreeNode *root = new TreeNode(preorder[prestart]);
    // 寻找中序中root位置i
    int i=instart;
    while(i<instart+len) {
        if(inorder[i]==preorder[prestart])
            break;
    
        ++i;
    }
    assert(i!=instart+len); // 一定找到；
    int leftLen = i-instart;
    int rightLen = len - leftLen -1;
    // 分别构造左右子树；
    root->left = buildSubtreeByPreOrderAndInorder(preorder, prestart+1, inorder, instart, leftLen); // 左边leftLen个
    root->right = buildSubtreeByPreOrderAndInorder(preorder, prestart+leftLen+1, inorder, i+1, rightLen); // 右边rightLen个；
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildSubtreeByPreOrderAndInorder(preorder, 0, inorder, 0, inorder.size());
}

// 297. 二叉树的序列化和反序列化
// 击败81%, 88%
class BinaryTreeCodec {
public:
    int nullNum = -10000;
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<int> leverOrder = getLevelOrderExpand(root, true, nullNum); // 题目给定节点在[-1000, 1000]之间
        ostringstream out;
        out<<"[";
        for(int i=0;i<leverOrder.size();i++) {
            out<<leverOrder[i];
            if(i+1!=leverOrder.size())
                out<<",";
        }
        out<<"]";
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> nums;
        istringstream in(data);
        char delimiter;
        in>> delimiter;
        if(delimiter=='[') {
            int a=nullNum;
            while(in>>a) { // 能够读取到整数；
                nums.push_back(a);
                in>>delimiter;
            }
            return vectorIntLayerOrder2BinaryTree(nums, nullNum); // nullNum代表空节点；
        }
        else {
            cout<<"序列化的二叉树格式不符合[1,2,...,n]的格式要求!"<<endl;
            return NULL;
        }
    }
};