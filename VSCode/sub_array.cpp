#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

/*子数组, sub array, 连续子数组
常用方法有滑动窗口，dp等；

最大子数组和，最大子数组积，和大于等于target的长度最小的子数组
环形最大子数组和
*/

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

// 152. 乘积最大子数组
// ! 利用前缀积，因为0的存在，所以走不通，千万注意此点，而且前缀积/前缀和的代码比较复杂，甚至不如直接遍历；
// 直接遍历法, O(n^2), 击败5%, 72%
int maxProduct(vector<int>& nums) {
    int ans = INT_MIN;
    int partialProduct;
    for(int i=0;i<nums.size();++i) {
        partialProduct = 1;
        for(int j=i;j<nums.size();++j) {
            partialProduct *= nums[j];
            if(partialProduct>ans)
                ans = partialProduct;
            if(partialProduct==0)
                break;
        }
    }

    return ans;
}
// dp; dp_max[i]表示nums[0, i]的最大正乘积，dp_min[i]表示nums[0,i]的最小负乘积；
// if nums[i]>0, dp_max[i]= max(nums[i], dp_max[i-1]*nums[i]), dp_min[i]= dp_min[i-1]*nums[i]
// if nums[i]<0, dp_min[i]= min(nums[i], dp_max[i-1]*nums[i]), dp_max[i]= dp_min[i-1]*nums[i]
// if nums[i]==0, dp_max[i]= dp_min[i-1] = 0;
// ! 这种dp定义初始值无法确定；如果使用0或1或-1或nums[0]等都不行，见反例{-2};
// 注意到dp[i]只与dp[i-1]有关，所以可优化dp空间；

// * 更正：dp_max[i]表示nums[0, i]的最大乘积，dp_min[i]表示nums[0,i]的最小乘积；
// dp_max[i] = max(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1], nums[i]);
// dp_max[i] = min(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1], nums[i]);
// O(n), 击败62%, 82%
int maxProductDP(vector<int>& nums) {
    int dp_max=nums[0], dp_min=nums[0];
    int ans = nums[0];
    for(int i=1;i<nums.size();++i) {
        int old_max = dp_max; // ! 注意dp_max
        dp_max = max(max(nums[i], dp_max*nums[i]), dp_min*nums[i]);
        dp_min = min(min(nums[i], old_max*nums[i]), dp_min*nums[i]);
        ans = max(ans, dp_max);
    }

    return ans;
}

// TODO: 环形最大子数组和
// 思路1：求非环形的最大子数组和，求所有元素和sum，将所有元素取负数后，再求最大子数组和，则sum+负数组的最大子数组和即环形部分的最大子数组和；两者取最大即可；(记得做过此题，但忘记在哪了)
// 思路2：将n个元素的环形拓展成2n-1个元素的数组，且限制最大子数组长度为n, 则问题就转换成求新数组的长度小于等于n的最大子数组和；(未验证正确与否)

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

    cout<<"乘积最大子数组"<<endl;
    nums.assign({2,3,-2,4});
    cout<< maxProductDP(nums)<<endl;
    nums.assign({-2});
    cout<< maxProductDP(nums)<<endl;
    nums.assign({-4, -3, -2});
    cout<< maxProductDP(nums)<<endl;

    return 0;
}