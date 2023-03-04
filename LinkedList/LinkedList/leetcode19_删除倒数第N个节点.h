#pragma once
#include"ListNode.h"

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// 根据题目，倒数第n个节点必存在；

		if (head == NULL)
			return head;

		ListNode *mid = head, *leftn = head, *leftleftn = NULL;
		// 维护两个相距n个节点的指针，当右边节点刚好指向最后一个的下一个时，左边节点指向倒数第n个节点；
		// leftleftn是leftn的左边节点，用于删除节点；
		while (mid!=NULL) // 右移mid到出界，则leftn刚好指向倒数第n个节点。
		{
			if (n > 0)
			{
				n--;
			}
			else
			{
				// 右移n次了
				leftleftn = leftn;
				leftn = leftn->next;
			}
			mid = mid->next;
		}
		// del leftn. 三种情况，删除第一个节点，删除最后一个节点，以及删除中间节点；
		if (head==leftn)
		{
			head = head->next;
		}
		else
		{
			leftleftn->next = leftn->next;
		}
		delete leftn;
		return head;
	}
};