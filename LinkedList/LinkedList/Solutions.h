#pragma once
#include"ListNode.h"
#include"TreeNode.h"

// ֪��ͼ�⣺https://zhuanlan.zhihu.com/p/150871816
// TODO: ����ͷ�ڵ������

// 2. �������
class Solution2 {
public:
	string problem = "���������ʾ�Ĵ��������";
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
// 19. ɾ��������N���ڵ�
class Solution19 {
public:
	string problem = "ɾ����������n���ڵ�";
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// ������Ŀ��������n���ڵ�ش��ڣ�

		if (head == NULL)
			return head;

		ListNode *mid = head, *leftn = head, *leftleftn = NULL;
		// ά���������n���ڵ��ָ�룬���ұ߽ڵ�պ�ָ�����һ������һ��ʱ����߽ڵ�ָ������n���ڵ㣻
		// leftleftn��leftn����߽ڵ㣬����ɾ���ڵ㣻
		while (mid != NULL) // ����mid�����磬��leftn�պ�ָ������n���ڵ㡣
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
		if (head == leftn)
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
// ɾ����N���ڵ�
class Solution19_2 {
public:
	string problem = "ɾ�������n���ڵ�";
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// �����n���ڵ�ش��ڣ�

		if (head == NULL)
			return head;

		// 3�������ɾ����һ���ڵ㣬ɾ�����һ���ڵ㣬ɾ���м�ڵ㣻
		if (n == 1) {
			return head->next;
		}

		ListNode *mid = head, *left = NULL;
		for (int i = 0; i < n - 1; i++) // ����mid n-1��
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
// 21. �ϲ�2����������
class Solution21 {
public:
	string problem = "�ϲ�2����������";
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode *head = NULL, *tail = NULL;
		while (list1 != NULL && list2 != NULL)
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
// 23. �ϲ�k����������
class Solution23 {
public:
	string problem = "�ϲ�k����������";
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* head = NULL, *tail = NULL;
		vector<ListNode*> heap;
		for (auto list : lists)
		{
			if (list != NULL)
			{
				heap.push_back(list);
			}
		}
		if (heap.empty())
		{
			return NULL;
		}

		// lambda���ʽ����������ȫ�ü��ɣ�[](){};
		// �Զ���ν�ʣ�ν�ʼ�����ֵΪboolֵ�ĺ����������жϣ�
		auto greater = [](ListNode* a, ListNode*b) {
			return a->val > b->val; // less
		};
		// ��Ϊ�㷨������
		// make_heap (�����ʹheap[0]��С, Ĭ��less��������, O(n)) 
		// pop_heap (��heap[0]��heap[size-1]����������heap[0]��heap[size-2]�޸��ѣ�����½�O(log n))
		// push_heap (heap[0]��heap[size-2]�Ƕѣ���heap[size-1]����push�ģ��˺����޸��ѣ��������O(log n))
		// ���㷨��Ҫ�������ʹ�ã�����vector���������v[0], v.pop_back(), v.push_back()��;
		make_heap(heap.begin(), heap.end(), greater); // Ĭ��ν��Ϊless<T>()����a<b���������ѣ�������greater<T>()�ɹ�����С�ѣ�ע��heap������ListNode*, ����Ҫ�Զ���ν�ʣ�
		while (!heap.empty())
		{
			// heap[0]����Сֵ��
			if (head == NULL)
			{
				head = tail = heap[0];
			}
			else
			{
				tail->next = heap[0];
				tail = tail->next;
			}

			// heapɾ���Ѷ�������ӶѶ���next��heap�У�
			pop_heap(heap.begin(), heap.end(), greater);
			heap.pop_back();
			if (tail->next != NULL)
			{
				heap.push_back(tail->next);
				push_heap(heap.begin(), heap.end(), greater);
			}
		}

		return head;
	}
};
// 24. ������������ڵ�
class Solution24 {
public:
	string problem = "������������ڵ�";
	// ˼·1��ֱ�ӽ�����(��ʵ��)
	// ˼·2���½�����ÿ����һ����ӵ�������ֻ�����ʱ��תһ�¾��У�
	// ˼·2.1: ��˼·2�Ļ����ϣ�ʹ��һ��flag��ʾ��ǰ�ڵ����ż����ʱ���������뵽tail�ĺ���, żʱ����뵽tailָ��ڵ��ǰ��(������ͷ�幹�취)
	// ˼·2.2: ��˼·2.1�Ļ����ϣ���չ��k���ڵ�һ��Ľ�����
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL)
		{
			return head;
		}

		// �ڵ�������1
		ListNode *mid = head, *right = head->next, *left = NULL;
		while (mid != NULL && right != NULL)
		{
			if (left == NULL) // midָ��head
			{
				head = right;
				mid->next = right->next;
				right->next = mid;
			}
			else
			{
				left->next = right;
				mid->next = right->next;
				right->next = mid;
			}

			// ע��mid��right�Ѿ������ˣ�
			left = mid;
			mid = mid->next;
			if (mid != NULL)
			{
				right = mid->next;
			}
			else
			{
				right = NULL;
			}
		}

		return head;
	}
};
// 25. k��һ�鷭ת����ڵ�
class Solution25 {
public:
	string problem = "k��һ�鷭ת����ڵ�";
	// ��ʵ��˼·����leetcode24_���������ڵ�.h��˼·2.2
	// ˼·2: �м��k���ڵ�����ݽṹ��stack;
	ListNode* reverseKGroup(ListNode* head, int k) {
		vector<ListNode*> listk;
		ListNode *ansHead = NULL, *ansTail = NULL;

		while (head != NULL)
		{
			listk.push_back(head);
			head = head->next;

			if (listk.size() == k)
			{
				// β�巨������ ע�⣺���췽��Ӧ��֤Node->next = NULL��
				for (int i = k - 1; i >= 0; i--)
				{
					listk[i]->next = NULL; // bug: û�����ᵼ�����һ����nextû�����ã�
					if (ansHead == NULL)
					{
						ansHead = ansTail = listk[i];
					}
					else
					{
						ansTail->next = listk[i];
						ansTail = ansTail->next;
					}
				}
				listk.clear();
			}
		}

		if (!listk.empty())
		{
			// β�巨
			for (size_t i = 0; i < listk.size(); i++)
			{
				listk[i]->next = NULL; // �˾䵹�ǿ��Բ��ã� 
				if (ansHead == NULL)
				{
					ansHead = ansTail = listk[i];
				}
				else
				{
					ansTail->next = listk[i];
					ansTail = ansTail->next;
				}
			}
			listk.clear();
		}

		return ansHead;
	}
};
// 61. ѭ����ת����
class Solution61 {
public:
	string problem = "ѭ����������kλ";
	// ������Ӧ�ڽ�head����kλ������k���ܴ��������ȣ�������Ҫ����������n����k%n��
	ListNode* rotateRight(ListNode* head, int k) {
		/*int n = 0;
		ListNode* p = head;
		while (p != NULL)
		{
			p = p->next;
			n++;
		}*/
		int n = getListSize(head);

		if (n <= 1)
			return head;

		k = k % n;
		if (k == 0)
			return head;

		int k_left = n - k; // �ɱ�֤n-k��(0, n)
		//cout << k << " " << n << " " << k_left << endl;

		ListNode *mid = head;
		ListNode *left = NULL;
		ListNode *newHead = NULL;
		while (mid != NULL)
		{
			if (k_left == 0)
			{
				left->next = NULL;
				newHead = mid;
			}

			k_left--;
			left = mid;
			mid = mid->next;
		}
		left->next = head;

		return newHead;
	}
};
// 82. 83. ɾ���ظ�Ԫ��, deleteDuplicates
// 86. �ָ�����, partition
// 92. ��ת��������˼·ͬ25; ListNode* reverseBetween(ListNode* head, int left, int right);

// ���������ϵ
// 109. ��������ת�߶�ƽ��Ķ�����������Ӧ�÷���BST������ѧϰ��
// 114. ������չ��Ϊ����
// ...

// 138. ���ƴ������ָ���������֤�½ڵ�Ҳָ�������������ڵ�
// ˼·: ���½ڵ���Ȳ��뵽ԭ�ڵ�ĺ��棬Ȼ��Ϳ���ԭ����ָ�������ڵ��ȡ�½ڵ�Ҫָ�������ڵ㣻
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val): val(_val), next(NULL), random(NULL) {}
	Node(int v, Node* n, Node* r): val(v), next(n), random(r) {}
};
class Solution138 { // copy from https://leetcode.cn/problems/copy-list-with-random-pointer/comments/
public:
	Node* copyRandomList(Node* head) {
		if (!head) return nullptr;
		Node* ite = head;
		while (ite) { // ��next����
			Node* n = new Node(ite->val, ite->next, nullptr);
			Node* c = ite->next;
			ite->next = n;
			ite = c;
		}
		ite = head;
		while (ite) { // ����random
			if (ite->random) ite->next->random = ite->random->next;
			ite = ite->next->next;
		}
		ite = head;
		Node* ret = head->next;
		while (ite->next) { // ��˿����(����)
			Node* c = ite->next;
			ite->next = ite->next->next;
			ite = c;
		}
		return ret;
	}
};
// 141. �ж������л�
class Solution141 {
public:
	string problem = "�ж������Ƿ��л�";
	ListNode* createCycleList(vector<int> vals, int pos, vector<ListNode*> &nodes) {
		// pos��0��ʼ��0��ʾ���һ���ڵ�ָ���һ���ڵ㣻-1���ʾû�л���
		ListNode* head = vector2List(vals);
		// nodes��������delete����ֹ�ڴ�й¶��
		ListNode* pp = head;
		while (pp!=NULL)
		{
			nodes.push_back(pp);
			pp = pp->next;
		}

		if (pos == -1)
			return head;

		ListNode* p = head, *tail = NULL;
		ListNode* posNode = head;
		while (p)
		{
			if (pos > 0) // �ܹ�����pos�Σ�
				posNode = posNode->next;

			pos--;
			tail = p;
			p = p->next;
		}
		tail->next = posNode;

		return head;
	}
	bool hasCycle(ListNode *head) {
		// ˼·1����ٱȽϷ�����¼������ÿ���ڵ��ַ��ÿ�ζ����ң������ҵ������л���O(n^2)������ȡ��
		// ˼·2��hash�ȽϷ�������hash���������map����¼��ǰ�ڵ�ĵ�ַ�Ƿ���ֹ������Ҹ��Ӷ���O(n)��������ǹ�ϣ��Ĺ������Ӷȣ��ռ�O(n)��unordered_mapҲ��һ��hash_map��
		// ˼·3������ָ�뷨
		if (head == NULL)
			return false;
		ListNode* fast = head, *slow = head;
		do
		{
			slow = slow->next;
			fast = fast->next;
			if (fast!=NULL)
			{
				fast = fast->next;
			}
		} while (fast!=NULL && slow!=NULL && fast!=slow);
		if (fast==NULL || slow==NULL)
		{
			return false;
		}
		else if (fast==slow)
		{
			return true;
		}
		else
		{
			cout << "Can't be here!" << endl;
			return false;
		}
	}
};