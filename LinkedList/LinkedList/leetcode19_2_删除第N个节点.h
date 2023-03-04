#pragma once
#include"ListNode.h"

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// 假设第n个节点必存在；

		if (head == NULL)
			return head;
	
		// 3种情况，删除第一个节点，删除最后一个节点，删除中间节点；
		if (n == 1) {
			return head->next;
		}
		
		ListNode *mid = head, *left = NULL;
		for (int i = 0; i < n-1; i++) // 右移mid n-1次
		{
			left = mid; // 注意left的初始化和迭代方法；
			mid = mid->next;
		}
		// del min
		left->next = mid->next; // 包含后两种情况；
		delete mid;

		return head;
	}
};