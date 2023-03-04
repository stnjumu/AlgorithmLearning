#include"ListNode.h"
#include<iostream>
using namespace std;


#include"leetcode19_删除倒数第N个节点.h"
int main() {
	ListNode* list1 = vector2List(vector<int>({ 1,2,3,4,5 }));
	int n = 2;
	//ListNode* list1 = vector2List(vector<int>({ 1 }));
	//int n = 1;
	//ListNode* list1 = vector2List(vector<int>({ 1,2 }));
	//int n = 1;
	printList(list1);

	Solution sol;
	ListNode* list3 = sol.removeNthFromEnd(list1, n);
	printList(list3);

	system("pause");
	return 0;
}


//#include"leetcode19_2_删除第N个节点.h"
//int main() {
//	/*ListNode* list1 = vector2List(vector<int>({ 1,2,3,4,5 }));
//	int n = 2;*/
//	/*ListNode* list1 = vector2List(vector<int>({ 1 }));
//	int n = 1;*/
//	ListNode* list1 = vector2List(vector<int>({ 1,2 }));
//	int n = 1;
//	printList(list1);
//
//	Solution sol;
//	ListNode* list3 = sol.removeNthFromEnd(list1, n);
//	printList(list3);
//
//	system("pause");
//	return 0;
//}


//#include"leetcode2_大数相加.h"
//int main() {
//	//ListNode* list1 = vector2List(vector<int>({ 2, 4, 3 })), *list2 = vector2List(vector<int>({ 5, 6, 4 }));
//	//ListNode *list1 = vector2List(vector<int>({ 0 })), *list2 = vector2List(vector<int>({ 0 }));
//	ListNode *list1 = vector2List(vector<int>({ 9,9,9,9,9,9,9 })), *list2 = vector2List(vector<int>({ 9,9,9,9 }));
//	printList(list1);
//	printList(list2);
//
//	Solution sol;
//	ListNode* list3 = sol.addTwoNumbers(list1, list2);
//	printList(list3);
//
//	system("pause");
//	return 0;
//}


//#include"leetcode21_合并链表.h"
//int main() {
//	//ListNode* list1 = vector2List(vector<int>({ 1, 2, 4 })), *list2 = vector2List(vector<int>({ 1, 3, 4 }));
//	ListNode *list1 = NULL, *list2 = vector2List(vector<int>({ 0 }));
//	printList(list1);
//	printList(list2);
//
//	Solution sol;
//	ListNode* list3 = sol.mergeTwoLists(list1, list2);
//	printList(list3);
//
//	system("pause");
//	return 0;
//}