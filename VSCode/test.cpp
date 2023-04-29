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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout<<-1%2<<endl;

    vector<int> v{1,2,2,4,8};
    ostream_iterator<int> output(cout,"*");
    copy(v.begin(),v.end(),output);
    cout<<endl;

    vector<string> strs{"hello", "world", "!"};
    printVectorOstreamIterator(strs, "iterator output");

    istringstream in("[]");
    char delimiter;
    in>>delimiter;
    cout<<delimiter<<endl;
    int a=-1;
    bool flag = bool(in>>a);
    cout<<flag<<endl;
    in>>delimiter;
    cout<<delimiter<<endl;
    return 0;
}