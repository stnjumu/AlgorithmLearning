#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

/* 基本用法
首先string可以看成是元素类型是字符的vector，vector支持的操作string全部支持；
string重载了>,==,<等比较运算符，比较大小是按照对应位置字符的ASCII值比较；
string重载了=赋值运算符，可以直接赋值，而不需要按C语言的字符数组一样必须调用strcpy了；
与字符串相关的stream流处理库和函数为sstream库和stringstream; 
    ! 注意：不要使用strstream库和该库的strstream等类，此库已被弃用，可完全被sstream库替代；
*/

void printVectorString(vector<string> strings, string name = "vector string") {
    cout<<name<<" = [";
    for(int i=0;i<strings.size();i++) {
        cout<<strings[i];
        if(i+1<strings.size()) {
            cout<<",";
        }
    }
    cout<<"]"<<endl;
}