#pragma once
#include<vector>
#include<iostream>
#include<string>
using namespace std;

// Definition for singly-linked list.
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

void printList(ListNode* head, string name = string("list")) {
	cout << name << " = ";
	while (head!=NULL)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}