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

		// 简单写法是重复上面的步骤，利用构造法将节点添加上去；
		// 但有更省时间的做法：直接把剩下的挂在之前的尾部即可，但此法稍容易出错，做题时注意采用最熟悉的方法，不易出错；
		// 下面的写法中错了非常好几次，一个注释对应一处易错点；
		if (list1 != NULL)
		{
			if (tail == NULL) //时刻注意空表情况
				head = tail = list1; // 注意head
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