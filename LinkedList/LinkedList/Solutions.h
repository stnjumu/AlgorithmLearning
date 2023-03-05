#pragma once
#include"ListNode.h"
#include"TreeNode.h"

// 知乎图解：https://zhuanlan.zhihu.com/p/150871816
// TODO: 虚拟头节点的链表；

// 2. 大数相加
class Solution2 {
public:
	string problem = "两个链表表示的大整数相加";
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
// 19. 删除倒数第N个节点
class Solution19 {
public:
	string problem = "删除链表倒数第n个节点";
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// 根据题目，倒数第n个节点必存在；

		if (head == NULL)
			return head;

		ListNode *mid = head, *leftn = head, *leftleftn = NULL;
		// 维护两个相距n个节点的指针，当右边节点刚好指向最后一个的下一个时，左边节点指向倒数第n个节点；
		// leftleftn是leftn的左边节点，用于删除节点；
		while (mid != NULL) // 右移mid到出界，则leftn刚好指向倒数第n个节点。
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
// 删除第N个节点
class Solution19_2 {
public:
	string problem = "删除链表第n个节点";
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// 假设第n个节点必存在；

		if (head == NULL)
			return head;

		// 3种情况，删除第一个节点，删除最后一个节点，删除中间节点；
		if (n == 1) {
			return head->next;
		}

		ListNode *mid = head, *left = NULL;
		for (int i = 0; i < n - 1; i++) // 右移mid n-1次
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
// 21. 合并2个有序链表
class Solution21 {
public:
	string problem = "合并2个有序链表";
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
// 23. 合并k个有序链表
class Solution23 {
public:
	string problem = "合并k个有序链表";
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

		// lambda表达式：三种括号全用即可，[](){};
		// 自定义谓词，谓词即返回值为bool值的函数，仅做判断；
		auto greater = [](ListNode* a, ListNode*b) {
			return a->val > b->val; // less
		};
		// 堆为算法；包含
		// make_heap (构造堆使heap[0]最小, 默认less构造最大堆, O(n)) 
		// pop_heap (将heap[0]和heap[size-1]交换，并将heap[0]到heap[size-2]修复堆，逐层下降O(log n))
		// push_heap (heap[0]到heap[size-2]是堆，而heap[size-1]是新push的，此函数修复堆，逐层上升O(log n))
		// 堆算法需要配合容器使用，利用vector和其操作：v[0], v.pop_back(), v.push_back()等;
		make_heap(heap.begin(), heap.end(), greater); // 默认谓词为less<T>()，即a<b，构造最大堆；而换用greater<T>()可构造最小堆；注意heap中又是ListNode*, 则需要自定义谓词；
		while (!heap.empty())
		{
			// heap[0]即最小值；
			if (head == NULL)
			{
				head = tail = heap[0];
			}
			else
			{
				tail->next = heap[0];
				tail = tail->next;
			}

			// heap删除堆顶，再添加堆顶的next到heap中；
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
// 24. 两两交换链表节点
class Solution24 {
public:
	string problem = "两两交换链表节点";
	// 思路1：直接交换；(已实现)
	// 思路2：新建链表，每两个一组添加到新链表，只需添加时反转一下就行；
	// 思路2.1: 在思路2的基础上，使用一个flag表示当前节点的奇偶，奇时就正常插入到tail的后面, 偶时则插入到tail指向节点的前面(类似于头插构造法)
	// 思路2.2: 在思路2.1的基础上，拓展到k个节点一组的交换；
	ListNode* swapPairs(ListNode* head) {
		if (head == NULL || head->next == NULL)
		{
			return head;
		}

		// 节点数大于1
		ListNode *mid = head, *right = head->next, *left = NULL;
		while (mid != NULL && right != NULL)
		{
			if (left == NULL) // mid指向head
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

			// 注意mid和right已经交换了；
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
// 25. k个一组翻转链表节点
class Solution25 {
public:
	string problem = "k个一组翻转链表节点";
	// 已实现思路：见leetcode24_两两交换节点.h中思路2.2
	// 思路2: 中间存k个节点的数据结构用stack;
	ListNode* reverseKGroup(ListNode* head, int k) {
		vector<ListNode*> listk;
		ListNode *ansHead = NULL, *ansTail = NULL;

		while (head != NULL)
		{
			listk.push_back(head);
			head = head->next;

			if (listk.size() == k)
			{
				// 尾插法，倒序； 注意：构造方法应保证Node->next = NULL；
				for (int i = k - 1; i >= 0; i--)
				{
					listk[i]->next = NULL; // bug: 没有这句会导致最后一个的next没有设置；
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
			// 尾插法
			for (size_t i = 0; i < listk.size(); i++)
			{
				listk[i]->next = NULL; // 此句倒是可以不用； 
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
// 61. 循环旋转链表
class Solution61 {
public:
	string problem = "循环右移链表k位";
	// 右旋对应于将head左移k位；由于k可能大于链表长度，所以需要先求链表长度n，再k%n；
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

		int k_left = n - k; // 可保证n-k在(0, n)
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
// 82. 83. 删除重复元素, deleteDuplicates
// 86. 分隔链表, partition
// 92. 反转部分链表，思路同25; ListNode* reverseBetween(ListNode* head, int left, int right);

// 与二叉树联系
// 109. 有序链表转高度平衡的二叉搜索树，应该放在BST构造中学习；
// 114. 二叉树展开为链表
// ...

// 138. 复制带有随机指针的链表，保证新节点也指向新链表的随机节点
// 思路: 让新节点的先插入到原节点的后面，然后就可用原链表指向的随机节点获取新节点要指向的随机节点；
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
		while (ite) { // 用next连接
			Node* n = new Node(ite->val, ite->next, nullptr);
			Node* c = ite->next;
			ite->next = n;
			ite = c;
		}
		ite = head;
		while (ite) { // 连接random
			if (ite->random) ite->next->random = ite->random->next;
			ite = ite->next->next;
		}
		ite = head;
		Node* ret = head->next;
		while (ite->next) { // 有丝分裂(大雾)
			Node* c = ite->next;
			ite->next = ite->next->next;
			ite = c;
		}
		return ret;
	}
};
// 141. 判断链表有环
class Solution141 {
public:
	string problem = "判断链表是否有环";
	ListNode* createCycleList(vector<int> vals, int pos, vector<ListNode*> &nodes) {
		// pos从0开始，0表示最后一个节点指向第一个节点；-1则表示没有环；
		ListNode* head = vector2List(vals);
		// nodes参数用于delete，防止内存泄露；
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
			if (pos > 0) // 总共右移pos次；
				posNode = posNode->next;

			pos--;
			tail = p;
			p = p->next;
		}
		tail->next = posNode;

		return head;
	}
	bool hasCycle(ListNode *head) {
		// 思路1：穷举比较法，记录遇到的每个节点地址，每次都查找，若查找到，则有环，O(n^2)，不可取；
		// 思路2：hash比较法，利用hash表或者其他map来记录当前节点的地址是否出现过，查找复杂度是O(n)，更多的是哈希表的构建复杂度；空间O(n)；unordered_map也是一种hash_map；
		// 思路3：快慢指针法
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