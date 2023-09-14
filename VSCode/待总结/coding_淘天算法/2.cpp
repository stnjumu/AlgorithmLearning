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

const vector<int> not_prime{4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27, 28, \
 30, 32, 33, 34, 35, 36, 38, 39, 40, 42, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 60, \
 62, 63, 64, 65, 66, 68, 69, 70, 72, 74, 75, 76, 77, 78, 80, 81, 82, 84, 85, 86, 87, 88, 90, 91, \
 92, 93, 94, 95, 96, 98, 99, 100, 102, 104, 105, 106, 108, 110, 111, 112, 114, 115, 116, 117, 118, \
 119, 120, 121, 122, 123, 124, 125, 126, 128, 129, 130, 132, 133, 134, 135, 136, 138, 140, 141, 142, \
 143, 144, 145, 146, 147, 148, 150, 152, 153, 154, 155, 156, 158, 159, 160, 161, 162, 164, 165, 166, \
 168, 169, 170, 171, 172, 174, 175, 176, 177, 178, 180, 182, 183, 184, 185, 186, 187, 188, 189, 190, \
 192, 194, 195, 196, 198,
};

bool is_not_prime(int n) {
    return find(not_prime.begin(), not_prime.end(), n) != not_prime.end();
}

// 题目：
// 淘天算法笔试
// 1.n个数组，每个数组是由1～an组成，设定从数组中拿m个数，只能从每个数组的最大值往下拿比如1～10的数组要先拿10再拿9..，请问拿m个数的最大值和最小值 数据规模 n = 10^5, an = 10^5
// ! 2.构造一个1-100的整数组成的数组，要求相邻两个数不能相同，相邻的两个数之和不能为质数，长度为100的话，请问有多少种构造方法？
// 3.定义好串是0/1字符串中0/1数量相等的串，输入一个长度不超过300的串，它的子序列的所有字串中有多少个好串？

// dp(i, j), 表示长度为j且以i开头的满足要求的序列；
// 则所求即 sum of dp(i, 100) for all i in [1, 100]；
// 递推关系式：dp[i,j] = sum of dp[k, j-1], for all k in [1, 100], k!=i and is_not_prime(k+1), 

int main() {
    vector<vector<int>> dp(101, vector<int>(101, 0));
    for(int i=1;i<=100;i++) {
        dp[i][1] = 1;
    }
    for(int j=1;j<=100;j++) {
        for(int i=2;i<=100;i++) {
            for(int k=1;k<=100;k++) {
                if(k!=i && is_not_prime(k+i)) {
                    dp[i][j] += dp[k][j-1];
                }
            }
        }
    }
    int ans = 0;
    for(int i=1;i<=100;i++) {
        ans+= dp[i][100];
    }
    cout<< ans<<endl; // 1731548979, 不确定对不对；

    return 0;
}