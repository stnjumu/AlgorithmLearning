#include"DataStructure/Array.h"
#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<string>
#include<numeric>
#include<unordered_set>
#include<unordered_map>
#include<cmath>
// abs() in cmath.
using namespace std;


// 42. 接雨水

// 思路3：单调栈

// TODO: 思路2：动态规划
// 每个位置填充水后的高度由其左边最高柱子和其右边最高柱子共同决定，当然它本身的高度也会影响是否需要填充；

// 思路1：我的实现；(已实现)
// 双向填充，先从左到右，对每个位置，找到之后第一个不小于它的柱子，填充上雨水；
// 上述过程不能涵盖左比右高，但中间低的情况，所有从右往左再来一遍即可；
// 最坏情况O(n^2)，空间O(1)
int trap1(vector<int> &height) {
    int ans = 0;
    int i = 0;
    while(i<height.size())
    {
        int left_height = height[i], right = i+1;
        while (right<height.size())
        {
            if(height[right]>=left_height)
                break;
            right++;
        }
        if(right<height.size()) { // 找到它之后第一个不小于它的柱子
            for(int j = i+1;j<right;j++) { // 计算中间的雨水
                ans += left_height - height[j];
                height[j] = left_height; // 计算过的位置可以填充上；
            }
            i=right; // 中间可跳过；
        }
        else
            i++;
    }
    // 反方向再来一遍；
    assert(i==height.size());
    i=height.size()-1;
    while(i>=0) {
        int right_height = height[i], left = i-1;
        while (left>=0)
        {
            if(height[left]>=right_height)
                break;
            left--;
        }
        if(left>=0) {
            for(int j = i-1;j>left;j--) {
                ans += right_height - height[j];
                height[j] = right_height;
            }
            i=left;
        }
        else
            i--;
    }
    return ans;
}

// 54. 螺旋矩阵
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    // 虽然写的不好看，但速度最快(击败100%)
    if(matrix.size() == 0 || matrix[0].size()==0)
        return {};
    int m=matrix.size(), n = matrix[0].size();
    int x=0,y=0;
    int x_min, y_min;
    int x_max, y_max;
    vector<int> ans;
    int layer = 0;
    int layerMax = min((m+1)/2,(n+1)/2);
    while(layer<layerMax) {
        x=y=x_min = y_min = layer;
        x_max = m-layer;
        y_max = n-layer;
        // right
        while(y<y_max) {
            ans.push_back(matrix[x][y]);
            y++;
        }
        // 调整
        x_min++; // 反方向遍历时会用到；第一行输出过了，x_min++使其无法再输出；
        // ! 就y_min会在变化后使用；
        y--; // 从[x_max-1][y_min]向下，注意[x_max-1][y_min]刚刚输出过，所以x++;
        x++;
        // down
        while(x<x_max) {
            ans.push_back(matrix[x][y]);
            x++;
        }
        y_max--; // 反方向遍历时会用到；
        y--;
        x--;
        // left
        while(y>=y_min && x>=x_min) {
            ans.push_back(matrix[x][y]);
            y--;
        }
        x_max--; // 可省略；因为每次循环开始会正确设置；
        y++;
        x--;
        // up
        while(x>=x_min && y<y_max) {
            ans.push_back(matrix[x][y]);
            x--;
        }
        y_min++; // 可省略；因为每次循环开始会正确设置；

        layer++;
    }
    return ans;
}
// copied from 参考答案；
vector<int> spiralOrder2(vector<vector<int>>& matrix) {

        if (matrix.empty()) return {};
        vector<int> res;
        int l = 0;
        int r = matrix[0].size() - 1;
        int t = 0;
        int b = matrix.size() - 1;

        while(true)
        {
            for (int i = l; i <= r; i++)    res.push_back(matrix[t][i]);
            if (++t > b)  break;
                
            for (int i = t; i <= b; i++)    res.push_back(matrix[i][r]);
            if (--r < l)    break;

            for (int i = r; i >= l; i--)    res.push_back(matrix[b][i]);
            if (--b < t)    break;

            for (int i = b; i >= t; i--)    res.push_back(matrix[i][l]);
            if (++l > r)    break;
        }

        return res;

}
// 自己写，使用方向数组direction4，并使用next_x, next_y
vector<int> spiralOrder3(vector<vector<int>>& matrix) {
    // m>=1, n>=1;
    int m=matrix.size();
    int n=matrix[0].size();
    vector<int> ans;

    // 右下左上
    int arrayDirection4[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    
    vector<int> start;
    vector<vector<int>> end;
    int layer = 0;
    int layerMax = min((m+1)/2,(n+1)/2);
    while(layer<layerMax) {
        start.assign({layer, layer});
        end.assign({{layer,n-1-layer}, {m-1-layer, n-1-layer}, {m-1-layer, layer}, {layer,layer}});
        // 特殊情况，这一圈只有一行或一列元素，不能先输出再走再判断;
        // ! 说明我的方法还不够优雅，推荐面试时写最简单的方法；使用direction4, 且使用next_x, next_y， 并且使用flag;
        if(layer == m-1-layer) {
            // 只有一行；
            while(start[1]<=n-1-layer) {
                ans.push_back(matrix[start[0]][start[1]]);
                ++start[1];
            }
            break; // 最后一圈；
        }
        if(layer == n-1-layer) {
            // 只有一列；
            while(start[0]<=m-1-layer) {
                ans.push_back(matrix[start[0]][start[1]]);
                ++start[0];
            }
            break; // 最后一圈；
        }

        for(int dir =0; dir<4; ++dir) {
            while(true) {
                // 先输出，再走, 走了再判断；
                ans.push_back(matrix[start[0]][start[1]]);

                start[0] = start[0] + arrayDirection4[dir][0];
                start[1] = start[1] + arrayDirection4[dir][1];
                // 以第一圈为例：路程为
                // dir = 0: [(0,0), (0, n-1)) 左开右闭区间, 即end位置不输出；
                // dir = 1: [(0,n-1), (n-1, n-1)) 
                // dir = 2: [(n-1,n-1), (n-1, 0)) 
                // dir = 3: [(n-1,0), (0, 0)) 
                if(start[0] == end[dir][0] && start[1] == end[dir][1]) break;
            }
        }
        ++layer; // ! don't forget;
    }
    return ans;
}
// TODO: 推荐面试时写最简单的方法；使用direction4, 且使用next_x, next_y， 并且使用flag;

// 剑指 Offer 60. n个骰子的点数
// dp[n, i]表示n个骰子的第i个点数的概率；
// dp[1, i] = 1/6
// dp[n, i] = sum_j(dp[n-1, i-j] * dp[1, j]) j in [1, 6] and dp[n-1, i-j]有意义； 
vector<double> dicesProbability(int n) {
    vector<double> dp_old;
    vector<double> dp0;
    dp0.assign(6,1.0/6.0);
    if(n == 1) {
        return dp0;
    }

    int i=2;
    dp_old.assign(dp0.begin(), dp0.end());
    while(i<=n) {
        vector<double> dp_new;
        int new_max = i * 6, new_min = i * 1;
        int old_max = new_max-6, old_min = new_min-1;
        for(int j = new_min; j<=new_max; j++) {
            // 求dp[i, j]
            double p=0.;
            for(int k= 1; k<=6; k++) {
                if(j-k>=old_min && j-k<=old_max)
                {
                    p+= dp_old[j-k-old_min] * dp0[k-1]; // dp0的min=1, max=6
                }
            }
            dp_new.push_back(p);
        }
        assert(dp_new.size()==new_max-new_min+1);
        dp_old.assign(dp_new.begin(), dp_new.end());
        i++;
    }
    return dp_old;
}
vector<double> dicesProbability2(int n) {
    vector<double> dp_old;
    dp_old.assign(6,1.0/6.0);
    if(n == 1) {
        return dp_old;
    }

    int i=2;
    while(i<=n) {
        vector<double> dp_new;
        int new_max = i * 6, new_min = i * 1;
        int old_max = new_max-6, old_min = new_min-1;
        for(int j = new_min; j<=new_max; j++) {
            // 求dp[i, j]
            double p=0.;
            for(int k= 1; k<=6; k++) {
                if(j-k>=old_min && j-k<=old_max)
                {
                    p+= dp_old[j-k-old_min] * (1.0/6.0); // dp0的min=1, max=6
                }
            }
            dp_new.push_back(p);
        }
        // assert(dp_new.size()==new_max-new_min+1);
        dp_old.assign(dp_new.begin(), dp_new.end());
        i++;
    }
    return dp_old;
}

// 121. 买卖股票的最佳时机
// 历史最低
int maxProfit(vector<int>& prices) {
    if(prices.size()<=1)
        return 0;
    int history_min = prices[0];
    int max = 0;
    for(int i = 1; i<prices.size(); i++) {
        int profit = prices[i]-history_min;
        if(profit>max) {
            max = profit;
        }
        if(prices[i]<history_min) {
            history_min=prices[i];
        }
    }
    return max;
}
// 122. 买卖股票的最佳时机 II
// 可以买卖多次，最多同时持有一股股票；注意：同一天买了又卖或者卖了又买不会获得更高的收益；
// 思路1：带状态的dp问题；
// dp[n, 0], n从0开始，表示在第n+1天不持有股票时，前n+1天的最大利润；
// dp[n, 1]，n从0开始，表示在第n+1天持有股票，前n+1天的最大利润；
// dp[0, 0] = 0, dp[0, 1] = -prices[0];
/*  dp[n, 0] = max_j(dp[j, 0], dp[j,1]+prices), j<i, // 由于dp[i, 0]和dp[i, 1]随i递增，只需看前一天即可；
             = max(dp[n-1, 1] + prices[n],  // 前一天持有股票，今天卖了；
                 dp[n-1, 0]) // 前一天不持有股票，今天不买；
    dp[n, 1] = max(dp[n-1, 0] - prices[n],  // 前一天没有持有，今天买
                 dp[n-1, 1]) // 前一天持有，今天不变
    dp[n, 1]是强制在这一天持有最好的股票，为了之后有一天能卖出赚一笔；
*/ 
// ans = dp[n, 0]
int maxProfit2(vector<int>& prices) {
    // 优化了dp空间
    if(prices.size()<=1) {
        return 0;
    }
    int dp0=0, dp1=-prices[0];

    int i = 1;
    while(i<prices.size()) {
        dp0 = max(dp1+prices[i], dp0);
        dp1 = max(dp0-prices[i], dp1);
        i++;
    }
    return dp0;
}
// TODO: 思路2：贪心法
// 利用第一天买，第二天卖又第二天卖，再第三天卖等价于第一天卖再第三天卖这种性质；
// 可以将任何一种买卖股票的决策：第i天买第j天卖(i卖j卖)，等价地用i买i+1卖、i+1买i+2卖、... 、j-1买j卖的相邻prices元素差分形式
// 可以证明，只需选择所有相邻差分大于0的差分项，即可保证得到最优解；

// 123. 买卖股票的最佳时机 III
// 最多买卖2次；最多同时持有一股股票；
// 不能再用贪心法，只能用dp，拓展更多状态即可；
// dp[i, 0]表示未持有; dp[i, 1]表示第一次持有，dp[i, 2]第一次卖出，dp[i, 3]第二次持有，dp[i,4]第二次卖出;
// 递推过程中保持dp[i, j]随i的递增性，可只考虑前一天的最优解；(最优子结构性质)
// dp[i, 0] = 0, 不需记录
// dp[i, 1] = max(dp[i-1, 1], -prices[i]), 第一次持有的最大收益；
// dp[i, 2] = max(dp[i-1, 2], dp[i-1,1]+prices[2])
// dp[i, 3] = max(dp[i-1, 3], dp[i-1,2]-prices[3])
// dp[i, 4] = max(dp[i-1, 4], dp[i-1,3]+prices[4])
// 初始值: dp[i, 1] = -prices[i], dp[i, 2] = 0, dp[i, 3] = -prices, dp[i, 4]=0;
// 最后ret max(dp[n-1, 2], dp[n-1, 4])
int maxProfit3(vector<int>& prices) {
    if(prices.size()<=1)
        return 0;
    int dp1=-prices[0], dp2 = 0, dp3=-prices[0], dp4=0;
    for(int i=1;i<prices.size();i++) {
        // 不是上个问题中的循环依赖，而是顺序依赖了；
        dp4=max(dp4, dp3+prices[i]);
        dp3=max(dp3, dp2-prices[i]);
        dp2=max(dp2, dp1+prices[i]);
        dp1=max(dp1, -prices[i]);
    }
    return max(dp4, dp2);
}

// 188. 买卖股票的最佳时机 IV
// 上题的2次改成k次, 只需找规律即可；
int maxProfit4(int k, vector<int>& prices) {
    if(prices.size()<=1)
        return 0;
    vector<int> dp;
    for(int i=0;i<k;i++) {
        dp.push_back(-prices[0]); // 第i次持有
        dp.push_back(0); // 第i次卖出
    }
    for(int i=1;i<prices.size();i++) {
        for(int j=dp.size()-1;j>=0;j--) {
            if(j%2==1)
                dp[j] = max(dp[j], dp[j-1]+prices[i]);
            else {
                if(j==0)
                    dp[j] = max(dp[j], -prices[i]);
                else
                    dp[j] = max(dp[j], dp[j-1]-prices[i]);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// 309. 最佳买卖股票时机含冷冻期
// 不限制最大交易次数，但每次卖出的第二天无法买入；
// 带状态的dp问题
// dp[i, 0]表示不持有股票，买卖到prices[i]这一项的最大利润
// dp[i, 1]表示持有股票
// dp[i, 2]表示冷冻期，无法购买；
// dp[i, 0] = max(dp[i-1, 0], dp[i-2, 0], ..., dp[0, 0], dp[i-1, 2]) 
//            max(dp[i-1, 0], dp[i-1, 2]) // 单调性 
// dp[i, 1] = max(dp[i-1, 1], dp[i-2, 1], ..., dp[0, 1], dp[i-1, 0]-prices[i])
//          = max(dp[i-1, 1], dp[i-1, 0]-prices[i]) // 单调性
// dp[i, 2] = dp[i-1, 1]+prices[i] // 只有由dp[i-1,1]才能到达此状态；
// dp[i, 2]不需记录，最后只需比较下dp[n-1, 2]和dp[n-1, 0]即可；
int maxProfit5(vector<int>& prices) {
    if(prices.size()<=1) {
        return 0;
    }
    int dp0=0, dp1=-prices[0], dp2=0;

    int i = 1;
    while(i<prices.size()) {
        int dp2_last = dp2;
        dp2 = dp1+prices[i]; // dp2依赖上一个dp1
        dp1 = max(dp0-prices[i], dp1); // dp1依赖上一个dp0
        dp0 = max(dp2_last, dp0); // dp0依赖上一个dp2, 刚好形成一个环，需要temp记录下上一个dp2
        i++;
    }
    return max(dp0,dp2);
}

// 714. 买卖股票的最佳时机含手续费
// 可以买卖无限次，但每次卖出都需要交手续费；
int maxProfit6(vector<int>& prices, int fee) {
    if(prices.size()<=1) {
        return 0;
    }
    int dp0=0, dp1=-prices[0];

    int i = 1;
    while(i<prices.size()) {
        dp0 = max(dp1+prices[i]-fee, dp0);
        dp1 = max(dp0-prices[i], dp1);
        i++;
    }
    return dp0;
}

// 1863. 找出所有子集的异或总和再求和
// ! 回溯问题，每个元素可以选或不选；O(2^n)
// ? 还可以每层迭代选一个做为start，分析的话很可能得到上界O(n!)，但实际上还是每个元素选/不选，仍然是O(2^n)
void back_trace_XOR(vector<int> &nums, int start, int xor_sum, int &ans) {
    if(start >= nums.size()) {
        ans += xor_sum;
        return;
    }
    // 选
    back_trace_XOR(nums, start+1, xor_sum ^ nums[start], ans); // 用int xor_sum的话回溯时不需要再异或一次
    // 不选
    back_trace_XOR(nums, start+1, xor_sum, ans);
}
int subsetXORSum(vector<int> &nums) {
    if(nums.size()==0)
        return 0;
    int ans=0;
    back_trace_XOR(nums, 0, 0, ans);
    return ans;
}

bool make(vector<int> &materials, vector<int> cookbook) {
    assert(materials.size()==cookbook.size());
    // 可以做就做；并return true; 否则return false;
    bool greaterE = true; // ! 比较得自己写，不能用materials >= cookbook, 这个只比较字典序，不是每个元素都比较，只需前面有一个>=就返回true了；
    // 反例见此题的样例3；
    for(int i=0;i<materials.size();i++) {
        if(materials[i]<cookbook[i]) {
            greaterE=false;
            break;
        }
    }
    if(greaterE) {
        for(int i=0;i<materials.size();i++) {
            materials[i]-=cookbook[i];
        }
        return true;
    }
    return false;
}
void takeApart(vector<int> &materials, vector<int> cookbook) {
    assert(materials.size()==cookbook.size());
    for(int i=0;i<materials.size();i++) {
        materials[i]+=cookbook[i];
    }
}
void back_trace_make(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit, int start, int beauty, int &ans) {
    // start: 当前需要判断是否要制作的菜，ans即结果；
    if(start>=cookbooks.size()) {
        if(limit<=0) {
            ans = max(ans,beauty);
        }
        return;
    }
    // 做cook start
    if(make(materials, cookbooks[start])) {
        back_trace_make(materials, cookbooks, attribute, limit-attribute[start][1], start+1, beauty+attribute[start][0], ans);
        takeApart(materials, cookbooks[start]);
    }
    // 不做cook start
    back_trace_make(materials, cookbooks, attribute, limit, start+1, beauty, ans);
}
// LCP 51. 烹饪料理
// 由于每种料理只能制作一次，所以就是简单的二叉树遍历空间O(2^n)
int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {
    int ans=-1;
    back_trace_make(materials, cookbooks, attribute, limit, 0, 0, ans);
    return ans;
}

// 51. N皇后
bool canPlace(vector<int> place, int start, int j) {
    for(int i=0;i<start;i++) {
        assert(place[i]!=-1);
        if(place[i]==j || abs(j-place[i]) == abs(start-i))
            return false;
    }
    return true;
}
void back_trace_NQueens(int n, int start, vector<int> &place, vector<vector<string>> &ans) {
    if(start>=n) {
        // new_ans的可变成全局变量；加快速度；
        vector<string> new_ans;
        string row;
        row.assign(n,'.');
        new_ans.assign(n, row);
        for(int i=0;i<n;i++) {
            new_ans[i][place[i]]='Q';
        }
        ans.push_back(new_ans);
    }
    
    for(int j=0;j<n;j++) {
        if(canPlace(place, start, j)) {
            place[start]=j;
            back_trace_NQueens(n, start+1, place, ans);
            // 回溯
            place[start]=-1;
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    vector<int> place; // place[i] = j表示第i行皇后放在第j个位置；
    place.assign(n,-1);
    vector<vector<string>> ans;

    back_trace_NQueens(n, 0, place, ans);
    return ans;
}

// 52. N皇后 II
void back_trace_NQueens_II(int n, int start, vector<int> &place, int &ans) {
    if(start>=n) {
        ans+=1;
    }

    for(int j=0;j<n;j++) {
        if(canPlace(place, start, j)) {
            place[start]=j;
            back_trace_NQueens_II(n, start+1, place, ans);
            // 回溯
            place[start]=-1;
        }
    }
}
int totalNQueens(int n) {
    int ans=0;
    vector<int> place;
    place.assign(n,-1);
    back_trace_NQueens_II(n,0,place,ans);
    return ans;
}

// 4. 寻找两个正序数组的中位数
// 要求O(log(m+n)), 则必须用二分法了；
// 思路1：转换成求第k=(m+n)/2小的数，每次比较两个数组第k/2个数，可以确定其中k/2个数一定不是中位数
//      然后去掉这些数，就转换成找第k/2小的数；每次去掉一半，O(log(m+n))
//      第i小，i>=0, 第0小表示最小的。
// TODO: https://leetcode.cn/problems/median-of-two-sorted-arrays/
// 思路2：分块法，取left = 数组1前i项，数组2前j项，保证i+j=(m+n)/2，其他数为right; 
// 保证len(left)<=len(right)且相差最多是1，从左到右探索刚好max(left)<min(right)的情况，即找到了解。
// 但这个思路是O(min(m, n)), 要想log，需要二分，但由于此题非常特殊，存在两端不可行，但中间可行的情况，所求又是从左向右第一个可行的解。
// ? 所以需要进一步转换，最终看题解，可转换成寻找第一个i, 使nums[i-1]<nums[j], 需要进一步思考；
// O(log(min(m, n)))
double findKMin(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int k) {
    int m=nums1.size(), n = nums2.size();
    // k和k/2从0开始，所以每次去掉k/2+1个数
    if(start1>=m) {
        return nums2[start2+k];
    }
    if(start2>=n) {
        return nums1[start1+k];
    }
    if(k==0) {
        return min(nums1[start1], nums2[start2]);
    }

    int half_k_index1 = min((k-1)/2 + start1, m-1);
    int half_k_index2 = min((k-1)/2 + start2, n-1);
    int num1=nums1[half_k_index1], num2 = nums2[half_k_index2];

    if(num1>num2) {
        int new_k = k-(half_k_index2-start2+1);
        return findKMin(nums1, nums2, start1, half_k_index2+1, new_k);
    }
    else if(num1<num2){
        int new_k = k-(half_k_index1-start1+1);
        return findKMin(nums1, nums2, half_k_index1+1, start2, new_k);
    }
    else {
        if(k%2==0) { // 两个都不是，可以去掉比较的两个数和之前所有数，不是去掉k个数因为有可能(k-1)/2有可能超界
            int new_k = k-(half_k_index1-start1+1)-(half_k_index2-start2+1);
            return findKMin(nums1, nums2, half_k_index1+1, half_k_index2+1, new_k);
        }
        // 超界情况
        if((k-1)/2+start1 >=m || (k-1)/2+start2>=n) {
            // 两个都不是
            int new_k = k-(half_k_index1-start1+1)-(half_k_index2-start2+1);
            return findKMin(nums1, nums2, half_k_index1+1, half_k_index2+1, new_k);
        }
        return num1;
    }
}
// 击败89%, 30%
double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
    int m=nums1.size(), n = nums2.size();
    if(m>n) {
        return findMedianSortedArrays1(nums2,nums1);
    }
    // m<=n;
    if(m==0) {
        int mid2= n/2; // n=2, mid2=1; n=
        if(n%2==1) {
            return nums2[mid2]; // 3/2 = 1 正中间
        }
        else {
            return (nums2[mid2]+nums2[mid2-1])/2.0; // 4/2 = 2, 中位数= (a[1]+a[2])/2
        }
    }
    
    // TODO
    int k = (m+n-1)/2;

    if((m+n)%2 == 1)
        return findKMin(nums1, nums2, 0, 0, k);
    else {
        int num1 = findKMin(nums1, nums2, 0, 0, k);
        int num2 = findKMin(nums1, nums2, 0, 0, k+1);
        return (num1+num2)/2.0;
    }
}

int myMin(vector<int>& nums1, vector<int>& nums2, int i, int j) {
    int m = nums1.size(), n = nums2.size();
    if(i>=m) {
        assert(j<n);
        return nums2[j];
    }
    if(j>=n) {
        assert(i<m);
        return nums1[i];
    }

    return min(nums1[i], nums2[j]);
}
int myMax(vector<int>& nums1, vector<int>& nums2, int i, int j) {
    // 由于调用时i=mid-1, 所以可能i,j<0;
    int m = nums1.size(), n = nums2.size();
    if(i<0 || i>=m) {
        assert(j>=0 && j<n);
        return nums2[j];
    }
    if(j<0 || j>=n) {
        assert(i>=0 && i<m);
        return nums1[i];
    }

    return max(nums1[i], nums2[j]);
}
// TODO: 未AC, 二分法有问题；存在两端不可行，但中间可行的情况，之前思路错了；
// ! findMedianSortedArrays2错误，可供警戒
double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    if(m>n) {
        return findMedianSortedArrays2(nums2,nums1);
    }
    // m<=n;
    if(m==0) {
        int mid2= n/2; // n=2, mid2=1; n=
        if(n%2==1) {
            return nums2[mid2]; // 3/2 = 1 正中间
        }
        else {
            return (nums2[mid2]+nums2[mid2-1])/2.0; // 4/2 = 2, 中位数= (a[1]+a[2])/2
        }
    }

    /*// 两个数组连起来有序
    // 本来打算先判断一些朴素情况，实际不需要；
    if(nums1.back()<=nums2[0]) {
        int mid= (m+n)/2; 
        if((m+n)%2==1) {
            if(mid<m)
                return nums1[mid];
            else
                return nums2[mid-m];
            // return mid<m ? nums1[mid] : nums2[mid-m];
        }
        else {
            int ans1, ans2;
            ans1 = mid<m ? nums1[mid] : nums2[mid-m];
            mid--;
            ans2 = mid<m ? nums1[mid] : nums2[mid-m];
            return (ans1+ans2)/2.0;
        }
    }
    if(nums2.back()<=nums1[0]) {
        int mid= (m+n)/2; 
        if((m+n)%2==1) {
            if(mid<n)
                return nums2[mid];
            else
                return nums1[mid-n];
            // return mid<m ? nums1[mid] : nums2[mid-m];
        }
        else {
            int ans1, ans2;
            ans1 = mid<n ? nums2[mid] : nums1[mid-n];
            mid--;
            ans2 = mid<n ? nums2[mid] : nums1[mid-n];
            return (ans1+ans2)/2.0;
        }
    }
    */
    // if(nums1 > nums2)
    //     return findMedianSortedArrays2(nums2,nums1);
    // 二分寻找i，使nums1[0, i)和nums2[0, j) 全小于剩下的值, i + j = (m+n)/2; 
    // 这种情况下，寻找从左到右第一个刚好满足这个情况的位置，刚好是二分法；
    // 先用[left, right) 
    int left = max(0, (m+n)/2-n), right = min(m, (m+n)/2);
    /*// 本来打算先判断一些朴素情况，实际不需要；
    // left=0刚好对应于nums1[0,0)和nums2[0, j)，即全选nums2
    // 但有可能nums2太短，没有足够的元素占据一半。
    int i = left, j = (m+n)/2 - i;
    int tempMax = myMax(nums1,nums2, i-1,j-1);
    int tempMin = myMin(nums1,nums2, i, j);
    if(tempMax <= tempMin)
        return (m+n)%2==1 ? tempMin : (tempMax+tempMin)/2.0;
    
    // right刚好对应全选
    i = right, j = (m+n)/2 - i;
    tempMax = myMax(nums1,nums2, i-1,j-1);
    tempMin = myMin(nums1,nums2, i, j);
    if(tempMax <= tempMin)
        return (m+n)%2==1 ? tempMin : (tempMax+tempMin)/2.0;
    */
    int i,j;
    int tempMax;
    int tempMin;

    while(left<right) {
        // left左边全部不满足，right及right右边全部满足；
        i = (left+right)/2; // mid
        j = (m+n)/2 - i;

        tempMax = myMax(nums1,nums2, i-1,j-1);
        tempMin = myMin(nums1,nums2, i, j);
        if(tempMax <= tempMin) // mid满足
            right = i; // right及right右边全部满足；由于left <= mid < right，所以不会存在死循环的情况；
        else
            left = i+1; // left左边全部不满足
    }
    // left = right, left左边全部不满足，right及right右边全部满足；
    i = right;
    j = (m+n)/2 - i;
    tempMax = myMax(nums1,nums2, i-1,j-1);
    tempMin = myMin(nums1,nums2, i, j);
    assert(tempMax<=tempMin);
    return (m+n)%2==1 ? tempMin : (tempMax+tempMin)/2.0;
}

// 11. 盛最多水的容器
int maxArea(vector<int>& height) {
    // 双指针，贪心，O(n)
    // 关键性质：盛水量和两端高度的最小值有关，再乘距离；
    // 初始化使用两端，则中间的墙想要盛更多水，肯定要使两端height的最小值提高(因为换用中间的墙会使距离变小)
    // 所以可以贪心的更换两端的墙中较小的那个；
    // ? 注意：两端高度相同时怎么办？答案是随便换那个都行；因为中间要想得到更大的水，这两个墙都必须被换；
    int i=0, j=height.size()-1;
    if(j<=0) {
        return 0;
    }

    int leftHeight=height[i], rightHeight=height[j];
    int area = (j-i)*min(leftHeight, rightHeight);
    while(i<j) {
        if(leftHeight<rightHeight) {
            i++;
            if(height[i]>leftHeight) {
                leftHeight=height[i];
            }
        }
        else {
            j--;
            if(height[j]>rightHeight) {
                rightHeight=height[j];
            }
        }
        int newArea = (j-i)*min(leftHeight, rightHeight);
        if(newArea>area) {
            area = newArea;
        }
    }
    return area;
}

// 55. 跳跃游戏
// 击败9%, 7%
bool canJump(vector<int>& nums) {
    int i=0, n=nums.size();
    if(n==1) {
        return true;
    }

    vector<bool> flag(n, false);
    flag[0]=1;
    while(i<n-1) {
        if(flag[i]&&nums[i]>0) {
            if(i+nums[i]>=n-1) // 可以跳到最后一个；
                return true;
            else // 填充可以跳到的位置
                fill(flag.begin()+i+1, flag.begin()+i+nums[i]+1, true); // flag [i+1, i+nums[i]+1) = true; 注意左开右闭
        }
        i++;
    }
    // printVector(flag);
    assert(flag[n-1]==false);
    return flag[n-1];
}
// 优化去掉flag数组，换成能够到达的最远下标max, 维护max即可；击败58%, 35%
bool canJump2(vector<int>& nums) {
    int i=0, n=nums.size();
    if(n==1) {
        return true;
    }

    int max=0;
    while(i<n-1) {
        if(i<=max&&nums[i]>0) {
            if(i+nums[i]>=n-1) // 可以跳到最后一个；
                return true;
            else {
                if(i+nums[i]>max)
                    max = i+nums[i];
            }
        }
        i++;
    }
    return false;
}

// 70. 爬楼梯
// 思路. dp
int climbStairs(int n) {
    // dp[i]=dp[i-1]+dp[i-2], dp[0]=1, dp[1]=1, 求dp[n]
    // TODO: 可选优化，易知这个等价于求斐波那契数列第n项，此方法可以优化dp空间到O(1)；
    // 注意斐波那契数列的复杂度可以降到O(log n), 见OneNote笔记，这部分较复杂，不推荐；
    if(n==1)
        return 1;
    vector<int> dp(n+1,1);
    for(int i=2;i<=n;i++) {
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

// 75. 颜色分类
// 只有3种类别，可用3指针，击败100%, 57%;
// 空间还可优化，利用使用int *指针而不用iterator, 使用前置++而不用后置++(后置++会引入临时变量保存++之前的值)
void sortColors(vector<int>& nums) {
    vector<int>::iterator it,it0,it1,it2;
    it=it0=it1=it2=nums.begin();

    while(it!=nums.end()) {
        if(*it==0) {
            *(it2++)=2; // ! 特别注意指针重合的情况，分析知后面的指针需要先赋值；
            *(it1++)=1;
            *(it0++)=0;
        }
        else if(*it==1) {
            *(it2++)=2;
            *(it1++)=1;
        }
        else {
            *(it2++)=2;
        }

        it++;
    }
}

// ! 128. 最长连续序列
// 暴力法, O(n^2)
// 这里使用了set，每次查找特定元素变成O(1)了，如果不用set, 在nums中查找特定元素是O(n)，则该暴力方法复杂度为O(n^3)
int longestConsecutive1(vector<int>& nums) {
    unordered_set<int> set;
    for(int i=0;i<nums.size();++i) {
        set.insert(nums[i]);
    }

    int ans = 0;
    for(int ai: set) {
        // count left
        int count_left = 1;
        while(set.find(ai-count_left)!=set.end()) {
            count_left++;
        }
        // (ai-count_left, ai]刚好count_left个；

        // count right
        int count_right = 1;
        while(set.find(ai+count_right)!=set.end()) {
            count_right++;
        }
        // [ai, ai+count_right)刚好count_right个；

        if(ans<count_left+count_right-1) {
            ans=count_left+count_right-1;
        }
    }
    return ans;
}
// 优化，单方向count; 
// ! 上面的方法每个元素都在两个方向遍历，例如对1,2,3,4，显然1-4被遍历了4次，实际上只需从最左边开始遍历一次；
// 注意优化后每段连续序列都只会从最左开始遍历一次，所以O(n)，击败51%, 50%
int longestConsecutive2(vector<int>& nums) {
    unordered_set<int> set;
    for(int i=0;i<nums.size();++i) {
        set.insert(nums[i]);
    }

    int ans = 0;
    for(int ai: set) {
        if(set.find(ai-1)==set.end()) {
            // only count right
            int count_right = 1;
            while(set.find(ai+count_right)!=set.end()) {
                count_right++;
            }
            // [ai, ai+count_right)刚好count_right个；

            if(ans<count_right) {
                ans=count_right;
            }
        }
    }
    return ans;
}
// TODO: 并查集, 注意并查集的查找是O(log*n)并不是O(1)，所以最终严格上不算O(n)，但一般应用中，O(log*n)非常小，可认为是常数；

// 152. 乘积最大子数组
// ! 利用前缀积，因为0的存在，所以走不通，千万注意此点，而且前缀积/前缀和的代码比较复杂，甚至不如直接遍历；
// 直接遍历法, O(n^2), 击败5%, 72%
int maxProduct(vector<int>& nums) {
    int ans = INT_MIN;
    int partialProduct;
    for(int i=0;i<nums.size();++i) {
        partialProduct = 1;
        for(int j=i;j<nums.size();++j) {
            partialProduct *= nums[j];
            if(partialProduct>ans)
                ans = partialProduct;
            if(partialProduct==0)
                break;
        }
    }

    return ans;
}
// dp; dp_max[i]表示nums[0, i]的最大正乘积，dp_min[i]表示nums[0,i]的最小负乘积；
// if nums[i]>0, dp_max[i]= max(nums[i], dp_max[i-1]*nums[i]), dp_min[i]= dp_min[i-1]*nums[i]
// if nums[i]<0, dp_min[i]= min(nums[i], dp_max[i-1]*nums[i]), dp_max[i]= dp_min[i-1]*nums[i]
// if nums[i]==0, dp_max[i]= dp_min[i-1] = 0;
// ! 这种dp定义初始值无法确定；如果使用0或1或-1或nums[0]等都不行，见反例{-2};
// 注意到dp[i]只与dp[i-1]有关，所以可优化dp空间；

// * 更正：dp_max[i]表示nums[0, i]的最大乘积，dp_min[i]表示nums[0,i]的最小乘积；
// dp_max[i] = max(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1], nums[i]);
// dp_max[i] = min(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1], nums[i]);
// O(n), 击败62%, 82%
int maxProductDP(vector<int>& nums) {
    int dp_max=nums[0], dp_min=nums[0];
    int ans = nums[0];
    for(int i=1;i<nums.size();++i) {
        int old_max = dp_max; // ! 注意dp_max
        dp_max = max(max(nums[i], dp_max*nums[i]), dp_min*nums[i]);
        dp_min = min(min(nums[i], old_max*nums[i]), dp_min*nums[i]);
        ans = max(ans, dp_max);
    }

    return ans;
}

// ! 300. 最长递增子序列
// 思路1：dp， dp[i]表示nums[0, i]中以nums[i]为结尾的最长递增子序列长度
// dp[i]=max_j(dp[j] + 1, if nums[i]>nums[j]
//             1, others), j<i;
// dp[0]=1;
// O(n^2), O(n)，击败20%, 10%
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    for(int i=1;i<nums.size();++i) {
        for(int j=0;j<i;j++) {
            if(nums[i]>nums[j])
                dp[i]=max(dp[i], dp[j]+1); // 用max函数不如if判断快；
        }
    }
    return *max_element(dp.begin(), dp.end());
}
// ! 思路2：O(nlogn); 遍历nums[0,n), dp[i]表示中所有长度为i的递增子序列的最后一个元素的最小值；
// 引入了一些贪心的思想，想让这个递增子序列的每个位置元素增长的尽可能慢；
// 维护方法，已遍历了nums[0,j-1]，则当前dp中dp[i]存了nums[0,j-1]的所有长度为i的递增子序列的最后一个元素的最小值；
// 遍历nums[j]时，只需要用nums[j]替换dp中第一个大于等于nums[j]的元素即可，如果没有大于等于nums[j]的元素，则插入到尾部；
// 最后dp的长度即为所求；
// 击败99%, 69%
int lengthOfLIS_Onlogn(vector<int>& nums) {
    vector<int> dp;
    dp.push_back(nums[0]);
    for(int i=1;i<nums.size();i++) {
        if(dp.back() < nums[i])
            dp.push_back(nums[i]);
        else {
            // find first pos, dp[pos]>=nums[i]
            auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
            assert(it!=dp.end());
            *it = nums[i];
        }
    }
    return dp.size();
}

int main()
{
    cout<< "接雨水"<<endl;
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};
    cout<< trap1(height)<<endl;

    height.assign({4,2,0,3,2,5});
    cout<< trap1(height)<<endl;

    height.assign({4,2,3});
    cout<< trap1(height)<<endl;

    cout<<"螺旋数组"<<endl;
    vector<vector<int>> matrix{{1,2,3},{4,5,6},{7,8,9}};
    printVector(spiralOrder3(matrix));

    matrix.assign({{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    printVector(spiralOrder3(matrix));

    matrix.assign({{7},{9},{6}});
    printVector(spiralOrder3(matrix));

    cout<< "n个骰子的点数"<<endl;
    printVector(dicesProbability(1));
    printVector(dicesProbability(2));
    printVector(dicesProbability2(2));

    cout<< "买卖股票的最佳时机"<<endl;
    vector<int> prices{7,1,5,3,6,4};
    cout<< maxProfit(prices)<<endl; // 5

    prices.assign({7,6,4,3,1});
    cout<< maxProfit(prices)<<endl; // 0

    cout<< "买卖股票的最佳时机 II"<<endl;
    prices.assign({7,1,5,3,6,4});
    cout<< maxProfit2(prices)<<endl; // 7

    prices.assign({1,2,3,4,5});
    cout<< maxProfit2(prices)<<endl; // 4

    prices.assign({7,6,4,3,1});
    cout<< maxProfit2(prices)<<endl;  // 0

    cout<< "买卖股票的最佳时机 III"<<endl;
    prices.assign({3,3,5,0,0,3,1,4});
    cout<< maxProfit3(prices)<<endl; // 6

    prices.assign({1,2,3,4,5});
    cout<< maxProfit3(prices)<<endl; // 4

    prices.assign({7,6,4,3,1});
    cout<< maxProfit3(prices)<<endl; // 0

    prices.assign({1});
    cout<< maxProfit3(prices)<<endl; // 0

    cout<< "买卖股票的最佳时机 IV"<<endl;
    prices.assign({2,4,1});
    cout<< maxProfit4(2,prices)<<endl; // 2

    prices.assign({3,2,6,5,0,3});
    cout<< maxProfit4(2,prices)<<endl; // 7

    cout<< "最佳买卖股票时机含冷冻期"<<endl;
    prices.assign({1,2,3,0,2});
    cout<< maxProfit5(prices)<<endl; // 3

    prices.assign({1});
    cout<< maxProfit5(prices)<<endl; // 0

    cout<< "买卖股票的最佳时机含手续费"<<endl;
    prices.assign({1, 3, 2, 8, 4, 9});
    cout<< maxProfit6(prices, 2)<<endl; // 8

    prices.assign({1,3,7,5,10,3});
    cout<< maxProfit6(prices,3)<<endl; // 6

    cout<< "找出所有子集的异或总和再求和" << endl;
    vector<int> nums{1,3};
    cout<< subsetXORSum(nums)<<endl;

    nums.assign({5,1,6});
    cout<< subsetXORSum(nums)<<endl;

    nums.assign({3,4,5,6,7,8});
    cout<< subsetXORSum(nums)<<endl;

    cout<< "烹饪料理" <<endl;
    vector<int> materials{10,10,10,10,10};
    vector<vector<int>> cookbooks{{1,1,1,1,1},{3,3,3,3,3},{10,10,10,10,10}};
    vector<vector<int>> attribute{{5,5},{6,6},{10,10}}; 
    cout<< perfectMenu(materials, cookbooks, attribute, 5)<<endl; // 11

    materials.assign({3,2,4,1,2});
    cookbooks.assign({{1,1,0,1,2},{2,1,4,0,0},{3,2,4,1,0}});
    attribute.assign({{3,2},{2,4},{7,6}});
    cout<< perfectMenu(materials, cookbooks, attribute, 1)<<endl; // 7

    materials.assign({17,20,10,13,8});
    cookbooks.assign({{0,13,4,0,0},{17,13,9,2,3},{3,13,12,14,18},{19,13,5,3,6},{14,4,12,3,5}});
    attribute.assign({{13,10},{18,5},{4,8},{4,2},{17,19}});
    cout<< perfectMenu(materials, cookbooks, attribute, 5)<<endl; // 18

    cout<<"N皇后"<<endl;
    printVectorVector(solveNQueens(4)); // 2,4,1,3或者3,1,4,2
    printVectorVector(solveNQueens(1)); // 1种
    cout<< solveNQueens(8).size()<<endl; // 92

    cout<<"N皇后"<<endl;
    cout<< totalNQueens(4) <<endl; // 2
    cout<< totalNQueens(8) <<endl; // 92

    cout<<"寻找两个正序数组的中位数"<<endl;
    vector<int> nums1{1,3};
    vector<int> nums2{2};
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 2

    nums1.assign({1,3});
    nums2.assign({2,4});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 2.5
    nums1.assign({3,4});
    nums2.assign({1,2});
    // nums1.assign({3});
    // nums2.assign({-2,-1});
    //[3,4]
    //[1,2,5]
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 2.5

    nums1.assign({1,2,6,8,10});
    nums2.assign({3,4,6,6,6});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 6

    nums1.assign({});
    nums2.assign({2,3});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 2.5

    nums1.assign({2,2,4,4});
    nums2.assign({2,2,4,4});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 3

    nums1.assign({0,0,0,0,0});
    nums2.assign({-1,0,0,0,0,0,1});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 0

    nums1.assign({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22});
    nums2.assign({0,6});
    cout<<findMedianSortedArrays1(nums1, nums2)<<endl; // 10.5

    cout<<"盛最多水的容器"<<endl;

    height.assign({1,8,6,2,5,4,8,3,7});
    cout<<maxArea(height)<<endl;

    height.assign({1,1});
    cout<<maxArea(height)<<endl;

    cout<<"跳跃游戏"<<endl;
    nums.assign({2,3,1,1,4});
    cout<<canJump(nums)<<endl;

    nums.assign({3,2,1,0,4});
    cout<<canJump(nums)<<endl;

    cout<<"爬楼梯"<<endl;
    cout<<climbStairs(2)<<endl;
    cout<<climbStairs(3)<<endl;

    cout<<"颜色分类"<<endl;
    nums.assign({2,0,2,1,1,0});
    printVector(nums);
    sortColors(nums);
    printVector(nums);

    cout<<"最长连续序列"<<endl;
    nums.assign({100,4,200,1,3,2});
    cout<<longestConsecutive2(nums)<<endl;
    nums.assign({0,3,7,2,5,8,4,6,0,1});
    cout<<longestConsecutive2(nums)<<endl;

    cout<<"乘积最大子数组"<<endl;
    nums.assign({2,3,-2,4});
    cout<< maxProductDP(nums)<<endl;
    nums.assign({-2});
    cout<< maxProductDP(nums)<<endl;
    nums.assign({-4, -3, -2});
    cout<< maxProductDP(nums)<<endl;

    cout<<"最长递增子序列"<<endl;
    nums.assign({10,9,2,5,3,7,101,18});
    cout<<lengthOfLIS_Onlogn(nums)<<endl;

    return 0;
}