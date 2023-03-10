#include <stdio.h>
#include"DataStructure/DList.h"
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main()
{
    // DList x(vector<int> ({1,2,3,4,5}));
    // x.print();
    // x.push_back(6);
    // x.print();
    vector<int> v{1,2};
    cout<< find(v.begin(),v.end(), 2)-v.begin()<<endl;
    return 0;
}