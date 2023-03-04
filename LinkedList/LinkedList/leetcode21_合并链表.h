#pragma once
#include"ListNode.h"
#include<vector>

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode *head = NULL, *tail = NULL;
		while (list1!=NULL && list2!=NULL)
		{
			int val;
			if (list1->val <= list2->val)
			{
				val = list1->val;
				list1 = list1->next;
			}
			else
			{
				val = list2->val;
				list2 = list2->next;
			}

			if (head == NULL)
			{
				head = tail = new ListNode(val);
			}
			else
			{
				tail->next = new ListNode(val);
				tail = tail->next;
			}
		}

		// ��д�����ظ�����Ĳ��裬���ù��취���ڵ������ȥ��
		// ���и�ʡʱ���������ֱ�Ӱ�ʣ�µĹ���֮ǰ��β�����ɣ����˷������׳�������ʱע���������Ϥ�ķ��������׳���
		// �����д���д��˷ǳ��ü��Σ�һ��ע�Ͷ�Ӧһ���״�㣻
		if (list1 != NULL)
		{
			if (tail == NULL) //ʱ��ע��ձ����
				head = tail = list1; // ע��head
			else
				tail->next = list1;
		}
		if (list2 != NULL)
		{
			if (tail == NULL)
				head = tail = list2;
			else
				tail->next = list2;
		}

		return head;
	}
};