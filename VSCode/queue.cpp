#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include"DataStructure/Queue.h"
using namespace std;


int main()
{
    cout<<"最大队列With Bug"<<endl;
    MaxQueue mq;
    mq.push_back(1);
    mq.push_back(2);
    mq.push_back(2);
    mq.push_back(2);
    cout<<mq.max_value()<<endl; // 2
    cout<<mq.pop_front()<<endl; // 1
    cout<<mq.max_value()<<endl; // 2
    cout<<mq.pop_front()<<endl; // 2
    cout<<mq.max_value()<<endl; // 应该为2
    cout<<mq.pop_front()<<endl; // 2
    cout<<mq.max_value()<<endl; // 应该为2

    cout<<"最小队列"<<endl;
    MinQueue minq;
    minq.push_back(2);
    minq.push_back(1);
    minq.push_back(1);
    minq.push_back(1);
    cout<<minq.min_value()<<endl; // 1
    cout<<minq.pop_front()<<endl; // 2
    cout<<minq.min_value()<<endl; // 1
    cout<<minq.pop_front()<<endl; // 1
    cout<<minq.min_value()<<endl; // 1
    cout<<minq.pop_front()<<endl; // 1
    cout<<minq.min_value()<<endl; // 1


    
    return 0;
}