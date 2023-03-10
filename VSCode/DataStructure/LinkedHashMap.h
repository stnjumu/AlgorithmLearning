#pragma once

#include<vector>
#include<iostream>
#include<unordered_map>
#include<assert.h>
using namespace std;

// 146. LRU 缓存，最近最少使用缓存，移除最近最久未使用；面试常考；(进阶：460. LFU)
// 要求按访问顺序排列的(k, v)对, 且k查询O(1), 插入O(1);
// 仅支持末尾删除O(1)

// 实现方式：按访问顺序排列的LinkedHashMap, 链表尾部最常用；
// 链表中存v，Hash表中存(k, Node* node), node->value就是v；
struct DLinkedMapNode {
    int key, value; // key 可能可以不维护；
    DLinkedMapNode* prev;
    DLinkedMapNode* next;
    DLinkedMapNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedMapNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LinkedHashMap
{
private:
    unordered_map<int, DLinkedMapNode*> mapOfNode; // Hashmap of key-> Node addr of v
    DLinkedMapNode* head;
    DLinkedMapNode* tail;
    int size;
    int capacity;

    void move_to_back(DLinkedMapNode *node) {
        // delete at src pos
        node->prev->next = node->next;
        node->next->prev = node->prev;
        // add at back
        tail -> prev -> next = node;
        node -> prev = tail->prev;
        node->next = tail;
        tail->prev = node;
    }
    void push_back(int key, int value) {
        // 必须验证过mapOfNode[key]不存在;
        assert(mapOfNode.count(key)!=0);

        DLinkedMapNode *node = new DLinkedMapNode(key, value);
        mapOfNode[key] = node;
        tail -> prev -> next = node;
        node -> prev = tail->prev;
        node->next = tail;
        tail->prev = node;

        size++;
    }
    void pop_front() {
        assert(tail->prev!=head && head->next!=tail);
        remove_node(head->next);
    }
    void remove_node(DLinkedMapNode* del) {
        del->prev->next = tail;
        tail->prev = del->prev;
        mapOfNode.erase(del->key);
        delete del;

        size--;
    }

public:
    LinkedHashMap(int _capacity): size(0), capacity(_capacity) {
        head = new DLinkedMapNode();
        tail = new DLinkedMapNode();
        head->next = head->prev = tail;
        tail->next = tail->prev = head;
    }
    ~LinkedHashMap() {
        clear();
        delete head;
        delete tail;
    }

    void clear() {
        mapOfNode.clear();
        size = 0;

        DLinkedMapNode* p = head->next;
        while (p!= tail)
        {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        tail->prev = head; // 不要忘了tail->prev，! 易错点；
    }
    
    int get(int key) {
        if (!mapOfNode.count(key))
            return -1;
        // 存在, 调整顺序
        DLinkedMapNode *node = mapOfNode[key];
        move_to_back(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (mapOfNode.count(key)) {
            // 存在，定位node，移动到队尾，并修改值；
            DLinkedMapNode *node = mapOfNode[key];
            move_to_back(node);
            node->value = value;
        }
        else {
            push_back(key, value);
            if (size > capacity)
                pop_front();
            assert(size<=capacity);
        }
    }
};