#pragma once

#include<vector>
#include<iostream>
using namespace std;

struct SingleLinkedNode {
    int val;
    SingleLinkedNode* next;
    SingleLinkedNode(): val(0), next(nullptr) {}
    SingleLinkedNode(int _val): val(_val), next(nullptr) {}
};

class SList
{
private:
    SingleLinkedNode* head, *tail;
    // head为空头节点；tail指向最后一个节点；
    // 目前来看，单链表用空头节点，双向链表用空头节点和空尾节点，非常方便，还没有发现弊端；
public:
    SList() {
        head = tail = new SingleLinkedNode();
    }
    SList(vector<int> nums) {
        head = tail =  new SingleLinkedNode();

        for(auto num: nums) {
            push_back(num);
        }
    }
    ~SList() {
        clear();
        delete head;
    }

    void clear() {
        SingleLinkedNode *p = head->next;
        while (p!=NULL)
        {
            head ->next = p->next;
            delete p;
            p = head->next;
        }
    }
    void push_back(int num) {
        SingleLinkedNode *temp = new SingleLinkedNode(num);
        // 使用空头节点不需要额外判断head == NULL;
        tail = tail->next = temp;
    }

    void print() {
        cout<<"SList = ";
        SingleLinkedNode* p = head->next;
        while (p!=NULL)
        {
            cout<<p->val<<" ";
            p=p->next;
        }
        cout<<endl;
    }
};