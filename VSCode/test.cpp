#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

int main()
{
    vector<int> nums{1,3,4,2,2};
    vector<int> nums2{1,3,4,2,9};
    auto x = nums2>=nums;
    cout<< bool(nums2>=nums)<<endl;

    return 0;
}