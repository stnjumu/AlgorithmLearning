#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include"DataStructure/ListNode.h"
using namespace std;

// 21. 合并两个有序链表
// 空头节点可简化链表构建，插入，删除的逻辑；
ListNode* mergeTwoListsWithEmptyHead(ListNode* list1, ListNode* list2) {
    ListNode* head=new ListNode(-1);
    ListNode *tail =head;
    while (list1!=NULL && list2!=NULL)
    {
        if (list1->val < list2->val)
        {
            tail = tail->next = list1;
            list1 = list1->next;
        }
        else {
            tail = tail->next = list2;
            list2 = list2->next;
        }
    }
    tail->next = list1==NULL ? list2 : list1;

    tail = head; // tail下面仅用于删除空头节点；
    head = head -> next;
    delete tail;
    return head;
}
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head=NULL, *tail =NULL;
    while (list1!=NULL && list2!=NULL)
    {
        ListNode *temp;
        
        if(list1->val < list2->val) {
            temp = list1;
            list1=list1->next;
        }
        else {
            temp = list2;
            list2=list2->next;
        }
        temp->next = NULL;
        if(head==NULL) {
            head = tail = temp;
        }
        else {
            tail = tail->next = temp;
        }
    }
    if(list1!=NULL) {
        if(head == NULL) {
            head = tail = list1;
        }
        else {
            tail -> next = list1;
            // 下面的tail不再指向链表尾部；
        }
    }
    else if(list2!=NULL) {
        if(head == NULL) {
            head = tail = list2;
        }
        else {
            tail -> next = list2;
            // 下面的tail不再指向链表尾部；
        }
    }
    return head;
}

// 142. 环形链表II
// Floyd判圈法，快慢指针
bool hasCycle(ListNode *head) {
    if (head == NULL)
        return false;
    ListNode* fast = head, *slow = head;
    // ! 必须使用do while, 因为刚开始slow==fast;
    do {
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
// 142. 环形链表II
// Floyd判圈法，快慢指针
// 分析可先分析圈较大的情况，这时fast比slow多走一圈，设非环部分长h, 圈中slow走了s，圈中除了s的剩余部分为f;
// 则h+s为slow走的，s+f为圈大小，fast比slow多走一圈，且相遇在h+s处，显然有2(h+s)=(h+s)+(f+s)，即h+s=f+s, h=f;
// 显然请另一个slow2指针从起点开始，slow从h+s处开始，两者都走h步后恰好相遇在入口节点；(第一次相遇)
// 再分析圈较小的情况，则fast会多走几圈，有k(f+s)=h+s, 整理得h=f+(k-1)(f+s)，用上面得方法，两个slow走了h步后也会刚好在入口节点相遇；
// 击败98%, 96%
ListNode *detectCycle(ListNode *head) {
    if (head == NULL)
        return NULL;
    ListNode* fast = head, *slow = head;
    // ! 必须使用do while, 因为刚开始slow==fast;
    do {
        slow = slow->next;
        fast = fast->next;
        if (fast!=NULL)
        {
            fast = fast->next;
        }
    } while (fast!=NULL && slow!=NULL && fast!=slow);

    if (fast==NULL || slow==NULL)
    {
        return NULL;
    }
    
    // 有环
    fast = head; // fast做为第二个slow指针，下面每次只走一步
    while(fast!=slow) {
        fast=fast->next;
        slow=slow->next;
    }
    return slow;
}

// 160. 两个链表的第一个公共节点
pair<ListNode*, ListNode*> buildListHasIntersectionNode(vector<int> a1, vector<int> b1, vector<int> shared_tail) {
    if(shared_tail.empty()) {
        return {vector2List(a1), vector2List(b1)};
    }

    pair<ListNode*, ListNode*> head_taila = vector2List_ReturnHeadAndTail(a1);
    pair<ListNode*, ListNode*> head_tailb = vector2List_ReturnHeadAndTail(b1);
    ListNode* list_shared_tail = vector2List(shared_tail);
    printList(list_shared_tail, string("shared part"));
    if(head_taila.second!=NULL)
        head_taila.second->next = list_shared_tail;
    else
        head_taila.second=list_shared_tail;
    if(head_tailb.second!=NULL)
        head_tailb.second->next = list_shared_tail;
    else
        head_tailb.second=list_shared_tail;
    printList(head_taila.first, string("listA"));
    printList(head_tailb.first, string("listB"));
    return {head_taila.first, head_tailb.first};
}
void deleteListHasIntersectionNode(ListNode* lista, ListNode* listb, ListNode* firstIntersectionNode) {
    ListNode* p = lista;
    while(p!=NULL && p->next!=firstIntersectionNode ) {
        p = p->next;
    }
    if(p != NULL) {
        p->next=NULL;
    }
    deleteList(lista);
    deleteList(listb);
}
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(headA == NULL || headB == NULL)
        return NULL;
    int lenA=0, lenB=0;
    ListNode *pa = headA, *pb = headB;
    while(pa!=NULL) {
        pa = pa->next;
        lenA++;
    }
    while(pb!=NULL) {
        pb = pb->next;
        lenB++;
    }
    if(lenA<lenB) {
        swap(lenA, lenB);
        swap(headA, headB);
    }
    // headA更长；
    pa = headA;
    pb = headB;
    for(int i=0;i<lenA-lenB;i++)
        pa = pa->next; // pa将listA长的几步先走了；
    while (pa != pb)
    {
        pa = pa->next;
        pb = pb->next;
    }
    return pa;
}

ListNode* sortList(ListNode* head) {
    if(head==NULL || head->next==NULL)
        return head;

    vector<ListNode*> numPointer;
    ListNode* p=head;
    while(p!=NULL) {
        numPointer.push_back(p);
        p=p->next;
    }

    sort(numPointer.begin(), numPointer.end(), [](ListNode* p1, ListNode*p2) {
        return p1->val<p2->val;
    });

    for(int i=1;i<numPointer.size();i++) {
        numPointer[i-1]->next=numPointer[i];
    }
    numPointer.back()->next=NULL;
    return numPointer[0];
}

int main()
{
    cout<<"合并两个有序链表"<<endl;
    ListNode *list1 = vector2List({1,2,4});
    ListNode *list2 = vector2List({1,3,4});
    ListNode *list3 = mergeTwoLists(list1, list2);
    printList(list3);
    deleteList(list3);

    list1 = vector2List({1,2,4});
    list2 = vector2List({1,3,4});
    list3 = mergeTwoLists(list1, list2);
    printList(list3);
    deleteList(list3);

    
    cout<<"两个链表的第一个公共节点"<<endl;
    pair<ListNode*, ListNode*> twoList = buildListHasIntersectionNode({4,1}, {5,0,1}, {8,4,5});
    list3 = getIntersectionNode(twoList.first, twoList.second);
    if(list3==NULL)
        cout<< "NULL"<<endl;
    else
        cout<<list3->val<<endl;
    deleteListHasIntersectionNode(twoList.first, twoList.second, list3);

    cout<<"排序链表"<<endl;
    list1 = vector2List({4,2,1,3});
    list1 = sortList(list1);
    printList(list1);
    deleteList(list1);

    return 0;
}