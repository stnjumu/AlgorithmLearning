#pragma once

#include<iostream>
#include<vector>
using namespace std;

/*
vector重载了比较运算符，>, >=, ==, !=等；比较逻辑与string相同，可能是为了支持string的字典序比较而实现的；
    vector a, b; a>b的比较方式是从前到后逐元素比较，直到第一个分出大小的位置，则该位置谁大就是谁大；
        如果一长一短的vector比较，例如lena > len_b, 两者刚好前len_b个元素完全一样，则长的更大；
    ==, !=比较好理解，就是长度相同且对应元素相等则相等；

删除元素：
erase: 仅支持迭代器删除指定位置的元素；（后续元素前移，并减少size）
    erase(it); 删除迭代器it指向位置的元素，返回指向原来it+1位置元素的新位置的迭代器；
    erase(it_begin, it_end); 删除[it_begin, it_end)的所有元素，并返回指向原来it_end的元素的新位置的迭代器； 
remove: 将指定范围内满足条件的元素都移到尾部；常配合erase删除指定值的元素；
    a.erase(remove(a.begin(), a.end(), val), a.end()); 删除a中所有值为val的元素；
    remove为std的算法，只会改变容器内部顺序，而不会改变容器大小；
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