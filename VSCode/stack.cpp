#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include"DataStructure/Stack.h"
using namespace std;

// 剑指 Offer 09. 用两个栈实现队列
class CQueue {
    stack<int> s1, s2;
    void moveS1ToS2() {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
public:
    CQueue() {

    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if(s2.empty()) {
            moveS1ToS2();
        }

        if(s2.empty()) {
            return -1;
        }
        else {
            int temp = s2.top();
            s2.pop();
            return temp;
        }
    }
};



int main()
{
    cout<<"最小栈"<<endl;
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-3);
    cout<<s.getMin()<<endl; // -3
    s.pop();
    cout<<s.top()<<endl; // 0
    cout<<s.getMin()<<endl; // -2

    cout<<"两个栈实现队列"<<endl;
    CQueue cq;
    cq.appendTail(3);
    cout<<cq.deleteHead()<<endl; // 3
    cout<<cq.deleteHead()<<endl; // -1
    cout<<cq.deleteHead()<<endl; // -1

    cq.appendTail(5);
    cq.appendTail(2);
    cout<<cq.deleteHead()<<endl; // 5
    cout<<cq.deleteHead()<<endl; // 2
    
    return 0;
}