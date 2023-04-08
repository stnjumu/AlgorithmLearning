#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 169.多数元素
// 排序后选中间的元素即可。O(nlogn)
// TODO: O(n)算法？https://leetcode.cn/problems/majority-element/
int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n=nums.size();
    return nums[n/2];
}

int main() {
    vector<int> nums{2,2,1,1,1,2,2};
    cout<<majorityElement(nums)<<endl;

    return 0;
}