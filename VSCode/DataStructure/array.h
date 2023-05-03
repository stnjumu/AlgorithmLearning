#pragma once

#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<numeric>
#include<assert.h>
// #include<VECTOR> // Window下C++头文件对大小写不敏感；
using namespace std;

/*
vector重载了比较运算符，>, >=, ==, !=等；比较逻辑与string相同，可能是为了支持string的字典序比较而实现的；
    vector a, b; a>b的比较方式是从前到后逐元素比较，直到第一个分出大小的位置，则该位置谁大就是谁大；
        如果一长一短的vector比较，例如lena > len_b, 两者刚好前len_b个元素完全一样，则长的更大；
    ==, !=比较好理解，就是长度相同且对应元素相等则相等；

vector内置删除函数:
    erase(it_begin, it_end); // 删除[it_begin, it_end)之间元素，比algorithm中通用函数更好用一些；
algorithm删除元素：
erase: 仅支持迭代器删除指定位置的元素；（后续元素前移，并减少size）
    erase(it); 删除迭代器it指向位置的元素，返回指向原来it+1位置元素的新位置的迭代器；
    erase(it_begin, it_end); 删除[it_begin, it_end)的所有元素，并返回指向原来it_end的元素的新位置的迭代器； 
remove: 将指定范围内满足条件的元素都移到尾部；常配合erase删除指定值的元素；
    a.erase(remove(a.begin(), a.end(), val), a.end()); 删除a中所有值为val的元素；
    remove为std的算法，只会改变容器内部顺序，而不会改变容器大小；
*/

void printBool(bool flag) {
    if(flag)
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
}

template<class T>
void printVector(vector<T> nums, string name = "vector") {
    cout<<name<<" = ";
    for(auto n:nums)
        cout<<n<<" ";
    cout<<endl;
}
template<class T>
void printVectorOstreamIterator(vector<T> nums, string name = "vector") {
    cout<<name<<" = ";
    ostream_iterator<T> output_it(cout, " "); // 绑定cout到输出流的迭代器，每迭代一次会额外写入一个" "字符串；
    copy(nums.begin(), nums.end(), output_it); // 比上面printVector麻烦很多，只是看起来高级；
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


// algorithm
// 自己实现的对int数组进行非稳定分组的简单函数, 左边小于pivot, 右边大于等于pivot
// 采用方法：双指针，Lomuto-Partition, 正向游走
// 注：稳定分组stable_partition一般需要额外O(n)的空间；而非稳定则O(1)空间即可;
// 一个指针指向LeftBack或RightBegin(初始化begin; 一个指针遍历
// 指向LeftBack时初始化为-1, Left为空时无意义；
// 指向RightBegin时初始化为begin(或0), Right为空时无意义；
// 注意两者使用时的区别，LeftBack先++再使用，而RightBegin先使用再++; 因为要交换rightBegin和<pivot的元素*i
// ! 以下两个函数仅经过简单测试
void mypartitionOnO1(vector<int> &nums, int pivot) {
    // 一个指针指向right.begin的前一个位置，即leftBack；维护循环前后指针指向left的最后一个元素(开始时指向-1)；
    // 遇到>=pivot的跳过；
    // 遇到<pivot的pos++, 再交换pos元素(right.begin)和i元素(<pivot的元素)
    int leftBack=-1;
    for(int i=0;i<nums.size();++i) {
        if(nums[i]<pivot) { // left需要新增一个
            leftBack++; // ++后暂时指向right.begin
            if(leftBack<i) // right非空，right为空则leftBack==i, 所以没有这个判断也对。
                swap(nums[leftBack], nums[i]); // 交换right.begin和新的<pivot的元素，这里会打乱原先后顺序；
        }
        // else 直接划为right，leftBack不需要任何变动；
    }
}
void mypartitionOnO1_it(vector<int>::iterator begin, vector<int>:: iterator end, int pivot) {
    // 迭代器it无法指向begin的前一个位置，即原来-1的位置；可以指向leftBack的后一个位置RightBegin，初始化为begin
    // 维护循环前后it指向left的最后一个元素(开始时指向-1)；
    // 遇到>=pivot的跳过；
    // 遇到<pivot的pos++, 再交换pos元素(right.begin)和i元素(<pivot的元素)
    vector<int>::iterator itRightBegin = begin; // 刚开始RightBegin没有元素；
    for(vector<int>::iterator it=begin;it!=end;it++) {
        if(*it<pivot) { // left需要新增一个
            if(itRightBegin!=it) // right非空，right为空则itRightBegin == i, 所以没有这个判断也对
                swap(*itRightBegin, *it); // 交换right.begin和新的<pivot的元素，这里会打乱原先后顺序；
            itRightBegin++; // RightBegin右移
        }
        // else 直接划为right，RightBegin不需要任何变动；
    }
}
// Lomuto-Partition还有反向游走，两者基本完全一样；
// Lomuto-Partition的期望交换次数为n/2-1/2， 因为每个小于pivot的基本都会交换一次；
// 还有更好的Hoare-Partition算法，采用双向游走，即双指针从两端向中间靠拢；每次交换可以将左边大于pivot的和右边小于pivot的进行交换，这里一次交换就顶上面的方法两次；
// Hoare-Partition的期望交换次数为n/6-1/3；为什么不是n/4，是因为两端元素交换前后不会影响中间元素是否交换，而上面方法前面的元素是否小于pivot会影响后面元素是否交换；
// 更详细说明请见：https://blog.csdn.net/qq_26552795/article/details/100193890和https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto/11550
// TODO: 实现Hoare-Partition;