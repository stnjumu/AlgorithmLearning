#include<unordered_map>
#include<algorithm>
#include<assert.h>
#include"DataStructure/Array.h"

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
// 二分查找：O(n^2*logn)
// 排序+双指针：O(n^2)

int binarySearch(vector<int> &nums, int start, int target) {
    // nums有序, 从nums[start:]查找目标，存在则返回目标下标，如果不存在，返回-1
    int left=start, right=nums.size();
    // [left, right)
    while(left<right) { // 一般left<=ans<right对应于left<right, 循环直到left,right无法构成区间[left, right)
        int mid = (left+right)/2;
        if(nums[mid]>target) // left<=ans<mid
            right=mid;
        else if(nums[mid]<target) // mid+1<=ans<right
            left=mid+1;
        else
            return mid;
    }
    // left=right, left左边都小于target，right和right右边都大于target
    return -1;
}
vector<vector<int>> threeSum(vector<int>& nums) {
    int n= nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    int last_numi=-100000;
    for(int i=0;i<n;i++) {
        if(nums[i]!=last_numi && nums[i]<=0) {// ! 去除重复项，且第一个数>0时三个数不会相加为0
            last_numi=nums[i];
            int last_numj=-100000;
            for(int j=i+1;j<n;j++) {
                if(nums[j]!=last_numj) { // ! 去除重复项；
                    last_numj = nums[j];

                    int index = binarySearch(nums, j+1, -nums[i]-nums[j]); // 由于前第三个数可以由前两个数推出，所有可以只判断是否找到，可用STL的bool binary_search(begin, end);
                    if(index!=-1) { // find
                        ans.push_back({nums[i],nums[j],nums[index]});
                    }
                }
            }
        }
    }
    return ans;
}
// 最优：排序+双指针；每个i作为left, 从left右边找mid, right;
vector<vector<int>> threeSum2(vector<int>& nums) {
    int n= nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    
    for(int i=0;i<n;i++) {
        if(i>0 && nums[i]==nums[i-1]) // 重复
            continue;
        
        int left = i+1, right = n-1;
        while(left<right) {
            if(nums[i]+nums[left]+nums[right]==0) {
                ans.push_back({nums[i],nums[left],nums[right]});
                left++;
                while(left<right && nums[left]==nums[left-1]) {
                    left++;
                }
                right--;
                while(left<right && nums[right]==nums[right+1]) {
                    right--;
                }
            }
            else if(nums[i]+nums[left]+nums[right]>0) {
                right--;
                while(left<right && nums[right]==nums[right+1]) {
                    right--;
                }
            }
            else {
                left++;
                while(left<right && nums[left]==nums[left-1]) {
                    left++;
                }
            }
        }
    }
    return ans;
}

// 16. 最接近的三数之和
// TODO: 还可优化，击败46%, 5%
int threeSumClosest(vector<int>& nums, int target) {
    int n= nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    
    int minDest= 1000000; // ! 最小值必须大于|target|+3*|nums[i]|
    int minDest_threeSum=1000000;
    for(int i=0;i<n;i++) {
        if(i>0 && nums[i]==nums[i-1]) // 重复
            continue;
        // if(i>0 && nums[i-1]>target) // ! 之前就已经超了，后面只会大的更多，错了，target可能是负数；
        //     break;
        
        int left = i+1, right = n-1;
        while(left<right) {
            int sum = nums[i]+nums[left]+nums[right];
            int dest = sum - target;
            if(dest == 0) {
                return target;
            }
            else if(dest>0) {
                if(minDest > dest) {
                    minDest = dest;
                    minDest_threeSum = sum;
                }

                right--;
                while(left<right && nums[right]==nums[right+1]) {
                    right--;
                }
            }
            else {
                dest = -dest;
                if(minDest > dest) {
                    minDest = dest;
                    minDest_threeSum = sum;
                }

                left++;
                while(left<right && nums[left]==nums[left-1]) {
                    left++;
                }
            }
        }
    }
    return minDest_threeSum;
}


int main() {
    cout<<"两数之和"<<endl;
    vector<int> nums{2,7,11,15};
    vector<int> ans = twoSum(nums, 9);
    cout<< ans[0]<<ans[1]<<endl;

    cout<<"三数之和"<<endl;
    nums.assign({-1,0,1,2,-1,-4});
    printVectorVector(threeSum2(nums));

    nums.assign({0,1,1});
    printVectorVector(threeSum2(nums));

    nums.assign({0,0,0});
    printVectorVector(threeSum2(nums));

    nums.assign({0,0,0,0});
    printVectorVector(threeSum2(nums));

    cout<<"最接近的三数之和"<<endl;
    nums.assign({-1,2,1,-4});
    cout<<threeSumClosest(nums, 1)<<endl;

    nums.assign({0,0,0});
    cout<<threeSumClosest(nums,1)<<endl;

    nums.assign({-100,-98,-2,-1});
    cout<<threeSumClosest(nums,-101)<<endl;

    nums.assign({-1000,-1000,-1000});
    cout<<threeSumClosest(nums,10000)<<endl;

    return 0;
}
