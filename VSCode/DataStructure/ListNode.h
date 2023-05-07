#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

/*
    LeetCode常用的单链表节点定义；
    我提供了一些常用单链表基本函数；
	快慢指针判断链表是否有环的算法称为：Floyd判圈法，又称龟兔赛跑算法
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* vector2List(vector<int> v) {
	ListNode *head = NULL, *tail = NULL;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (head == NULL)
		{
			head = tail = new ListNode(v[i]);
		}
		else
		{
			tail->next = new ListNode(v[i]);
			tail = tail->next;
		}
	}
	return head;
}
pair<ListNode*, ListNode*> vector2List_ReturnHeadAndTail(vector<int> v) {
	ListNode *head = NULL, *tail = NULL;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (head == NULL)
		{
			head = tail = new ListNode(v[i]);
		}
		else
		{
			tail->next = new ListNode(v[i]);
			tail = tail->next;
		}
	}
	return {head, tail};
}

int getListSize(ListNode* head) {
	int n = 0;
	while (head != NULL)
	{
		head = head->next;
		n++;
	}
	return n;
}

void printList(ListNode* head, string name = string("list")) {
	cout << name << " = ";
	while (head!=NULL)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

void deleteList(ListNode *head) {
	ListNode *del = head;
	while (head!=NULL)
	{
		del = head;
		head = head->next;
		delete del;
	}
}

// 剑指 Offer 18. 删除链表的节点
// 击败87%, 68%
ListNode* deleteNode(ListNode* head, int val, bool onlyDeleteFirst = false) {
	// 删除值为val的节点；onlyDeleteFirst = true则只删除从前到后的第一个值为val的节点；
	// 删除的节点内存需要释放
	// 返回删除后的链表头指针

	ListNode* headNULL = new ListNode(-1, head);
	ListNode* prev = headNULL; // head = headNULL->next
	while(head!=NULL) {
		// prev -> head -> ...
		if(head->val == val) {
			// delete node head
			// prev -> head -> temp -> ...
			// to
			// prev -> temp -> ...
			ListNode* temp = head ->next;
			prev -> next = temp;
			delete head;
			head = temp;
			if(onlyDeleteFirst)
				break;
		}
		else {
			prev = head;
			head = head->next;
		}
	}

	head = headNULL->next;
	delete headNULL;
	return head;
}
