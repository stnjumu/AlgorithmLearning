#include"DataStructure/array.h"
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

// 56. 合并区间
// 击败79%, 71%
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    int i=1,n=intervals.size();
    while(i<n) {
        // 法1. 分级判断
        // if(intervals[i][0]==ans.back()[0]) {
        //     ans.back()[1]=intervals[i][1];
        // }
        // else {
        //     if(intervals[i][0]<ans.back()[1]) {
        //         ans.back()[1]=max(ans.back()[1], intervals[i][1]);
        //     }
        //     else if(intervals[i][0]==ans.back()[1]) {
        //         ans.back()[1]=intervals[i][1];
        //     }
        //     else {
        //         ans.push_back(intervals[i]);
        //     }
        // }

        // 法2. 分成有交集和无交集两类
        if(intervals[i][0]<=ans.back()[1]) {
            ans.back()[1]=max(ans.back()[1], intervals[i][1]);
        }
        else {
            ans.push_back(intervals[i]);
        }

        i++;
    }
    return ans;
}

int main() {
    cout<<"合并区间"<<endl;
    vector<vector<int>> intervals{{1,3},{2,6},{8,10},{15,18}};
    printVectorVector(merge(intervals));

    intervals.assign({{1,4},{4,5},{8,10},{7,18}});
    printVectorVector(merge(intervals));

    return 0;
}