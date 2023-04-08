#include"DataStructure/Array.h"
#include<assert.h>
#include<algorithm>
#include<unordered_set>
using namespace std;

// 39. 组合总和
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

int main() {
    cout<<"组合总数"<<endl;
    vector<int> candidates{2,3,6,7};
    printVectorVector(combinationSum(candidates, 7));

    candidates.assign({2,3,5});
    printVectorVector(combinationSum(candidates, 8));

    candidates.assign({2});
    printVectorVector(combinationSum(candidates, 1));
}