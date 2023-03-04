#pragma once
#include"ListNode.h"

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *ansHead = NULL, *ansTail = NULL;
		int carry = 0;
		while (l1 != NULL or l2 != NULL or carry != 0)
		{
			int n1 = 0, n2 = 0;
			if (l1 != NULL)
			{
				n1 = l1->val;
				l1 = l1->next;
			}
			if (l2 != NULL)
			{
				n2 = l2->val;
				l2 = l2->next;
			}
			int ans = n1 + n2 + carry;
			carry = ans / 10;
			ans = ans % 10;

			if (ansHead == NULL)
			{
				ansHead = ansTail = new ListNode(ans);
			}
			else
			{
				ansTail->next = new ListNode(ans);
				ansTail = ansTail->next;
			}
		}
		return ansHead;
	}
};