#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include"DataStructure/Queue.h"
using namespace std;


int main()
{
    cout<<"最大队列"<<endl;
    MaxQueue mq;
    mq.push_back(1);
    mq.push_back(2);
    cout<<mq.max_value()<<endl; // 2
    cout<<mq.pop_front()<<endl; // 1
    cout<<mq.max_value()<<endl; // 2

    
    return 0;
}