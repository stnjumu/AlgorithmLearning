#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<assert.h>

using namespace std;

// TODO: 两数之和, 三数之和，最接近的三数之和，四数之和

// 1. 两数之和
// 暴力法：O(n^2)
// 哈希查找：O(n)
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hashtable;
    for(int i=0;i<nums.size();i++) {
        if(hashtable.find(nums[i])!=hashtable.end()) { // 已经有了
            if(nums[i]*2==target) // 主要解决相同的数相加刚好是target的特殊情况
                return {hashtable[nums[i]], i};
        }
        else
            hashtable[nums[i]]=i;
    }

    for (int i = 0; i < nums.size(); ++i) {
        auto it = hashtable.find(target - nums[i]);
        if (it != hashtable.end() && it->second!=i) { // ! 排除一个数的两倍刚好是target的情况
            return {it->second, i};
        }
    }
    return {};
}
// ! 标答, 非常优雅，值得学习；
vector<int> twoSum2(vector<int>& nums, int target) {
    unordered_map<int, int> hashtable;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = hashtable.find(target - nums[i]); // 利用a+b=target，遍历a或b都能得到答案，遍历到a时查找不到b，添加了a，遍历b时就会查找到a了；
        if (it != hashtable.end()) {
            return {it->second, i};
        }
        hashtable[nums[i]] = i;
    }
    return {};
}

// 15. 三数之和
// 暴力法：O(n^3)
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    // TODO:
}

int main() {
    cout<<"两数之和"<<endl;
    vector<int> nums{2,7,11,15};
    vector<int> ans = twoSum(nums, 9);
    cout<< ans[0]<<ans[1]<<endl;

    return 0;
}
