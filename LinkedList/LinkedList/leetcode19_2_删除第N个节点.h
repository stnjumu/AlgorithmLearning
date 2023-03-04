#pragma once
#include"ListNode.h"

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// �����n���ڵ�ش��ڣ�

		if (head == NULL)
			return head;
	
		// 3�������ɾ����һ���ڵ㣬ɾ�����һ���ڵ㣬ɾ���м�ڵ㣻
		if (n == 1) {
			return head->next;
		}
		
		ListNode *mid = head, *left = NULL;
		for (int i = 0; i < n-1; i++) // ����mid n-1��
		{
			left = mid; // ע��left�ĳ�ʼ���͵���������
			mid = mid->next;
		}
		// del min
		left->next = mid->next; // ���������������
		delete mid;

		return head;
	}
};