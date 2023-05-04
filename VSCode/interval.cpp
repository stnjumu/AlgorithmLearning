#include"DataStructure/array.h"
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

/* 区间
区间相关操作，例如：区间更新与查询，区间查询最值、和等；
* 线段树
区间更新与查询；动态；
构造时间O(nlogn), 查询时间O(logn)； 空间O(n), 保守估计最小4n，与要维护的区间内容有关；
* ST表，Sparse Table, 稀疏表
静态区间最值查询(RMQ)：Range Minimum/Maximum Query
ST表构造时间O(nlogn), RMQ的时间复杂度O(1), 不支持修改(静态结构)；空间复杂度O(nlog n)
    https://blog.csdn.net/qq_43332980/article/details/107411295
* 树状数组，Binary Index Tree, BIT, 二进制下标树
! 以下实现下标必须从1开始，即BIT[0]空闲；要想从0开始则是另一套写法，lowbit函数需要换，因为lowbit(0)=0；
    https://zhuanlan.zhihu.com/p/93795692， 那张图一定要记住
支持O(logn)时间的单点修改和区间查询；不支持插入删除；
维护区间A(i-lowbit(i), i]共lowbit(i)个；树结构是此区间所有元素Aj都是元素Ai的孩子；j in range (i-lowbit(i), i)
    注意：i为区间A(i-lowbit(i), i]的右端点，一般使用BIT_i来存这个区间的和；普通数组前i项和修改是O(n)复杂度，BIT通过树状结构可以降到O(logn)
    注意：i-lowbit(i)刚好是上一个区间的右端点，所以while(i!=0) sum+=BIT_i; 即得到前i项和；根据lowbit的定义，可知每次迭代都会去掉i的二进制表示中的最低一位1，可知最多减O(log n)次
    其中关键定义lowbit(i)表示i二进制表示中最低位的1及其后面所有0表示的树，例如6=110(B), lowbit(6)=10(B)=2
    可使用位运算快速获得：lowbit(x) = x & (-x)
    孩子下标C获得父亲P的下标的快速方法：P = C + lowbit(C)，类似于进位；
单点修改updata(i, val)：O(log n)
    目的：将Ai改为Ai+val; 也可支持Ai改为val，只需要类似于求一下差值即可；
    从i开始向上爬树，直到树顶，更新遇到的所有节点维护的区间和BIT_i+=val即可; 共log n 个节点；
区间查询query(a, b): O(log n)
    目的：查询A[a,b]的所有元素和；
    由内部方法query(i)间接实现，O(logn)时间内查询前i项和；
    query(i): 求前i项和；while(i!=0) sum+=BIT_i; 分析见上；
    if(a>0) query(b)-query(a-1)即为所求；a==0则query(b)即为所求；
构造：O(nlog n), 空间O(n)
    初始化BIT为和A等长的全0数组，然后将每个值都update进去即可；O(nlog n)
其他应用：
    求逆序对；https://zhuanlan.zhihu.com/p/93795692
    1409. 查询带键的排列；此题非常巧妙，转换成树状数组都很难；
*/

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