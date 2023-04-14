#include"DataStructure/Array.h"

// 96. 不同的二叉搜索树
int numTrees(int n) { // n>=1
    // dp, dp[n]表示解，dp[n]=\sum_i (dp[i-1]*dp[n-i]); 以i为根，左子树个数*右子树个数；
    vector<int> dp(n+1,0);
    dp[0]=1; // 利于计算；
    dp[1]=1; // 选1为根，左右都是空，只有一种，但dp[0]*dp[0]=1; 也可以并到循环中；
    for(int i=2;i<=n;++i) {
        for(int j=1;j<=i;++j) {
            dp[i]+=dp[j-1]*dp[i-j];
        }
    }
    return dp[n];
}


int main() {
    cout<< "不同的二叉搜索树"<<endl;
    cout<<numTrees(3)<<endl;
    cout<<numTrees(1)<<endl;

    return 0;
}