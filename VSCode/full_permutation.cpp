#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<unordered_set>
using namespace std;
// 回溯法；
// 交换法确定每层选定的值；此法无法按字典序输出；
void back_tracking(vector<int> &nums, int start) {
    if(start>=nums.size()) {
        for(auto num:nums) {
            cout<< num<<" ";
        }
        cout<<endl;
        return;
    }

    for (size_t i = start; i < nums.size(); i++)
    {
        swap(nums[start], nums[i]);
        back_tracking(nums, start+1);
        swap(nums[start], nums[i]);
    }
}

void back_tracking_unique(vector<int> &nums, int start) {
    if(start>=nums.size()) {
        for(auto num:nums) {
            cout<< num<<" ";
        }
        cout<<endl;
        return;
    }

    unordered_set<int> num_exist; // 每一层递归只遍历当层没遍历过的；
    for (size_t i = start; i < nums.size(); i++)
    {
        if(num_exist.count(nums[i])==0) { // 没有遍历过
            num_exist.insert(nums[i]);
            swap(nums[start], nums[i]);
            back_tracking_unique(nums, start+1);
            swap(nums[start], nums[i]);
        }
    }
}

void full_permutation_swap(vector<int> &nums, bool has_repeating_num) {
    if(has_repeating_num)
        back_tracking_unique(nums, 0);
    else
        back_tracking(nums, 0);
}

// 复现标准库的算法实现；基于此实现的全排列方法自动支持重复数字的序列；
bool my_next_permutation(vector<int> &nums) {
    // find last s, s.t. nums[s] < nums[s+1]
    // if not exist, then nums in descending order
    int s = nums.size()-2;
    while (s>=0)
    {
        if(nums[s]<nums[s+1])
            break;
        s--;
    }
    if(s>=0) { // find s, next_premutation exists.
        // find last b, s.t. nums[s] < nums[b]
        int b = nums.size()-1;
        while (b>s)
        {
            if(nums[s]<nums[b])
                break;
            b--;
        }
        assert(s<b);

        // swap nums[s], nums[b], and nums[s+1:] in descending order, reverse them;
        swap(nums[s], nums[b]);
        reverse(nums.begin()+s+1, nums.end());
        return true;
    }
    else {
        // all descending order. next_permutation is all ascending order.
        reverse(nums.begin()+s+1, nums.end());
        return false; // false表示一次遍历结束；
    }
    
}
void full_permutation(vector<int> &nums) {
    // next_permutation支持重复数字；生成的全排列中不会包含重复排列；
    do
    {
        for(auto num: nums)
            cout<<num<<" ";
        cout<<endl;
    // } while (next_permutation(nums.begin(), nums.end()));
    } while (my_next_permutation(nums));
    
}

int main() {
    cout<<"基于swap回溯法的全排列生成, 排列无顺序"<<endl;
    // vector<int> nums{1, 2, 3, 4};
    // full_permutation_swap(nums, false);
    vector<int> nums{1, 2, 2, 4};
    full_permutation_swap(nums, true);

    cout<<"非递归方法的全排列生成，排列按字典序"<<endl; 
    nums.assign({1, 2, 2, 4});
    full_permutation(nums);
    return 0;
}