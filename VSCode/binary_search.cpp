#include<algorithm>
#include"Math/Math.h"
#include<assert.h>
// 二分法实现求平方根，注意乘法溢出怎么解决；

bool canFinish(vector<int> &piles, int h, int k) {
    int h_need = 0;
    for(int i = 0; i<piles.size();i++) {
        h_need += (piles[i]+k-1)/k; // 上取整
        if(h_need>h)
            return false;
    }
    return true;
}
// 875. 爱吃香蕉的珂珂
// 左闭右闭，可行解 in [left, right], while条件(left<=right), 迭代条件：left=mid+1, right=mid-1; 结束时left=right+1
int minEatingSpeed(vector<int>& piles, int h) {
    int right = *max_element(piles.begin(), piles.end());
    int left = 1;
    while(left<=right) {
        int mid = (left+right)/2;
        if(canFinish(piles,h, mid)) { // mid可以，mid和mid右边都可以；
            right = mid -1; // 保证right的右边都可以；
        }
        else { // mid不行，mid和mid左边都不行；
            left = mid +1; // 保证left的左边都不可以；
        }
    }
    // left左边不行，right右边行；left==right+1
    return right+1; // left也行
}
// 左开右闭，可行解 in [left, right)，while条件(left<right), 迭代条件: left=mid+1, right=mid; 结束时left=right
int minEatingSpeed2(vector<int>& piles, int h) { // 结果显示这个稍快一点
    int right = *max_element(piles.begin(), piles.end());
    int left = 1;
    while(left<right) { // 少循环一次；
        int mid = (left+right)/2;
        if(canFinish(piles,h, mid)) { // mid可以，mid和mid右边都可以；
            right = mid; // 保证right和right的右边都可以；
        }
        else { // mid不行，mid和mid左边都不行；
            left = mid +1; // 保证left的左边都不可以；
        }
    }
    // left左边不行，right和right右边行；left==right
    return left;
}
// 左开右闭和左闭右闭是两种风格，很难说哪种更好，个人习惯左开右闭；

// 剑指 Offer 11. 旋转数组的最小数字
// TODO: 学习标答做法；
int minArray(vector<int>& numbers) {
    // 奇怪现象，去掉assert会导致运行时间增长；
    int left = 0, right = numbers.size()-1;
    if(right == 0 || numbers[0]<numbers[right]) // right==0即只有一个元素，后面判断的则是没有旋转的情况；
        return numbers[0];
    
    // 将数组分为左右两部分，左边即没有旋转，右边即将左边小的旋转过去的；
    // 维护left一直指向左边，right一直指向右边；
    while(left<right-1) {
        assert(numbers[left]>=numbers[right]);
        int mid = (left+right)/2;
        // 有冗余判断；
        if(numbers[mid]>numbers[left] || numbers[mid]>numbers[right]){ // mid在左边
            left = mid;
            continue;
        }
        else if(numbers[mid]<numbers[left] || numbers[mid]<numbers[right]){ // mid在右边
            right = mid;
            continue;
        }
        else { // mid不确定；
            assert(numbers[left] == numbers[mid] && numbers[mid]==numbers[right]);
            // 特殊情况，不能确定mid在哪边；只能把left和right做一点移动；
            if(numbers[left+1]>=numbers[left])
                left++;
            if(numbers[right-1]<=numbers[right])
                right--;
        }

    }
    // left == right - 1
    return numbers[right];
}

// 4. 寻找两个正序数组的中位数
// 思路见array.cpp，其中一种方法是二分法；

int main() {
    vector<int> piles{3,6,7,11};
    cout<<minEatingSpeed(piles, 8)<<endl;
    
    piles.assign({30,11,23,4,20});
    cout<<minEatingSpeed(piles, 5)<<endl;
    
    piles.assign({30,11,23,4,20});
    cout<<minEatingSpeed(piles, 6)<<endl;

    vector<int> numbers{3,4,5,1,2};
    cout<<minArray(numbers)<<endl;

    numbers.assign({2,2,2,0,1});
    cout<<minArray(numbers)<<endl;

    numbers.assign({1,3,5});
    cout<<minArray(numbers)<<endl;

    numbers.assign({2,2,2,2,2,2});
    cout<<minArray(numbers)<<endl;

    numbers.assign({3,1});
    cout<<minArray(numbers)<<endl;

    numbers.assign({3,3,1,3});
    cout<<minArray(numbers)<<endl;

    return 0;
}