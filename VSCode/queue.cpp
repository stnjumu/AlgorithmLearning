#include<iostream>
#include"DataStructure/Array.h"
#include<assert.h>
#include<algorithm>
#include"DataStructure/Queue.h"
using namespace std;

// 239. 滑动窗口最大值
// 最大队列, O(n), 击败37%, 22%
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MaxQueue max_q;
    vector<int> ans;
    for(int i=0;i<nums.size();++i) {
        if(max_q.size()==k)
            max_q.pop_front();
        max_q.push_back(nums[i]);
        if(max_q.size()==k)
            ans.push_back(max_q.max_value());
    }
    return ans;
}

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

    cout<<"滑动窗口最大值"<<endl;
    vector<int> nums{1,3,-1,-3,5,3,6,7};
    printVector(maxSlidingWindow(nums, 3));
    
    return 0;
}