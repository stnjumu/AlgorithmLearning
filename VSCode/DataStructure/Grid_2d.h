#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<cctype>
#include<limits>
#include<map>
#include<set>
using namespace std;

// 方向数组：direction array
// 右下 (下是x增大，右是y增大)
vector<vector<int>> direction2{{0,1},{1,0}};
// 上下左右
vector<vector<int>> direction4{{-1,0},{1,0},{0,-1},{0,1}};
// 上下左右，和4个斜对角方向; 从上开始顺时针方向;
vector<vector<int>> direction8{{-1,0},{-1,1},{0,1},{1,1},
                                {1,0},{1,-1},{0,-1},{-1,-1}};
// examples
void printNextPositions4(int x,int y, int m, int n) {
    // position = (x, y), grid shape = m*n; x in [0, m), y in [0, n)
    cout<< "next positions of ("<<x<<","<<y<<") is "<<endl;
    // driection=4, 上下左右
    for(auto dir: direction4) {
        int new_x=x+dir[0];
        int new_y=y+dir[1];
        // ! 特别注意x,y和m,n对应关系，千万别反了
        if(new_x<0 || new_x>=m) continue;
        if(new_y<0 || new_y>=n) continue;
        // using new_position (new_x, new_y)
        cout<< "("<<new_x << ","<<new_y<<")"<<endl;
    }
}

// 更快的方向数组：direction array faster
// 右下 (下是x增大，右是y增大)
int arrayDirection2[2][2]={{0,1},{1,0}};
// 上下左右
int arrayDirection4[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
// 上下左右，和4个斜对角方向; 从上开始顺时针方向;
int arrayDirection8[8][2]={{-1,0},{-1,1},{0,1},{1,1},
                                {1,0},{1,-1},{0,-1},{-1,-1}};
// examples
void printArrayNextPositions4(int x,int y, int m, int n) {
    // position = (x, y), grid shape = m*n; x in [0, m), y in [0, n)
    cout<< "next positions of ("<<x<<","<<y<<") is "<<endl;
    // driection=4, 上下左右
    for(int i=0;i<4;++i) {
        int new_x= x + arrayDirection4[i][0];
        int new_y= y + arrayDirection4[i][1];
        // ! 特别注意x,y和m,n对应关系，千万别反了
        if(new_x<0 || new_x>=m) continue;
        if(new_y<0 || new_y>=n) continue;
        // using new_position (new_x, new_y)
        cout<< "("<<new_x << ","<<new_y<<")"<<endl;
    }
}
