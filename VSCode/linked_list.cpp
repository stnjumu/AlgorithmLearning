#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include"DataStructure/ListNode.h"
#include"DataStructure/array.h"
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
// 注意头插法对指针的操作次数是迭代版本的2倍；
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
ListNode* reverseListIter(ListNode* head) {
    ListNode *prev = NULL;
    while(head!=NULL) {
        // ... <- prev, head -> ...
        // =>
        // ... <- prev <- head, temp -> ...
        ListNode *temp = head->next;
        head->next = prev;
        // 迭代
        prev = head;
        head = temp;
    }
    return prev;
}

// ! 25. K个一组翻转链表
// 思路1：使用双端队列保存k个节点，每凑够k个就反序插入，不够就正序插入；时间O(n), 空间O(k)
// 思路2：优化成O(1)空间复杂度；双指针，[left, right)凑够k个就头插法反序；
// 头插法 [left, right) 
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
            // 法1：head insert
            // TODO: 法2：迭代版本的链表翻转，利用reverseListIter;
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
// 迭代翻转 [left, right] right定义和上面right不太一样，这个更符合直觉；
ListNode* reverseKGroup2(ListNode* head, int k) {
    // using null head
    ListNode *headNULL= new ListNode(-1, head);
    
    int i=0;
    ListNode *leftleft=headNULL, *left=head;
    ListNode *right=head, *rightright=nullptr;
    // leftleft->left-> ... -> right->rightright
    while(right!=nullptr) {
        i++;
        rightright = right->next;
        if(i%k==0) {
            // reverse [left, right]
            // reverse_list(leftleft, left, right, rightright); // 可以把下面实现一个函数；
            ListNode *p = left, *pp=nullptr;
            while(p!=rightright) {
                ListNode *temp_next = p->next;
                p->next = pp;
                pp = p;
                p = temp_next;
            }
            leftleft->next = right;
            left->next= rightright;

            // for next it
            leftleft = left;
            left = rightright;
        }
        
        // for next it
        right=rightright;
    }

    head = headNULL->next;
    delete headNULL;
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

// 160. 相交链表/两个链表的第一个公共节点
// 击败68%， 30%
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

// 234. 回文链表
// O(n),O(1)的做法：先遍历一次得len, len%2==0: 反转后半个链表，然后进行比较；len%2==1: 翻转后len/2个节点，然后仅比较前len/2个节点；两种情况可合并；
// 优化：利用fast, slow指针，fast指向NULL时，slow刚好走过ceil(len/2.0)步，刚好指向节点及之后共len/2个节点；
// 击败53%, 58%
bool isPalindrome(ListNode* head) {
    ListNode *slow = head;
    ListNode *fast = head;
    ListNode *lastslow = NULL;
    int len=0;
    while(fast!=NULL) {
        fast=fast->next;
        len++;
        if(fast!=NULL) {
            fast=fast->next;
            len++;
        }
        lastslow = slow;
        slow = slow->next;
    }
    // fast指向NULL时，slow刚好指向节点及之后刚好有len/2个；
    // 断开两链表
    lastslow->next=NULL;

    // 翻转slow链表
    slow = reverseListIter(slow);

    // 连上两链表，为了以后回收空间
    lastslow->next=slow;

    // 判断前后两部分链表的前len/2个元素相同；
    // len为奇数时刚好不会判断中间元素；
    fast=head; // 只是为了节省空间，下面的fast也是每次走一步；
    len/=2;
    while(len>0) {
        assert(slow!=NULL && fast!=NULL);
        if(slow->val!=fast->val)
            return false;
        slow = slow->next;
        fast = fast->next;
        len--; // ! 又忘写了!
    }
    return true;
}

// 剑指 Offer 06. 从尾到头打印链表
// 击败100%, 91%
vector<int> reversePrint(ListNode* head) {
    vector<int> ans;
    while(head!=NULL) {
        ans.push_back(head->val);
        head=head->next;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
// 如果可以修改原链表，且不需要返回vector，只反序打印, 则可先翻转链表，再打印；则O(1)空间可行；

// 剑指 Offer 35. 复杂链表的复制
// 链表额外多一个random指针，完成链表的copy

/*下面代码说明链表节点类不好用继承实现；
class Node: public ListNode {
public:
    // 继承自父类有int val; ListNode *next;
    Node* random;
    // 子类调用父类构造函数；
    Node(int _val): ListNode(_val), random(NULL) {}
    // ! Node指针不会自动转换为ListNode
    Node(int _val, Node* _next): ListNode(_val, _next), random(NULL) {}
    Node(int _val, Node* _next, Node* _random): ListNode(_val, _next), random(_random) {}
};
*/
class Node{
public:
    int val; 
    Node* next;
    Node* random;
    Node(int _val): val(_val), next(NULL), random(NULL) {}
    Node(int _val, Node* _next): val(_val), next(_next),  random(NULL) {}
    Node(int _val, Node* _next, Node* _random): val(_val), next(_next),  random(_random) {}
};
Node* vector2ListOffer35(vector<int> v, vector<int> randomIndex) {
    // v即每个节点的val, randomIndex[i]表示第i个节点的random指向第randomIndex[i]个节点；
    assert(randomIndex.size() == v.size());
	Node *head = NULL, *tail = NULL;
    vector<Node*> nodes;
	for (int i = 0; i < v.size(); i++) {
		if (head == NULL)
			head = tail = new Node(v[i]);
		else
			tail = tail->next = new Node(v[i]);
        nodes.push_back(tail);
	}

    // set random;
    for(int i=0;i<randomIndex.size();i++) {
        assert(randomIndex[i]< int(nodes.size())); // ! int 和 size_t比较会转换为无符号数，-1会变成很大的数；
        if(randomIndex[i]==-1)
            nodes[i]->random=NULL;
        else
            nodes[i]->random=nodes[randomIndex[i]];
    }

	return head;
}
void printListOffer35(Node* head, string name = string("list")) {
	cout << name << " val = ";
    Node* p = head;
	while (p!=NULL)
	{
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
	cout << "list random" << " = ";
    while (head!=NULL)
	{
        if(head->random == NULL)
            cout<<"null"<<" ";
        else
    		cout << head->random->val << " ";
		head = head->next;
	}
	cout << endl;
}
void deleteListOffer35(Node *head) {
	Node *del = head;
	while (head!=NULL)
	{
		del = head;
		head = head->next;
		delete del;
	}
}
// 原地，不使用额外空间；
// 击败97%, 93%
Node* copyRandomList(Node* head) {
    // ... -> nodei -> ...
    // to
    // ... -> nodei -> nodei' -> ...
    Node *p =head;
    while(p != NULL) {
        Node *temp = new Node(p->val, p->next);
        // insert temp to p->next
        p->next = temp;

        // 迭代
        p = temp -> next;
    }

    // set new node's random
    p = head;
    Node *pp;
    while(p!=NULL) {
        pp = p->next;
        assert(pp!=NULL);
        // ... -> p -> pp -> ...
        // pp is copy of p
        // if p->random == NULL, pp->random = NULL
        // else pp->random = p->random->next;
        pp->random = p->random == NULL ? NULL : p->random->next;

        p = pp->next;
    }

    // split two list
    Node *newHead=NULL, *newTail=NULL;
    p = head;
    while(p!=NULL) {
        if(newTail==NULL) {
            newTail=newHead = p->next;
        }
        else {
            newTail=newTail->next= p->next;
        }

        // ... -> p -> newTail -> ...
        p -> next = p->next->next;
        p = p->next;
    }
    // 可确定newTail->next被设置为NULL;

    return newHead;
}

// 剑指 Offer 22. 链表中倒数第k个节点
// 击败100%, 24%
ListNode* getKthFromEnd(ListNode* head, int k) {
    // 假设链表节点数n>=k;
    ListNode* p=head, *pp = head;
    int count = 0;
    while(p!=NULL) {
        if(count<k) {
            // 先走k步
            count++;
            p=p->next;
        }
        else {
            pp = pp->next;
            p=p->next;
        }
    }
    return pp;
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

    cout<<"回文链表"<<endl;
    list1 = vector2List({1,2,2,1});
    printList(list1);
    cout<<isPalindrome(list1)<<endl;
    printList(list1);
    deleteList(list1);

    cout<<"从尾到头打印链表"<<endl;
    list1 = vector2List({1,2,3,4});
    printList(list1);
    printVector(reversePrint(list1));
    deleteList(list1);

    cout<< "复杂链表的复制"<<endl;
    Node* randomList = vector2ListOffer35({7, 13,11, 10,1}, {-1,0,4,2,0});
    printListOffer35(randomList);
    Node* randomListCopy = copyRandomList(randomList);
    deleteListOffer35(randomList);
    printListOffer35(randomListCopy, "copy list");
    deleteListOffer35(randomListCopy);

    cout<<"删除链表的节点"<<endl;
    list1 = vector2List({1,2,3,4,1,6,7,8,1});
    printList(list1);
    cout<<getListSize(list1)<<endl;
    list1 = deleteNode(list1, 1);
    printList(list1);
    cout<<getListSize(list1)<<endl;
    deleteList(list1);

    cout<<"链表中倒数第k个节点"<<endl;
    list1 = vector2List({1,2,3,4,5});
    cout<< getKthFromEnd(list1, 2)->val<<endl;
    deleteList(list1);
    
    return 0;
}