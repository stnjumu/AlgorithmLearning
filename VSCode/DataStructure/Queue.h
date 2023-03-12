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
class MaxQueue {
    queue<int> q;
    deque<int> dq_max;
public:
    MaxQueue() {

    }
    
    int max_value() {
        if(q.empty())
            return -1;
        else
            return dq_max.front();
    }
    
    void push_back(int value) {
        q.push(value);
        while (!dq_max.empty() && dq_max.back()<value) // 时刻注意队列为空；
        {
            dq_max.pop_back();
        }
        if(dq_max.empty() || dq_max.back()>value)
            dq_max.push_back(value);
        // == value时不需要变动；
    }
    
    int pop_front() {
        if(q.empty())
            return -1;
        
        int temp = q.front();
        q.pop();

        if(!dq_max.empty() && dq_max.front()==temp) {
            dq_max.pop_front();
        }
        return temp;
    }
};
