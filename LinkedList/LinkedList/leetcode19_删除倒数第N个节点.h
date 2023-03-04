#pragma once
#include"ListNode.h"

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// ������Ŀ��������n���ڵ�ش��ڣ�

		if (head == NULL)
			return head;

		ListNode *mid = head, *leftn = head, *leftleftn = NULL;
		// ά���������n���ڵ��ָ�룬���ұ߽ڵ�պ�ָ�����һ������һ��ʱ����߽ڵ�ָ������n���ڵ㣻
		// leftleftn��leftn����߽ڵ㣬����ɾ���ڵ㣻
		while (mid!=NULL) // ����mid�����磬��leftn�պ�ָ������n���ڵ㡣
		{
			if (n > 0)
			{
				n--;
			}
			else
			{
				// ����n����
				leftleftn = leftn;
				leftn = leftn->next;
			}
			mid = mid->next;
		}
		// del leftn. ���������ɾ����һ���ڵ㣬ɾ�����һ���ڵ㣬�Լ�ɾ���м�ڵ㣻
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