#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
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