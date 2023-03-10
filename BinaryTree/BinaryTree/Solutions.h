#pragma once
#include"TreeNode.h"
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

		int i = 0, j = nums_sort.size() - 1;
		while (j > i)
		{
			if (nums_sort[i] + nums_sort[j] == target)
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
};