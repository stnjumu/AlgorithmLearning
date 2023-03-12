#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<assert.h>
using namespace std;

// 155. 最小栈，常数时间内检索最小元素的栈；
// 最小栈同理；
class MinStack {
    stack<int> s, min_s;
    // min_s 每个元素对应s中对应位置及以下的所有元素；(注：下面的先进栈，top刚出栈)
    // 维护min.top()一直是s的min即可；
public:
    MinStack() {

    }
    
    void push(int val) {
        s.push(val);
        if(min_s.empty())
            min_s.push(val);
        else
            min_s.push(min(min_s.top(), val));
    }
    
    void pop() {
        s.pop();
        min_s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min_s.top();
    }
};