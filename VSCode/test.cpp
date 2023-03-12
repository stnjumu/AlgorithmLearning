#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

int findDuplicate(vector<int>& nums) {
        int n=nums.size();
        if(n==1)
            return nums[0];
        int x=0;
        for(int i=1;i<n;i++)
            x^=i;
        for(int i=0;i<n;i++)
            x^=nums[i];
        return x;
}

int main()
{
    vector<int> nums{1,3,4,2,2};
    cout<<findDuplicate(nums)<<endl;
    return 0;
}