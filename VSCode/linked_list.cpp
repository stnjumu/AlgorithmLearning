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

// 206. 反转链表
// 空头节点，头插法，击败7%, 40%
ListNode* reverseList(ListNode* head) {
    ListNode *headNull = new ListNode(-1);

    while(head!=NULL) {
        // 头插法
        ListNode *temp = head;
        head = head->next;

        temp->next=headNull->next;
        headNull->next=temp;
    }

    head = headNull->next;
    delete headNull;
    return head;
}
// 迭代版本，两个指针即可；击败93%, 78%
ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL;

    while(head!=NULL) {
        // ... <- prev -> head -> ...
        ListNode *temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
    }
    return prev;
}

// ! 25. K个一组翻转链表
// 思路1：使用双端队列保存k个节点，每凑够k个就反序插入，不够就正序插入；时间O(n), 空间O(k)
// 思路2：优化成O(1)空间复杂度；双指针，[left, right)凑够k个就头插法反序；
// 下面是思路2的实现，只需记住[left, right)左开右闭会非常好做，翻转[left, right]的话会比较难做；
ListNode* reverseKGroup(ListNode* head, int k) {
    if(k<=1)
        return head;
    
    ListNode *headNull = new ListNode(-1, head);

    ListNode *leftleft = headNull;
    ListNode *left=headNull->next, *right=left; // 必须[left, right)
    int count = 0;
    while(right!=NULL) {
        right=right->next;
        count++;

        if(count==k) {
            // [left, right) 翻转；
            // leftleft -> left -> ... -> lastright -> right
            // head insert
            ListNode *p = left;
            while(p!=right) {
                // p in [left, right), left其实不用插入，可以优化；
                ListNode *temp = leftleft-> next;
                leftleft-> next = p;
                p = p->next;
                leftleft->next->next = temp;
            }
            // leftleft -> lastright -> ... -> left, right
            left->next = right;
            // leftleft -> lastright -> ... -> left -> right

            // 迭代
            leftleft = left;
            right = left = left->next;
            count=0;
        }
    }

    head = headNull->next;
    delete headNull;
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

// 148. 排序链表
// 思路1：使用O(n)的空间存放指针，借用sort排序；击败68%, 67%;
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
// 思路2：原地归并排序；利用21. 合并两个有序链表代码
// for len in [2, 4, 8, ..., x], x<list.len: 每len个长度合并一下(merge)
// 即自底向上的归并排序，不需要额外空间, O(nlogn), O(1), 击败12%, 50%，反而更慢了，空间更大了；
pair<ListNode*, ListNode* > mergeTwoListsAndReturnHeadTail(ListNode* list1, ListNode* list2) {
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
    while(tail->next!=NULL) { // 需要返回tail节点
        tail=tail->next;
    }

    list1 = head -> next;
    delete head;
    return {list1, tail};
}
ListNode* sortList_SpaceO1(ListNode* head) {
    int listLen = getListSize(head);
    ListNode *headNULL = new ListNode(-1, head); // 空头节点，简化操作
    int len = 1;
    while(len < listLen) {
        ListNode* lastLeft = headNULL;
        ListNode* left = headNULL->next;
        ListNode* right = headNULL->next;
        ListNode* lastRight= headNULL;

        while(left!=NULL) {
            // 构造从left出发，要合并的两个链表, left和right, 注意设置list1和list2最后的一个节点的next = NULL;
            int i = len;
            while(i>0 && right!=NULL) {
                lastRight = right;
                right=right->next;
                i--;
            }
            if(right != NULL) {
                // 存在两个链表
                lastRight -> next = NULL; // list1: [left, right)

                ListNode *rightBack = right; // list2: [right, rightBack]
                ListNode *rightEnd = NULL; // 或list2: [right, rightEnd)
                i = len-1; // 从right要到rightBack, 即list2的最后一个节点；需要走len-1步；
                while(i>0 && rightBack!=NULL) {
                    rightBack = rightBack->next;
                    i--;
                }
                // rightBack==NULL, 说明list2长度不够len，没有下一次迭代了，且末尾是NULL，不需特殊处理；
                if(rightBack!=NULL) {
                    rightEnd = rightBack->next; // 为下一次迭代做准备；
                    rightBack->next=NULL; // list2: [right, rightEnd)
                }
                
                auto headTail = mergeTwoListsAndReturnHeadTail(left, right); // 注意名字中虽然有空头节点，但此函数输入不需要空头节点
                // 连接前后
                lastLeft -> next = headTail.first;
                headTail.second->next = rightEnd;

                // 迭代
                lastLeft = lastRight= headTail.second; // 注意不是rightBack, 因为merge操作会改变其顺序；
                left= right =rightEnd;
            }
            else {
                // 只剩一个待合并的链表left了；
                break; // ! 没有这句会死循环；
            }
        }

        // 迭代
        len *=2;
    }

    head = headNULL->next;
    delete headNULL;
    return head;
}

// 160. 相交链表
// 击败68%， 30%
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int len1 = getListSize(headA);
    int len2 = getListSize(headB);
    if(len2<len1) {
        swap(len1,len2);
        swap(headA, headB);
    }

    // len1 <= len2
    int len = len2-len1; // 长的链表先走几步；之后一起走，如果相交两者会相遇；
    // B先走len步
    while(len>0) {
        len--;
        headB=headB->next;
    }
    while(headA!=headB) {
        headA=headA->next;
        headB=headB->next;
    }
    return headA;
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

    cout<< "K个一组翻转链表"<<endl;
    list1 = vector2List({1,2,3,4,5});
    list1 = reverseKGroup(list1, 2);
    printList(list1);
    deleteList(list1);
    
    list1 = vector2List({1,2,3,4,5,6,7,8,9,10});
    list1 = reverseKGroup(list1, 3);
    printList(list1);
    deleteList(list1);
    
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

    cout<<"排序链表-O(1)空间"<<endl;
    list1 = vector2List({-1,5,3,4,0});
    list1 = sortList_SpaceO1(list1);
    printList(list1);
    deleteList(list1);

    return 0;
}