#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;


int solution2(vector<int> &nums);
int solution_circle(vector<int> nums) {
    if(nums.size()<=2)
        return solution2(nums);
    // 思路：破圈法
    // 分成偷第一个和不偷第一个两种情况，则可形成符合solution2要求的输入；
    int back = nums.back();
    nums.pop_back();
    int ans1 = solution2(nums); // 不偷最后一个；

    nums.erase(nums.begin());
    nums.pop_back();
    int ans2 = solution2(nums) + back; // 偷最后一个；
    return max(ans1, ans2);
}

// 动态规划；时间O(n), 空间O(1)
int solution3(vector<int> &nums) {
    if (nums.size()==0)
        return 0;
    if (nums.size()==1)
        return nums[0];
    
    int dp_last_last = nums[0], dp_last= max(nums[0], nums[1]);

    for (size_t i = 2; i < nums.size(); i++)
    {
        int temp = dp_last;
        dp_last = max(dp_last, dp_last_last+nums[i]);
        dp_last_last = temp;
    }
    
    return dp_last;
}
// 动态规划；时间O(n), 空间O(n)
// 虽然本题前一个决策直接影响后一个决策，但影响距离只有1，所以仍是无后效性；
// dp[i]表示是否nums [0, i]的最优解，dp[i] = max(dp[i-1], dp[i-2]+nums[i])
int solution2(vector<int> &nums) {
    if (nums.size()==0)
        return 0;
    if (nums.size()==1)
        return nums[0];
    
    vector<int> dp;
    dp.resize(nums.size(), 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (size_t i = 2; i < dp.size(); i++)
    {
        dp[i] = max(dp[i-1], dp[i-2]+nums[i]); // ! 注意到dp[i]只与前两个dp有关系，所以实际上不需要一直保存所有dp；可优化空间到O(1), 见solution3
    }
    
    return dp.back();
}

int back_tracking1(vector<int> &nums, int ans, int start) {
    if (start>=nums.size())
        return ans;
    else
        return max(back_tracking1(nums, ans+nums[start], start+2), back_tracking1(nums, ans, start+1));
}
// 递归法，复杂度非常高O(n!)
int solution1(vector<int> &nums) {
    int ans=0;
    return back_tracking1(nums, ans, 0);
}

int main()
{
    // leetcode 198：从非负数组nums中选择若干个互补相邻的数，使数的总和最大；
    vector<int> nums{1,2,3,1}; // ans = 4
    cout<< solution1(nums)<<endl;
    cout<< solution2(nums)<<endl;
    cout<< solution3(nums)<<endl;
    nums.assign({2,7,9,3,1}); // ans = 12
    cout<< solution1(nums)<<endl;
    cout<< solution2(nums)<<endl;
    cout<< solution3(nums)<<endl;

    // leetcode 213: 从环形(第一个和最后一个相邻)的非负数组nums中选择若干个互补相邻的数，使数的总和最大；
    nums.assign({2,3,2}); // ans = 3
    cout<< solution_circle(nums)<<endl;
    nums.assign({1,2,3,1}); // ans = 4
    cout<< solution_circle(nums)<<endl;
    
    return 0;
}