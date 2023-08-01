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

vector<int> useQueueRemoveRepeat(vector<int>& nums, int k) {
    vector<int> ret;
    // nums只能遍历一遍；不可回溯；
    queue<int> nums_before;
    // queue<pair<int, int>> text;
    // text.emplace(1, 2);
    for(auto n: nums) {
        int size_nb= nums_before.size();
        bool find = false;
        for(int i=0;i<size_nb;i++) {
            if(n==nums_before.front()) find=true;
            nums_before.push(nums_before.front());
            nums_before.pop();
        }
        if(!find) {
            ret.push_back(n);
            nums_before.push(n);
            if(nums_before.size()>k) nums_before.pop();
        }
    }
    return ret;
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

    cout<<"遍历队列去除窗口内重复元素"<<endl;
    nums.assign({1,2,3,4,5,3,4,5,7,7,7,7,1});
    printVector(nums);
    printVector(useQueueRemoveRepeat(nums,3));
    printVector(useQueueRemoveRepeat(nums,2));
    
    return 0;
}