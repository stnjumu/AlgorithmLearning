#include"DataStructure/Array.h"
#include<assert.h>
#include<algorithm>
#include<unordered_set>
using namespace std;

// 39. 组合总和
// 和为target的所有组合
// 如果让求排列总数，一般遍历肯定超限；可以求每一个不同的组合，在对每个组合求排列数，再相加；可利用getPermutationNumOfRepeatNums函数in full_permutation.cpp求有重复元素的排列数；
void back_trace_combinationSum(vector<int>& candidates, int start, int target, vector<vector<int>> &ans, vector<int> &combination) {
    assert(target>=0);
    if(target==0) {
        ans.push_back(combination);
    }

    for(int i=start;i<candidates.size() && candidates[i]<=target; i++) {
        combination.push_back(candidates[i]);
        back_trace_combinationSum(candidates, i, target-candidates[i], ans, combination);
        combination.pop_back();
    }
}
// 击败88%, 63%
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> combination;
    sort(candidates.begin(), candidates.end());

    back_trace_combinationSum(candidates, 0, target, ans, combination);
    return ans;
}

// 78. 子集
// 类似于求所有组合；遍历法，每个元素选或不选，O(2^n), 击败100%, 8%
void back_trace_subsets(vector<int> &nums, int start, vector<vector<int>> &ans, vector<int> &temp) {
    if(start>=nums.size()) {
        ans.push_back(temp);
        return;
    }

    // 不取
    back_trace_subsets(nums, start+1, ans, temp);
    // 取
    temp.push_back(nums[start]);
    back_trace_subsets(nums, start+1, ans, temp);
    temp.pop_back();
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> temp;
    vector<vector<int>> ans;
    int start = 0;
    back_trace_subsets(nums, start, ans, temp);
    return ans;
}

int main() {
    cout<<"组合总数"<<endl;
    vector<int> candidates{2,3,6,7};
    printVectorVector(combinationSum(candidates, 7));

    candidates.assign({2,3,5});
    printVectorVector(combinationSum(candidates, 8));

    candidates.assign({2});
    printVectorVector(combinationSum(candidates, 1));

    cout<<"子集"<<endl;
    vector<int> nums{1,2,3};
    printVectorVector(subsets(nums));
    nums.assign({0});
    printVectorVector(subsets(nums));
}