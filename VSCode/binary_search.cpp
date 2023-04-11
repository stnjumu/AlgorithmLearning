#include<algorithm>
#include"Math/Math.h"
#include<assert.h>

/*
STL Algorithm
bool binary_search(it_begin, it_end, val), 判断val是否在[begin, end)之间，序列需有序；
iterator lower_bound(it_begin, it_end, val), 二分查找[begin,end)中第一个大于等于val的位置，序列需有序；iterator-it_begin即下标
iterator upper_bound(it_begin, it_end, val), 二分查找[begin,end)中第一个大于val的位置，序列需有序；iterator-it_begin即下标
*/
// 二分查找
int binarySearch(vector<int> &nums, int target) {
    // nums有序, 返回目标下标，如果不存在，返回应该插入的位置下标；
    int left=0, right=nums.size();
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
    return left;
}

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
        else { // mid不确定；例如：1,1,1,1,1,1,1,1,1，其中任何一个中间位置的1都可以变成0且满足旋转数组的要求，*left=*mid=*right=1，但完全无法确定0在哪一边，这种情况下必须两边都判断，O(n)，即无法根据既有信息去除一半；
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

// 33. 搜索旋转排序数组
int searchRotateArray(vector<int>& nums, int target) {
    // ! 题目限定元素互不相同, O(log n)
    // 如果可能有相同元素，则最坏O(n), 反例就是全1数组把中间某个1变成0，然后查找0的位置；
    int left=0, right=nums.size()-1;
    if(right<0) {
        return -1;
    }
    if(right==0) {
        if(nums[0]==target) {
            return 0;
        }
        else
            return -1;
    }

    // [left, right]对应判断条件left<=right
    while(left<=right) {
        int mid = (left+right)/2;
        
        if(nums[mid]==target)
            return mid;
        else if(nums[mid]>target) { // target可能在mid左边，也可能在右边的旋转部分
            if(nums[left]<nums[mid] || left==mid) { // ! 左边有序, 注意left==mid的特殊情况；[left, mid]有序，没有left==mid会误判断左边无序，而右边有序的情况，此时错误判断右边都>mid>target;反例就是[3,1]中查找1;
                if(nums[left]==target)
                    return left;
                if(nums[left]<target) // target在这个范围内；则target在左边
                    right = mid-1;
                else // target<*left, 只可能出现在旋转部分了
                    left = mid +1;
            }
            else { // 左边无序，则右边[mid, right]有序, 右边都>mid>target, 不能在右边；
                right = mid -1;
            }

        }
        else { // nums[mid]<target
            if(nums[left]<nums[mid] || left==mid) { // 左边[left,mid]有序，左边都<mid<target，不能在左边
                left=mid+1;
            }
            else { // 右边[mid, right]有序
                if(nums[right]==target)
                    return right;
                if(target<nums[right]) // target在右边范围内
                    left=mid+1;
                else
                    right = mid -1;
            }
        }
    }
    // left==right+1
    return -1;
}
// old AC版本；没考虑清楚left==mid的情况，但判断的多，所以没问题；
int searchRotateArray2(vector<int>& nums, int target) {
    // ! 题目限定元素互不相同, O(log n)
    // 如果可能有相同元素，则最坏O(n), 反例就是全1数组把中间某个1变成0，然后查找0的位置；
    int left=0, right=nums.size()-1;
    if(right<0) {
        return -1;
    }
    if(right==0) {
        if(nums[0]==target) {
            return 0;
        }
        else
            return -1;
    }

    while(left<=right) {
        int mid = (left+right)/2;
        if(nums[left]==target) // 直接判断left,和right就可以避免left==mid这种特殊情况
            return left;
        if(nums[right]==target)
            return right;
        
        if(nums[mid]==target)
            return mid;
        else if(nums[mid]>target) { // target可能在mid左边，也可能在右边的旋转部分
            if(nums[left]<nums[mid]) { // ! 左边有序, [left, mid]有序, left==mid时会判断错误，更新right，由于前面已经判断相邻的left, right不是target，所有right=mid-1没问题；
                if(nums[left]<target) // target在这个范围内；则target在左边
                    right = mid-1;
                else // target<*left, 只可能出现在旋转部分了
                    left = mid +1;
            }
            else { // 左边无序，则右边[mid, right]有序, 右边都>mid>target, 不能在右边；
                right = mid -1;
            }

        }
        else { // nums[mid]<target
            if(nums[left]<nums[mid]) { // 左边[left,mid]有序，左边都<mid<target，不能在左边
                left=mid+1;
            }
            else { // 右边[mid, right]有序
                if(target<nums[right]) // target在右边范围内
                    left=mid+1;
                else
                    right = mid -1;
            }
        }
    }
    // left==right+1
    return -1;
}

// 4. 寻找两个正序数组的中位数
// 思路见array.cpp，其中一种方法是二分法；

// 34. 在排序数组中查找元素的第一个和最后一个位置, O(log n)
// 击败93%, 40%
vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    if(right==0) {
        return {-1,-1};
    }
    // 特殊情况，加快速度；已验证没有下面这一段也是可以AC的；
    if(target<nums[0] || target>nums.back())
        return {-1,-1};

    int leftAns = -1;
    int rightAns = -1;
    // 找第一个大于等于target的位置；
    // [left, right)
    while(left<right) {
        int mid = (left+right)/2;
        if(nums[mid]>target) { // target在左边[left, mid)
            right= mid;
        }
        else if(nums[mid]<target) { // target在右边[mid+1, right)
            left= mid+1;
        }
        else { // target in [left, mid] = [left, mid+1)
            if(right == mid+1) { // 说明right不变，会死循环；只有两种情况：left==mid==right-1, left+1 == mid == right-1;
                if(nums[left]==target) { // left就是所求；
                    right = left;
                }
                else {
                    left++; // left不是所求；
                }
            }
            else {
                right = mid+1;
            }
        }
    }
    assert(left==right);
    if(left < nums.size() && nums[left]==target) // 存在target
        leftAns=left;

    left = 0;
    right = nums.size();
    // 找最后一个大于等于target的位置；
    // [left, right)
    while(left<right) {
        int mid = (left+right)/2;
        if(nums[mid]>target) { // target在左边[left, mid)
            right= mid;
        }
        else if(nums[mid]<target) { // target在右边[mid+1, right)
            left= mid+1;
        }
        else { // target in [mid, right)
            if(left == mid) { // 说明left不变，会死循环；只有一种情况：left==mid==right-1
                // left就是所求；
                right=left;
            }
            else {
                left=mid;
            }
        }
    }

    assert(left==right);
    if(left<nums.size() && nums[left]==target) // 存在target
        rightAns=left;
    return {leftAns, rightAns};
}
// 0ms 标答
vector<int> searchRange2(vector<int>& nums, int target) {
    // [left, right]若使用left<right做为while条件，则需要额外判断最后时left位置(left==right);
    // 上面我的实现中可能死循环的位置刚好是最后一轮循环(做了额外判断)，这里的做法刚好可以避免这种情况；
    vector<int> res(2,-1);
    if(nums.empty()) return res;
    int n=nums.size(),l=0,r=n-1;
    while(l<r){ // ? [l, r]为什么可以用l<r? 应该是因为外面额外对nums[l]判断了；
        int m=l+(r-l)/2;
        if(nums[m]>=target) r=m; // ! r=m一定会移动(l<=m<r)，不会死循环；如果while条件是(l<=r)就会死循环；
        else l=m+1;
    }
    if(nums[l]!=target) return res; // 没找到这里就可以直接返回了；
    res[0]=l;
    r=n;
    while(l<r){
        int m=l+(r-l)/2;
        if(nums[m]<=target) l=m+1;
        else r=m;
    }
    res[1]=l-1;
    return res;
}

int main() {
    cout<<"爱吃香蕉的珂珂"<<endl;
    vector<int> piles{3,6,7,11};
    cout<<minEatingSpeed(piles, 8)<<endl;
    
    piles.assign({30,11,23,4,20});
    cout<<minEatingSpeed(piles, 5)<<endl;
    
    piles.assign({30,11,23,4,20});
    cout<<minEatingSpeed(piles, 6)<<endl;

    cout<<"旋转数组的最小数字"<<endl;
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

    cout<<"搜索旋转排序数组"<<endl;
    numbers.assign({4,5,6,7,0,1,2});
    cout<<searchRotateArray(numbers, 0)<<endl;

    numbers.assign({4,5,6,7,0,1,2});
    cout<<searchRotateArray(numbers, 3)<<endl;

    numbers.assign({1});
    cout<<searchRotateArray(numbers, 0)<<endl;

    numbers.assign({3,1});
    cout<<searchRotateArray(numbers, 1)<<endl;

    cout<<"在排序数组中查找元素的第一个和最后一个位置"<<endl;
    numbers.assign({5,7,7,8,8,10});
    vector<int> ans = searchRange(numbers, 8);
    cout<<"["<<ans[0]<<" "<<ans[1]<<"]"<<endl;

    numbers.assign({5,7,7,8,8,10});
    ans = searchRange(numbers, 6);
    cout<<"["<<ans[0]<<" "<<ans[1]<<"]"<<endl;
    
    numbers.assign({5,7,7,7,8,8,10});
    ans = searchRange(numbers, 7);
    cout<<"["<<ans[0]<<" "<<ans[1]<<"]"<<endl;

    numbers.assign({5,7,7,7,8,8,10});
    ans = searchRange(numbers, 0);
    cout<<"["<<ans[0]<<" "<<ans[1]<<"]"<<endl;

    numbers.assign({5,7,7,7,8,8,10});
    ans = searchRange(numbers, 11);
    cout<<"["<<ans[0]<<" "<<ans[1]<<"]"<<endl;

    return 0;
}