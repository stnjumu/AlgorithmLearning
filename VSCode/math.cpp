#include"Math/Math.h"
#include"DataStructure/Array.h"
#include<iostream>
#include<assert.h>
using namespace std;

// 338. 比特位计数
// 暴力法：击败40%, 11%
int countBitsOfOneNum(int i) {
    int ans = 0;
    while(i!=0) {
        ans += i%2;
        i/=2;
    }
    return ans;
}
vector<int> countBits1(int n) {
    vector<int> ans;
    for(int i=0;i<=n;++i) {
        ans.push_back(countBitsOfOneNum(i));
    }
    return ans;
}
// my数学规律, 2i+1的最后一位B[0]=1, 4i+2, 4i+3的倒数第二位B[1]为0，...
// 更慢了，击败10%, 59%
vector<int> countBits(int n) {
    vector<int> ans(n+1, 0);
    int half = 1;
    while(half <= n) { // half==n也得进循环；
        // 每2half个数，[0, 2half), [2half, 4half) ..., 其中每组的后half个数的倒数第k位为1，所以+1;
        // 其中half = 2^k; 例如half = 1表示每个奇数的最后一位为1, 所以+1;
        int frontHalfFlag = true;
        int i = 0;
        int count = 0;
        while(i<=n) {
            if(frontHalfFlag == false) {
                // 是每组的后half个数；
                ++ans[i];
            }
            ++count;
            if(count==half) {
                count = 0;
                frontHalfFlag = ! frontHalfFlag; // 翻转
            }
            ++i;
        }

        half*=2;
    }
    return ans;
}

// TODO: 理解标答：https://leetcode.cn/problems/counting-bits/solution/bi-te-wei-ji-shu-by-leetcode-solution-0t1i/
// 三种方法都是时间O(n), 空间O(1)，下面只给出了一种示例代码——方法三
// 方法二：dp, 最高有效位；
// 方法三：dp, 最低有效位；
vector<int> countBits3(int n) {
    vector<int> bits(n + 1);
    for (int i = 1; i <= n; i++) {
        bits[i] = bits[i >> 1] + (i & 1);
    }
    return bits;
}
// 方法四：dp, 最低设置位；


int main() {
    cout<< fastPower(-1.0, -2147483648)<<endl;
    cout<< myPow3(2.0, -2)<<endl;

    for(int i=0;i<100;i++) {
        assert(int(sqrt(i)) == mySqrt(i)); // Nothing happen means mySqrt is right.
        // cout<< i << ","<<mySqrt(i)<<endl;
    }

    cout<<"比特位计数"<<endl;
    printVector(countBits(2));
    printVector(countBits(5));

    return 0;
}