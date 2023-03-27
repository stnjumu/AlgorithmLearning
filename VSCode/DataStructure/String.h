#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

/* 基本用法
首先string可以看成是元素类型是字符的vector，vector支持的操作string全部支持；
string重载了>,==,<等比较运算符，比较大小是按照对应位置字符的ASCII值比较；
string重载了=赋值运算符，可以直接赋值，而不需要按C语言的字符数组一样必须调用strcpy了；
! string重载了+, +=运算符，用于字符串拼接，类似于append()函数，但使用场景不同；
    append可知拼接string, string的部分(substring), 字符数组(char *)，迭代器范围；但不能append单个字符(char)，与push_back函数刚好互补，两者配合可处理大部分应用；
    +和+=只能拼接string, char *, char；注+运算会返回新的临时string对象，+=则是在原对象后面追加，效率较高；
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