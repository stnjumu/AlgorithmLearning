#include"ListNode.h"
#include<iostream>
using namespace std;

#include"Solutions.h"
void solveProblem(int id) {
	if (id == 2)
	{
		ListNode* list1 = vector2List(vector<int>({ 2, 4, 3 })), *list2 = vector2List(vector<int>({ 5, 6, 4 }));
		//ListNode *list1 = vector2List(vector<int>({ 0 })), *list2 = vector2List(vector<int>({ 0 }));
		//ListNode *list1 = vector2List(vector<int>({ 9,9,9,9,9,9,9 })), *list2 = vector2List(vector<int>({ 9,9,9,9 }));
		printList(list1);
		printList(list2);

		Solution2 sol;
		cout << sol.problem << endl;
		ListNode* list3 = sol.addTwoNumbers(list1, list2);
		printList(list3);
		deleteList(list3);
	}
	else if (id == 19)
	{
		ListNode* list1 = vector2List(vector<int>({ 1,2,3,4,5 }));
		int n = 2;
		//ListNode* list1 = vector2List(vector<int>({ 1 }));
		//int n = 1;
		//ListNode* list1 = vector2List(vector<int>({ 1,2 }));
		//int n = 1;
		printList(list1);
		
		Solution19 sol;
		cout << sol.problem << endl;
		ListNode* list3 = sol.removeNthFromEnd(list1, n);
		printList(list3);
		deleteList(list3);
	}
	else if (id == 21)
	{
		ListNode* list1 = vector2List(vector<int>({ 1, 2, 4 })), *list2 = vector2List(vector<int>({ 1, 3, 4 }));
		//ListNode *list1 = NULL, *list2 = vector2List(vector<int>({ 0 }));
		printList(list1);
		printList(list2);

		Solution21 sol;
		cout << sol.problem << endl;
		ListNode* list3 = sol.mergeTwoLists(list1, list2);
		printList(list3);
		deleteList(list3);
	}
	else if (id == 23)
	{
		vector<ListNode*> lists;
		lists.push_back(vector2List(vector<int>({ 1,4,5 })));
		lists.push_back(vector2List(vector<int>({ 1,3,4 })));
		lists.push_back(vector2List(vector<int>({ 2,6 })));
		//lists.push_back( vector2List(vector<int>({ }) ) );

		for (auto list : lists)
			printList(list);

		Solution23 sol;
		cout << sol.problem << endl;
		ListNode* ans = sol.mergeKLists(lists);
		printList(ans);
		deleteList(ans);
	}
	else if (id == 24)
	{
		ListNode *list = vector2List(vector<int>({ 1, 2, 4 }));
		//ListNode *list = vector2List(vector<int>({ 1, 2, 3, 4 }));
		//ListNode *list = vector2List(vector<int>({  }));
		//ListNode *list = vector2List(vector<int>({ 1 }));

		printList(list);

		Solution24 sol;
		cout << sol.problem << endl;
		ListNode* ans = sol.swapPairs(list);
		printList(ans);
		deleteList(ans);
	}
	else if (id == 25)
	{
		ListNode *list = vector2List(vector<int>({ 1, 2, 3, 4, 5 }));
		//ListNode *list = vector2List(vector<int>({ 1, 2 }));
		int k = 2;
		//int k = 3;
		printList(list);

		Solution25 sol;
		cout << sol.problem << endl;
		ListNode* ans = sol.reverseKGroup(list, k);
		printList(ans);
		deleteList(ans);
	}
	else if (id == 61)
	{

		//ListNode *list = vector2List(vector<int>({ 0, 1, 2 }));
		ListNode *list = vector2List(vector<int>({ 1, 2, 3, 4, 5 }));
		int k = 2;
		//int k = 4;
		printList(list);

		Solution61 sol;
		cout << sol.problem << endl;
		ListNode* ans = sol.rotateRight(list, k);
		printList(ans);
		deleteList(ans);
	}
	else if (id == 141)
	{
		Solution141 sol;
		vector<ListNode*> nodes;
		//ListNode *list = sol.createCycleList(vector<int>({ 3,2,0,-4 }), 1, nodes);
		//ListNode *list = sol.createCycleList(vector<int>({ 1,2 }), 0, nodes);
		ListNode *list = sol.createCycleList(vector<int>({ 1 }), -1, nodes);
		cout << sol.problem << endl;
		cout << sol.hasCycle(list) << endl;
		
		cout << "nodes = ";
		for (auto node : nodes)
		{
			cout << node->val << " ";
			delete node;
		}
		cout << endl;
	}
	else
	{
		cout << "Not supported id: " << id << endl;
	}

	system("pause");
	return;
}

int main() {
	vector<int> problem = vector<int>(
		{ 2,19,21,23,24,25,61,141 }
	);
	solveProblem(141);

	return 0;
}
