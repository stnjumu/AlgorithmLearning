#pragma once

#include<vector>
#include<iostream>
using namespace std;

/*
list库就是双向链表；
*/

struct DLinkedNode {
    int value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _value): value(_value), prev(nullptr), next(nullptr) {}
};

class DList
{
private:
    DLinkedNode* head, *tail;
public:
    DList() {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next=head->prev = tail;
        tail->next=head->prev = head;
    }
    DList(vector<int> nums) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next=head->prev = tail;
        tail->next=tail->prev = head;

        for(auto num: nums) {
            push_back(num);
        }
    }
    ~DList() {
        clear();
        delete head;
        delete tail;
    }

    void clear() {
        DLinkedNode* p = head->next;
        while (p!= tail)
        {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        tail->prev = head; // 不要忘了tail->prev，! 易错点；
    }
    void push_back(int num) {
        DLinkedNode *temp = new DLinkedNode(num);
        // 重连两条，新增两条，最后重连tail；! 重点；
        tail->prev->next = temp;
        temp -> prev = tail->prev;
        temp -> next = tail;
        tail -> prev = temp;
    }

    void print() {
        cout<<"DList = ";
        DLinkedNode* p = head->next;
        while (p!=tail)
        {
            cout<<p->value<<" ";
            p=p->next;
        }
        cout<<endl;
    }
};