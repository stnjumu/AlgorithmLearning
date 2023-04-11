#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

double f(double x,int n) {
    if(n==1)
        return x;
    if(n%2==0) {
        double temp = f(x,n/2);
        return temp * temp;
    }
    else {
        return f(x,n/2)*f(x,n-n/2);
    }
}

// 50. 求幂Pow(x, n)
// 注：普通的O(n)的方法时间会超限；
// 法1：递归二分法，利用Pow(x, 2n) = Pow(x, n) * Pow(x, n)的性质，O(logn)
// 法2：位方法；根据n的二进制编码，例如：n=7=111B, 表示x^(2^2)*x^(2^1)*x^1 = x^4 * x^2 * x
// 而x^(y), y=2^i是通过迭代法在32次时间内运算出来的；
// 如果n每次循环取二进制的最低位，然后向右移位，则也可以在每次循环后将x^y平方一下，得x^(2y)；
// 此方法需要特别注意负指数，int负数右移会高位补0，最终移位得到-1=1111111...1B；
double fastPower(double x, int n) {
    // return x^n;
    if(n==0||x==1.0)
        return 1.0;
    if(x==-1.0 &&n % 2 ==0)
        return 1.0;
    if(x==-1.0&& n%2==1)
        return -1.0;
    if(x==0.0) {
        return 0.0;
    }
    if(n==-2147483648) // 因为n==MAX_MIN时，-n还==MAX_MIN; 无法转换成正指数运算；
        return 0.0;
    if(n<0) { // 转换成正指数运算，这种方法需要特别考虑-2147483648的情况；
        n = -n;
        x = 1/x;
    }

    // double xpow[32]{0.};
    return f(x, n);
}
// 法2.1 位方法的递归实现；
// https://leetcode.cn/problems/powx-n/solution/8xing-dai-ma-kuai-su-mi-de-jian-ming-xie-zktu/
// /2和%2配合可以替代>>1和&1，但一些细节不同；
double myPow(double x, int n) {
    if (n == 0) return 1.0;
    if (n == 1) return x;
    if (n == -1) return 1.0/x; // ! 右移的话，负数补1，最终得到-1而不是0；除以2的话最终会得到0；
    double sqrt = myPow(x, n >> 1);
    return sqrt * sqrt * myPow(x, n & 1);
}
// 法2.2 位方法的递归实现；来源同2.1
// C++中int m>0, (-m%n) == -(m%n); n>0, m%n == m%(-n)
// ! C++中，m%n的符号和m相同，和n无关；返回值等价于将m一直向0加减n，直到最接近0且仍和m同符号；
// TODO: 基于上，有m%n + m/n == m；确定下；
// 标答，快速幂，分析见OneNote算法笔记
double myPow2(double x, int n) 
{
    if (n == 0) return 1.0;
    double sum = 1.0, time = n > 0 ? x : 1.0/x;
    while (n)
    {
        if (n % 2)
            sum *= time;  
        time *= time;
        n /= 2;
    }
    return sum;
}
// 个人实现，仿照myPow2，先计算x^(2^i)数组；再位方法进行计算；
// 将这个数组计算过程融合到迭代中即可变成myPow2；
double myPow3(double x, int n) {
    vector<double> xpow2powi;
    if(n<0) {
        x = 1/x;
    }
    // xpow2powi[i] = x^(2^i)
    xpow2powi.push_back(x);
    double temp = x;
    for(int i=0;i<32;i++) {
        temp = temp * temp;
        xpow2powi.push_back(temp);
    }

    double ans = 1.0;
    int i=0;
    while(n!=0) {
        if(n%2!=0) { // 3%2 == 1, (-3)%2 == -1 
            ans *= xpow2powi[i];
        }
        i++;
        n/=2;
    }
    return ans;
}

// TODO: 用myPow2的二分法思路可以同样实现整数除法
// 剑指 Offer II 001. 整数除法 或 29. 两数相除

// TODO: 69. x的平方根
// 思路1： 二分法
// TODO: 思路2：牛顿法，自己定义f(x) = x^2 - C，即求f(x)的根，根据切线手算下一个迭代点坐标；
int mySqrt_Overflow(int x) {
    if(x<=1) {
        return x;
    }
    int left = 1, right = x-1;
    while(left<=right) {
        int mid = (left+right)/2;
        int mm = mid*mid;
        if(mm == x)
            return mid;
        if(mm < x) // mid及mid左边的都小于解
            left = mid + 1;
        else if(mm > x) // mid及mid右边都大于解
            right = mid-1;
    }
    // left左边都小于解，right右边都大于解；left<right表明left>解，所以刚好应返回left-1
    return left-1;
}
// ! 思路1的做法会乘法溢出，因为mid=right/2, right很大时，mid
int mySqrt(int x) {
    if(x<=1) {
        return x;
    }
    int left = 1, right = x-1;
    while(left<=right) {
        int mid = (left+right)/2;
        int x_div_m = x/mid;
        if(x_div_m == mid)
            return mid;
        if(x_div_m > mid) // 基本等价于mid*mid<x, mid及mid左边的都小于解
            left = mid + 1;
        else if(x_div_m < mid) // 基本等价于mid*mid>x, mid及mid右边都大于解
            right = mid-1;
    }
    // left左边都小于解，right右边都大于解；left<right表明left>解，所以刚好应返回left-1
    return left-1;
}

