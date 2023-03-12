#pragma once
#include<assert.h>
// 正整数除法上取整
int ceil_A_divide_by_B(int a, int b) {
    assert(a>=1 && b>1); // 定理中是a>1&&b>1，我检查了下，a==1也可；
    return (a+b-1)/b; // 数学定理；
}

int ceil_2(int a) {
    assert(a>=1);
    return (a+1)/2;
}
