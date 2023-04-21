#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<assert.h>
using namespace std;

// 面试题59 - II. 队列的最大值
// max_value, push_back, pop_front的均摊复杂度均为O(1)
// 其他两个好分析，push_back中有从尾部pop所有小于value的值得操作，但pop操作最多执行次数和push_back次数相同，所以均摊到每个元素上还是O(1);
// 最小值同理；
// (已修复) MaxQueue发现bug，在同时入队连续的相同值时，dq_max并没有重复入队，会导致一些问题；请见cpp main中的测试用例；可能那道题给定不重复的正整数条件；
// 下面的MinQueue无此bug, 要修复MaxQueue的此bug，只需在value和dq_max.back相同时也压入value即可；

const int notFoundNum=-1; // 有些题目-1可能在值域中，请修改notFoundNum到不会使用的数，例如INT_MIN;
class MaxQueue {
    queue<int> q;
    deque<int> dq_max;
public:
    MaxQueue() {}
    
    int size() {
        return q.size();
    }

    int max_value() {
        if(q.empty())
            return notFoundNum;
        else
            return dq_max.front();
    }
    
    void push_back(int value) {
        q.push(value);
        while (!dq_max.empty() && dq_max.back()<value) // 时刻注意队列为空；
        {
            dq_max.pop_back(); // 被覆盖
        }
        dq_max.push_back(value);
    }
    
    int pop_front() {
        if(q.empty())
            return notFoundNum;
        
        int temp = q.front();
        q.pop();

        if(!dq_max.empty() && dq_max.front()==temp) {
            dq_max.pop_front();
        }
        return temp;
    }
};

// 最小队列，等价于上面队列的最大值；
class MinQueue {
    queue<int> q;
    deque<int> dq_min;
    // q即队列，dq_min维护最小值；
    // 入队一个小值时会导致之前入队的值在最小值中失效；（被更小值覆盖）
    // 入队一个大值时会在之前入队的小值出队时生效；
    // 出队的值一定大于等于dq_min记录的值，相等时说明最小值以出队，所以dq_min也出队；
public:
    MinQueue() {}

    int size() {
        return q.size();
    }

    int min_value() {
        if(dq_min.empty())
            return notFoundNum;
        else
            return dq_min.front();
    }

    void push_back(int value) {
        q.push(value);
        while(!dq_min.empty() && value<dq_min.back()) {
            dq_min.pop_back(); // 被小值覆盖；
        }
        dq_min.push_back(value);
    }

    int pop_front() {
        if(q.empty())
            return notFoundNum;
        
        int temp = q.front();
        q.pop();

        if(!dq_min.empty() && temp == dq_min.front())
            dq_min.pop_front();
        return temp;
    }
};

// 最大最小队列，只是将上面两种方法进行了结合；
// 同时维护最大值，最小值的队列；
class MaxMinQueue {
    queue<int> q;
    deque<int> dq_min, dq_max;
    // q即队列，dq_min维护最小值, dq_max维护最大值；
    // dq_min的维护方式如下：(dq_max类似)
    // 入队一个小值时会导致之前入队的值在最小值中失效；（被更小值覆盖）
    // 入队一个大值时会在之前入队的小值出队时生效；
    // 出队的值一定大于等于dq_min记录的值，相等时说明最小值以出队，所以dq_min也出队；
    // 重复值重复压入dq_min;
public:
    MaxMinQueue() {}

    int size() {
        return q.size();
    }

    int max_value() {
        if(q.empty())
            return notFoundNum;
        else
            return dq_max.front();
    }

    int min_value() {
        if(dq_min.empty())
            return notFoundNum;
        else
            return dq_min.front();
    }

    void push_back(int value) {
        // q
        q.push(value);
        // dq_min
        while(!dq_min.empty() && value<dq_min.back()) {
            dq_min.pop_back(); // 被小值覆盖；
        }
        dq_min.push_back(value);
        // dq_max
        while (!dq_max.empty() && dq_max.back()<value) // 时刻注意队列为空；
        {
            dq_max.pop_back(); // 被覆盖
        }
        dq_max.push_back(value);
    }

    int pop_front() {
        if(q.empty())
            return notFoundNum;
        
        // q
        int temp = q.front();
        q.pop();
        // dq_min
        if(!dq_min.empty() && temp == dq_min.front())
            dq_min.pop_front();
        // dq_max
        if(!dq_max.empty() && dq_max.front()==temp) {
            dq_max.pop_front();
        }
        return temp;
    }
};