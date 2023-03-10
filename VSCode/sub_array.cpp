#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

// 53. 最大子数组和
// 子数组是数组的一个连续部分
// 思路1: 动态规划；O(n), 空间最好O(1), 已实现；
// TODO: 思路2：分治法；不懂；

int maxSubArrayDP(vector<int> &nums) {
    // 由下面两种解法可知，本题无后效性；
    // 定义子问题: dp[i]，表示以nums[i]结尾的所有子数组的和的最大值；
    // 则递推式：dp[i] = dp[i-1]+nums[i] if dp[i-1] > 0 else nums[i], dp[0]=nums[0]
    // 则递推式：dp[i] = dp[i-1]+nums[i] if dp[i-1] > 0 else nums[i], dp[0]=nums[0]
    // 注意到dp[i]只与dp[i-1]有关，可以只保留dp_last，节省空间；即为maxSubArray2的做法；
    // 求最大值都是O(n)，不论是中间每次都判断，还是最后用max_element;

    // 时间O(n), 空间O(n)
    if(nums.size()==0)
        return 0;
    vector<int> dp;
    dp.push_back(nums[0]);
    for (size_t i = 1; i < nums.size(); i++)
    {
        if (dp.back()>0)
        {
            dp.push_back(nums[i]+dp.back());
        }
        else {
            dp.push_back(nums[i]);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int maxSubArray2(vector<int>& nums) { // 版本2，对思路1的完善，可支持全负；
    // 此种解题的思路非常像动态规划了；
    // 时间O(n), 空间O(1)
    // 注意：线上judge的话，空间复杂度一般没要求的话不需要强求；代码难写的同时也难理解；
    if(nums.size()==0)
        return 0;
    
    int max = nums[0], sum_last = nums[0];

    for (size_t i = 1; i < nums.size(); i++)
    {
        if(sum_last <= 0) {
            sum_last = nums[i];
        }
        else {
            sum_last += nums[i];
            
        }
        if(max < sum_last)
            max = sum_last;
    }
    return max;
}

int maxSubArray1(vector<int>& nums) {
    int max = 0;
    int sum_last = 0;

    for (size_t i = 0; i < nums.size(); i++)
    {
        if (nums[i]>0)
        {
            sum_last += nums[i];
            if(max < sum_last) {
                max = sum_last;
            }
        }
        else {
            sum_last += nums[i];
            if (sum_last < 0)
            {
                sum_last = 0; // 清0
            }
        }
    }
    // 以上代码在存在正值和0时是对的；但全负数的话max=0;
    if(max == 0)
    {
        max = *max_element(nums.begin(), nums.end());
    }
    return max;
}

int main()
{
    vector<int> nums{-2,1,-3,4,-1,2,1,-5,4};
    cout<<maxSubArray1(nums)<<endl;
    cout<<maxSubArray2(nums)<<endl;
    cout<<maxSubArrayDP(nums)<<endl;

    nums.assign({-1});
    cout<<maxSubArray1(nums)<<endl;
    cout<<maxSubArray2(nums)<<endl;
    cout<<maxSubArrayDP(nums)<<endl;

    nums.assign({5,4,-1,7,8});
    cout<<maxSubArray1(nums)<<endl;
    cout<<maxSubArray2(nums)<<endl;
    cout<<maxSubArrayDP(nums)<<endl;

    return 0;
}