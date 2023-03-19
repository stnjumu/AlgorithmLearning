#pragma once

#include<iostream>
#include<vector>
using namespace std;

/*
vector重载了比较运算符，>, >=, ==, !=等；比较逻辑与string相同，可能是为了支持string的字典序比较而实现的；
    vector a, b; a>b的比较方式是从前到后逐元素比较，直到第一个分出大小的位置，则该位置谁大就是谁大；
        如果一长一短的vector比较，例如lena > len_b, 两者刚好前len_b个元素完全一样，则长的更大；
    ==, !=比较好理解，就是长度相同且对应元素相等则相等；
*/

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