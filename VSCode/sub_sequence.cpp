#include"DataStructure/Array.h"
#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<string>
#include<unordered_set>
using namespace std;

// 子序列，可以不连续

// 1143. 最长公共子序列
// 定义dp[i,j], i in [0, m), j in [0, n), 表示text1[0, i]和text2[0,j]的最长公共子序列；
// dp[i,j] = dp[i-1,j-1]+1,  if text1[i]==text2[j]
// dp[i,j] = max(dp[i-1,j], dp[i,j-1]), if text1[i]!=text2[j]
// dp[m-1, n-1]即为所求；
// 若设dp[-1, j] = dp[i, -1] = 0，则可以简化计算流程; 将dp下标全部+1即能作为C++数组的下标；
int length_longest_common_subsequence_dp(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    if (m==0||n==0)
    {
        return 0;
    }
    
    vector<vector<int>> dp;
    for(int i=0;i<m+1;i++) { // 第一行全部是0
        vector<int> temp;
        temp.assign(n+1, 0); // 第一列全部是0
        dp.push_back(temp);
    }
    for(int i=1;i<m+1;i++) {
        for(int j=1;j<n+1;j++) {
            if(text1[i-1]==text2[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[m][n];
}

// 300. 最长严格递增子序列 (array.cpp中又做了一遍)
// 暴力法：O(n!)
// 思路1：动态规划，构造子问题dp[i]表示以nums[i]结尾的最长严格递增子序列长度；具体分析见下；
// TODO: 思路2：贪心；注意到在判断后面的数和一个序列是否可以构成更长的严格递增子序列长度时，只需比较该数和序列的最后一个数；与之前的数没有关系；
//      所以可以仅记录每个长度的严格递增子序列的最后一位；并且相同长度的严格递增子序列的最后一位可以只记录最小值；
//      在查询后面的数和已有序列能构成的最长严格递增子序列时，只需找到第一个大于它的位置，就是当前以该数结尾的最长严格递增子序列；
//  例如：维护的序列最后一位为[1, 4, 8]，则下一个数为5时，5可以和以4结尾的序列(可能使[1,4])构成更长序列，可以更改维护的序列为[1, 4, 5] (贪心, 因为[1,4,8能构成更长的序列的话，则[1,4,5也能构成，反之不行]])

// 思路1实现；
// dp[i]表示nums[0, i]中以nums[i]结尾的最长严格递增子序列长度；
// dp[i] = max_j{ dp[j]+1 if nums[j]< nums[i] else 1}, j in range[0, i)
// 初始化dp全为1，则可忽略递推式中的1；
int length_longest_increasing_subsequence_dp(vector<int>& nums) {
    if(nums.size()==1)
        return 1;
    
    vector<int> dp;
    dp.assign(nums.size(), 1);

    for (size_t i = 1; i < dp.size(); i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if(nums[j]<nums[i]) {
                // 可相对dp[j]变长1
                if(dp[i]<dp[j]+1)
                    dp[i] = dp[j]+1;
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}


void back_trace(vector<vector<int>> &ans, vector<int> &nums, int start, vector<int> &ascent) {
    if(start>=nums.size()){
        return;
    }
    
    unordered_set<int> searched_num;
    
    for(int i=start;i<nums.size();i++) {
        if(searched_num.find(nums[i])==searched_num.end()) {
            searched_num.insert(nums[i]);
            if(ascent.empty() || nums[i]>=ascent.back()) {
                ascent.push_back(nums[i]);
                if(ascent.size()>=2)
                    ans.push_back(ascent); // 一个递增子序列；
                back_trace(ans, nums, i+1, ascent);
                ascent.pop_back();
            }
        }
    }
}
// 491. 递增子序列
// ! 求所有不重复的递增子序列，由于要记录每个序列，而每个位置都可以做为子序列开始，每个位置都要考虑选或不选，具有明显的后效性，非dp问题；
// ! 如果只是求最长递增子序列，长度是没有后效性的，而这个问题也具有最优子结构性质，所以可以用dp;
// 经典的回溯法例题，和之前做过的交换法求所有子排列的问题的思路完全相同，见full_permutation.cpp；
vector<vector<int>> findSubsequences(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> ascent;
    back_trace(ans, nums, 0, ascent);
    return ans;
}

int main()
{
    cout<< "最长严格递增子序列"<<endl;
    vector<int> nums{10,9,2,5,3,7,101,18};
    cout<<length_longest_increasing_subsequence_dp(nums)<<endl;

    nums.assign({0,1,0,3,2,3});
    cout<<length_longest_increasing_subsequence_dp(nums)<<endl;

    nums.assign({7,7,7,7,7,7,7});
    cout<<length_longest_increasing_subsequence_dp(nums)<<endl;

    nums.assign({4,10,4,3,8,9});
    cout<<length_longest_increasing_subsequence_dp(nums)<<endl;

    cout<< "最长公共子序列"<<endl;
    string text1("abcde"), text2("ace");
    cout<<length_longest_common_subsequence_dp(text1,text2)<<endl;

    text1.assign("abc");
    text2.assign("abc");
    cout<<length_longest_common_subsequence_dp(text1,text2)<<endl;
    
    text1.assign("abc");
    text2.assign("def");
    cout<<length_longest_common_subsequence_dp(text1,text2)<<endl;

    cout<< "递增子序列"<<endl;
    nums.assign({4,6,7,7});
    printVectorVector(findSubsequences(nums));

    nums.assign({4,4,3,2,1});
    printVectorVector(findSubsequences(nums));

    return 0;
}