#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<assert.h>
#include<numeric>
#include<unordered_set>
#include<stack>
using namespace std;

// 1. 两数之和
// 思路1：遍历，O(n^2)
// 思路2：排序后，使用双指针排除法，O(nlogn) (已实现)
// 思路3：哈希表，利用哈希表存x，则再次查找target-y时每次O(1)，所以共O(n)，但是空间复杂度也是O(n)
class Solution1 {
public:
	string problem = "两数之和";
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> nums_sort;
		nums_sort.assign(nums.begin(), nums.end());
		//for (auto num : nums)
		//	nums_sort.push_back(num);
		sort(nums_sort.begin(), nums_sort.end());

		int i = 0, j = nums_sort.size()-1;
		while (j>i)
		{
			if (nums_sort[i]+nums_sort[j]==target)
			{
				break;
			}
			else if (nums_sort[i] + nums_sort[j] > target) // 排除j;
			{
				j--;
			}
			else // 排除i
			{
				i++;
			}
		}
		assert(j > i); // 题目默认有解；

		vector<int> ans;
		for (size_t k = 0; k < nums.size(); k++)
		{
			if (nums[k] == nums_sort[i] || nums[k] == nums_sort[j])
				ans.push_back(k);
		}
		return ans;
	}

	vector<int> twoSum_hash(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable;
		for (int i = 0; i < nums.size(); ++i) {
			auto it = hashtable.find(target - nums[i]);
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable[nums[i]] = i;
		}
		return {};
	}
	//  作者：LeetCode - Solution
	//	链接：https ://leetcode.cn/problems/two-sum/solution/liang-shu-zhi-he-by-leetcode-solution/
};
// 26. 删除重复项：即实现标准库的removeDuplicates, 原地删除重复项并返回新长度，不关心多余部分的数值；
class Solution26 {
public:
	string problem = "removeDuplicates";
	int removeDuplicates(vector<int>& nums) {
		int i = 0, j=1,n = nums.size();
		while (j<n)
		{
			if (nums[j]!=nums[i])
			{
				nums[++i] = nums[j++];
			}
			else
			{
				j++;
			}
		}
		return i + 1;
	}
};
// 27. 移除元素
// 31. 下一排列：next_permutation; 
// 可以把排列当成数字考虑，例如123456，数值大的排列在后面；考虑时把排列写出来会好思考很多；
// 三点：要增大；增大幅度要最小；
// 把后面的大数b和前面的小数s交换位置，则新排列会在旧排列的后面；
// 要想得到的新排列刚好在当前排列下一位，则必须保证新排列增加值最小；需要从后往前找第一个小数s, s后面几位有比s大的；例如123465中的4，564321中的5；
//		注意s右边的位必为降序，所以找s可找相邻的升序对
// 找到s后再找s后面比s大的数中最小的，记为b，例如：564321中的s=5, b=6, 512643中的s=2, b=3;
//		注意又可倒序找第一比s大的数，即为b；
// 将b,s交换后，(可断定原s位置之后仍为降序)，需要将原s位置之后的所有位按升序排列；

// 35. 二分查找
class Solution35 {
public:
	string problem = "binary_search and return index";
	int searchInsert(vector<int>& nums, int target) {
		// binary_search() in STL returns bool, not int.
		// nums升序;
		int left = 0, right = nums.size()-1; // size-1
		while (left<=right) // <可能会导致最后一个left == right的位置没有判断；
		{
			int mid = (left + right) / 2;
			if (nums[mid]==target)
			{
				return mid;
			}
			else if (nums[mid]<target)
			{
				left = mid+1;
			}
			else
			{
				right = mid-1;
			}
		}
		// 上述过程保证left左边都是小于target的，right右边全部大于target；
		// 最后left==right或right-1==left;
		return left;
	}
};
// 121. 买卖股票问题；给定股票一段时间的价格序列，[7,1,5,3,6,4]，求最大利润；
// 思路1：暴力O(n^2)
// 思路2：O(n): 用minRecordPrices记录每一天的历史最低；[7,1,5,3,6,4] -> 历史最低[7,1,1,1,1,1] -> 从历史最低买入但当天卖出的最大利润 [0,0,4,2,5,3]

// 136. 只出现一次数字
class Solution136 {
public:
	string problem = "只出现一次数字，其他数字全部出现两次；要求线性时间、常数空间。";
	int singleNumber(vector<int>& nums) {
		// 性质：数字a, a异或a=0; 且异或具有交换律和结合律；
		int ans = 0;
		for (auto num : nums)
			ans ^= num;
		return ans;
	}
};
// 137. 只出现一次数字2, 其他数字出现3次；
// 思路1：模3逻辑电路；思路2：将每个数字的每一位(&(1<<i)即可)提取出来: 0/1，再分别计数，最后模3可得只出现一次的数字的每一位；
// https://leetcode.cn/problems/single-number-ii/comments/

// 217. 存在重复元素； 219. 存在距离小于等于k的重复元素；
// 哈希表的应用；

// 268. 丢失的数字，给定范围[0, n]和n个数，找到那个数没有出现；
// 和136问题一样可以用异或解决；

// 594. 最长和谐子序列: 和谐数组：[3,2,3,2,2]等最大值和最小值只差刚好为1；
// 求nums的最长和谐子序列，则一种是用hash表计数；一种是排序后用统计相邻数字的个数；

// 628. 三个数最大乘积;
// 设max1, max2, max3分别表示第一、二、三大，min1, min2分别表示第一、二小；分情况讨论易知：
// 最大乘积只能在max1*max2*max3和min1*min2*max1之间存在；


// * 中等难度；
// TODO
// 137. 只出现一次的数字II (做一下,dp)

// 491. 递增子序列 (回溯)
class Solution491 {
public:
	vector<int> list;
	vector<vector<int>> ans;
	void backtracking(vector<int>& nums, int start) {
		if (start>=nums.size)
		{
			return;
		}
		for (size_t i = start; i < nums.size(); i++)
		{
			if (list.empty())
			{
				list.push_back(nums[i]);
			}
			else
			{
				if (list.back()<=nums[i])
				{
					list.push_back(nums[i]);
					ans.push_back(list);
				}
				else
				{
					continue;
				}
			}
			// 未完，未去重；
			backtracking(nums, i + 1);
			list.pop_back();
		}
	}
	vector<vector<int>> findSubsequences(vector<int>& nums) {

		backtracking(nums, 0);
	}
};