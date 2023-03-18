#pragma once

#include<iostream>
#include<vector>
using namespace std;

template<class T>
void printVector(vector<T> nums, string name = "vector") {
    cout<<name<<" = ";
    for(auto n:nums)
        cout<<n<<" ";
    cout<<endl;
}
template<class T>
void printVectorVector(vector<vector<T>> nums, string name = "vector vector") {
    cout<<name<<" = [";
    for(int i=0;i<nums.size();i++) {
        cout<< "[";
        for(int j=0;j<nums[i].size();j++) {
            cout<< nums[i][j];
            if(j+1<nums[i].size()) { // 无符号数
                cout<< ",";
            }
        }
        cout<<"]";
        if(i+1<nums.size()) {
            cout<<",";
        }
    }
    cout<<"]"<<endl;
}