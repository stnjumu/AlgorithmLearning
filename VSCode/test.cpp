#include <vector>
#include <iostream>
#include <iterator>
#include<sstream>
using namespace std;

template<class T>
void printVectorOstreamIterator(vector<T> nums, string name = "vector") {
    cout<<name<<" = ";
    ostream_iterator<T> output_it(cout, " "); // 绑定cout到输出流的迭代器，每迭代一次会额外写入一个" "字符串；
    copy(nums.begin(), nums.end(), output_it); // 比上面printVector麻烦很多，只是看起来高级；
    cout<<endl;
}

void f(){ cout<<"f"<<endl;}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const int a = 10;
    const int *p = &a;
    int *q;
    q = const_cast<int *>(p);
    cout <<a<<" "<<*p<<" "<<*q<<endl;
    *q = 20;    //fine
    cout <<a<<" "<<*p<<" "<<*q<<endl; // 10 20 20
    cout <<&a<<" "<<p<<" "<<q<<endl;
    return 0;
}