#include"DataStructure/Array.h"
#include<iostream>
#include<vector>
#include<stack>
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

// 思路0：暴力
// 每个位置填充水后的高度由其左边最高柱子和其右边最高柱子共同决定，当然它本身的高度也会影响是否需要填充；
// O(n^2), 超时
int trap0(vector<int>& height) {
    // 每个位置求其左边最高和右边最高即可；
    int n = height.size();
    int ans =0;
    for(int i=0;i<n;++i) {
        int maxLeft = 0, maxRight = 0;
        for(int j=0;j<i;++j) {
            if(maxLeft<height[j])
                maxLeft = height[j];
        }
        for(int j=i+1;j<n;++j) {
            if(maxRight<height[j])
                maxRight = height[j];
        }

        int minMaxLeftRight = min(maxLeft, maxRight);
        if(minMaxLeftRight>height[i]) {
            // 能接到雨水
            ans += minMaxLeftRight-height[i];
        }
    }
    return ans;
}


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
// 思路2：dp
// 根据暴力方法可知，求maxLeft和maxRight的过程存在大量重复计算；
// 简单写一写就可以发现，可以O(n)时间内求maxLeft或maxRight
// O(n), O(n), 击败83%, 9%;
// 可选优化，maxLeftArray和maxRightArray可以合并成一个，因为只需要两者中的最小值；
// * 可选优化，将maxLeft定义为i和i左边元素的最大值，maxRight定义为i和i右边元素的最大值；可以更简单一些；
int trap2(vector<int> &height) {
    int n = height.size();
    vector<int> maxLeftArray(n, 0), maxRightArray(n, 0);

    // maxLeft
    int maxLeft = 0;
    for(int i=0;i<n;++i) {
        // 先设置maxLeftArray
        maxLeftArray[i] = maxLeft;

        if(maxLeft < height[i])
            maxLeft = height[i];
    }
    // maxRight
    int maxRight = 0;
    for(int i=n-1;i>=0;--i) {
        // 先设置maxRightArray
        maxRightArray[i] = maxRight;

        if(maxRight < height[i])
            maxRight = height[i];
    }

    int ans =0;
    for(int i=0;i<n;++i) {
        int minMaxLeftRight = min(maxLeftArray[i], maxRightArray[i]);
        if(minMaxLeftRight>height[i])
            ans += minMaxLeftRight - height[i];
    }
    return ans;
}
// 击败83%, 61%
int trap2_better(vector<int> &height) {
    int n = height.size();
    vector<int> minMaxLeftRight(n, 0);

    // maxLeft
    int maxLeft = 0;
    for(int i=0;i<n;++i) {
        // 求i即i左边的最大值；
        maxLeft = max(maxLeft, height[i]);

        minMaxLeftRight[i] = maxLeft;
    }
    // maxRight, minMax, ans
    int maxRight = 0;
    int ans =0;
    for(int i=n-1;i>=0;--i) {
        // 求i即i右边的最大值；
        maxRight = max(maxRight, height[i]);
        
        minMaxLeftRight[i] = min(minMaxLeftRight[i], maxRight);
        ans += minMaxLeftRight[i]-height[i];
    }

    return ans;
}
// 思路3：单调栈； 不懂, O(n),O(n)

// TODO: 思路4：双指针, O(n), O(1)
// * 注意：maxLeft可以定义为i左边所有元素的max(可能接到负的雨水，需要判断)，也可以定义为i即i左边所有元素的max(接到雨水最少为0，不需额外判断)
// 思路4采用后者：maxLeft定义为i即i左边所有元素的max；maxRight类似；
// 注意到：left从0开始，right从n-1开始；并先更新maxLeft, maxRight；
// 刚开始if *left<*right, 有maxLeft==*left < *right==maxRight, 即 maxLeft < maxRight; 
//      此时left的能接的雨水刚好能确定，因为被maxleft限制住了，而右边又有大于maxLeft的maxRight，所以可以确定，当然这只是刚开始，且接的水一定是0；
// if *left>=*right, 有maxLeft==*left >= *right==maxRight, 即 maxLeft >= maxRight; 同理可确定right能接的水(当然一定为0)；
// 我们贪心地选择填充left和right中较小地一个，之后移动填充后的那个，并更新maxLeft, maxRight; 相等则选择right.
// 则对任意时刻，有*left<=maxLeft, *right<=maxRight;
// ! 我们需要证明定理1: 对任意时刻，还有if *left<*right, then maxLeft < maxRight; if *left>=*right, then maxLeft >= maxRight.
// 可以只证明其中一条，另一条同理可证；对于if *left<*right, then maxLeft < maxRight. (我已尝试，直接用数学归纳法证明不了)
// 可以先证个引理，if *left<*right, then *right是当目前为止遇到的最大值，即 *right = max(maxLeft, maxRight); 根据贪心选择策略，引理显然成立。由引理易得*right = maxRight
// 根据引理，则有if *left<*right, then *right = max(maxLeft, maxRight) = maxRight; 有 maxLeft <= maxRight, 根据贪心选择策略中，相等会选right, 则 maxLeft < maxRight.
// 由上，定理1可证;

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
// 优化：观察发现，n个骰子最小点数为n, 最大点数为6n; 且概率的分母都是6^n;
// 定义概率为dp数组，dp[i, j]表示i个骰子的点数为j的概率，j in [n, 6n], dp[n]是所求, dp[1] = [1/6, 1/6, ..., 1/6]
// 拆分概率事件i个骰子点数为j的概率为6个事件的概率之和：1个骰子点数为k, k in [1, 6], 概率都是1/6; i-1个骰子点数为j-k；
// dp[i, j] = ( \sum_k dp[i-1, j-k] )/6, k in [1, 6]
// 需要保证j-k在dp[i, :]中有意义，超界概率为0；
// 所有dp[i, :]数组下标减去i，可以使其下标从0开始；
// 由于概率的分母都是6^n，可以用dp数组统计基本事件的次数(古典概型)；则上面dp递推式中不需要再/6
// 击败100%, 24%, 内存比之前多了一点点；
vector<double> dicesProbability3(int n) {
    vector<int> dp_old(6,1);
    if(n > 1) {
        int i=2;
        while(i<=n) {
            // dp_old = dp[i-1, :], 求dp_new = dp[i, :]
            int new_max = i * 6, new_min = i * 1;
            vector<int> dp_new(new_max-new_min+1, 0);
            int old_max = new_max-6, old_min = new_min-1;
            for(int j = new_min; j<=new_max; j++) {
                // dp[i, j], j in [new_min, new_max]
                for(int k= 1; k<=6; k++) { // k in [1, 6]
                    if(j-k>=old_min && j-k<=old_max) // dp[i-1, j-k]有意义
                    {
                        dp_new[j-new_min]+= dp_old[j-k-old_min]; // 基本事件计数
                    }
                }
            }
            // assert(dp_new.size()==new_max-new_min+1);
            dp_old.swap(dp_new); // O(1)时间交换；
            // dp_old.assign(dp_new.begin(), dp_new.end());
            i++;
        }
    }

    vector<double> ans;
    double div = pow(6.0, n);
    for(int i=0;i<dp_old.size();++i)
        ans.push_back(dp_old[i]/div);
    
    return ans;
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
// 因为有定理：如果能够跳到位置max, 则能跳到所有位置i, i<=max
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

// ! linear select, 线性时间选择；
// 215. 数组中的第K个最大元素；
// 思路1：partition，平均复杂度O(n),空间O(logn)，证明见算法导论9.2, 击败76%, 39%
// 这里借用了STL partition，自己实现见Array.h
// 可选：找第k(从1开始)大元素等价于第n-k(从0开始)小元素或第n-k+1(从1开始)小元素；
int myPartition(vector<int> &nums, int start, int end) {
    // 至少3个数；
    // 以pivot = nums[start]划分, left pivot right;
    // left全部>pivot, right全部<=pivot
    // 返回值为left.size, 即>pivot的个数；
    int pivot = nums[start];
    auto it = partition(nums.begin()+start+1, nums.begin()+end, [=](int x){
        return x>pivot;
    });
    // 前面>pivot; 后面<=pivot
    
    int lessCount = (it-nums.begin())-start-1;
    // swap pivot和it-1的元素；
    swap(nums[start], nums[start+lessCount]);
    return lessCount;
}
int findRangeKthLargest(vector<int> &nums, int start, int end, int k) {
    // 递归出口
    if(end-start<=2) { // 少于等于2个数，则可直接返回
        if(end-start == 1) {
            assert(k==1);
            return nums[start];
        }
        else {
            assert(k==1||k==2);
            if(k==1) {
                return max(nums[start], nums[start+1]);
            }
            else {
                return min(nums[start], nums[start+1]);
            }
        }
    }

    int greaterCount = myPartition(nums, start, end);
    // greater pivot less
    if(k<=greaterCount) {
        // 第k大在[start, start+greaterCount)
        return findRangeKthLargest(nums, start, start+greaterCount, k);
    }
    else if(k==greaterCount+1) {
        // 第k大刚好是pivot
        return nums[start+greaterCount];
    }
    else { // k>greaterCount+1
        // 第k大在[start+greaterCount+1, end)
        return findRangeKthLargest(nums, start+greaterCount+1, end, k-greaterCount-1); // ! 之前忘+1了；
    }
}
int findKthLargest(vector<int>& nums, int k) {
    return findRangeKthLargest(nums, 0, nums.size(), k);
}
// 思路2：大小为k的大根堆，O(nlogk), 空间O(logk)
// 思路3：基于堆排序，建大顶堆O(n), k-1次pop，O(klogn)， 总共O(n+klogn)

// 238. 除自身以外数组的乘积 (不使用除法)
// 思路：前缀积和后缀积相乘即结果
// 优化：由于每个前缀积和后缀积都只会使用一次，所以可优化到空间为O(1);
// 击败98%, 87%
vector<int> productExceptSelf(vector<int>& nums) {
    // 题目保证乘法不会溢出
    int n= nums.size();
    vector<int> ans(n,1);
    // 先给ans乘上前缀积
    int prod = 1;
    for(int i=0;i<n-1;++i) {
        prod *= nums[i];
        ans[i+1]=prod;
    }
    // 再乘后缀积
    prod = 1;
    for(int i=n-1;i>0;--i) {
        prod *= nums[i];
        ans[i-1]*=prod;
    }
    return ans;
}

// 279. 完全平方数
// n能拆分成完全平方数的和形式，求这些拆分中完全平方数的最少个数；
// 思路1：类背包问题的递归解法，击败14%, 5%
// 可选优化，代码可以写的更简洁
int getDPn_backtrace(vector<int> &squares, vector<int> &dp, int n) {
    if(dp[n]!=0) return dp[n];

    int dpn = 10001;
    for(auto square: squares) {
        if(n-square>=1)
            dpn = min(dpn, getDPn_backtrace(squares, dp, n-square));
    }
    dp[n]=dpn+1;
    return dpn+1;
}
int numSquares(int n) {
    // get all Squares <=n
    vector<int> squares;
    const int N = 10001;
    vector<int> dp(N, 0);

    int i=1;
    while(i*i<=n) {
        dp[i*i]=1;
        squares.push_back(i*i);
        i++;
        if(i*i==n) {
            return 1;
        }
    }

    return getDPn_backtrace(squares, dp, n);
}
// 思路2：dp
// O(n*sqrt(n))，因为每个数会遍历所有小于n的完全平方数，sqrt(n)个，击败40%, 10%.
int numSquaresDP(int n) {
    // get all Squares <=n
    // dp[i]表示i需要的平方数个数的最小值；
    // dp[i] = min_j(dp[i-j])+1, j是平方数，且j<i
    vector<int> squares;
    const int N = 10001;
    vector<int> dp(n+1, 0);

    int i=1;
    while(i*i<=n) {
        dp[i*i]=1;
        squares.push_back(i*i);
        i++;
        if(i*i==n) {
            return 1;
        }
    }

    // dp
    for(int i=1;i<=n;++i) {
        if(dp[i]!=1) { // 不是完全平方数；
            int minNum = 10001;
            for(int j=0;j<squares.size();++j) {
                if(squares[j]>i)
                    break;
                minNum = min(minNum, dp[i-squares[j]]);
            }
            dp[i]=minNum+1;
        }
    }
    return dp[n];
}
// 思路3：数学定理，所有正整数都可以表示成不超过4个正整数平方和的形式，详见https://leetcode.cn/problems/perfect-squares/solution/wan-quan-ping-fang-shu-by-leetcode-solut-t99c/

// 283. 移动零
// 原地将数组中0移到数组末尾，保持原来的相对顺序；
// 双指针，击败98%, 5%
// 下面这种方法就是array.h中mypartitionOnO1的双指针法，就是判断条件从小于pivot变成了不是0；
// 由此，可知可选优化：left==right时可不swap; 还可实现双端游走；
void moveZeroes(vector<int>& nums) {
    int left=0, right=0;
    while(right<nums.size()) {
        if(nums[right]!=0) {
            swap(nums[left], nums[right]);
            ++left;
        }

        ++right;
    }
}

// 312. 戳气球
// 贪心法不对，反例1,2,3,4,5, 正确答案：110
// dp, dp[i,j]表示剩下nums[i,j]，这些气球能得到的最大硬币数量；
// dp[i,i]= nums[i];
// dp[i,j]= max_k{ dp[i,k-1]+dp[k+1, j]+nums[i]*(1或nums[]) }
// TODO: 
int maxCoins(vector<int>& nums) {
    // dp
    cout<<"TODO"<<endl;
    return 0;
}

// ! 322. 零钱兑换
// 求最少硬币个数；
// 回溯法
int minCountCoinChange;
vector<int> minCountOfAmounts;
// 思路1：加上简单剪枝的回溯, 时间超限
void backtrace_coinChange1(vector<int> &coins, int amount, int count) {
    if(amount==0) { // ans
        minCountCoinChange = min(minCountCoinChange, count);
        return;
    }
    if(count>=minCountCoinChange) {// 剪枝
        return;
    }
    
    for(int coin: coins) {
        if(amount>=coin) {
            backtrace_coinChange1(coins, amount-coin, count+1);
        }
    }
}
int coinChange1(vector<int>& coins, int amount) {
    minCountCoinChange = 10001;
    sort(coins.begin(), coins.end(), greater<int>());
    backtrace_coinChange1(coins, amount, 0);
    return minCountCoinChange<10001? minCountCoinChange : -1;
}
// 思路2：记忆化搜索, 超时；我只记忆了有解子问题；
int backtrace_coinChange2(vector<int> &coins, int amount) {
    // 返回兑换amount需要最小零钱数或10001，10001表示兑换amount需要的最小零钱数超过了当前解；
    if(amount==0) { // ans
        return 0; // 不需要兑换0
    }
    if(minCountOfAmounts[amount]<10001) { // 记忆
        return minCountOfAmounts[amount];
    }
    
    int minCount=10001;
    bool flag =true;
    for(int coin: coins) {
        if(amount>=coin) {
            minCount = min(minCount, backtrace_coinChange2(coins, amount-coin));
        }
    }
    // 以下都是为了维护记忆；包括返回值；
    minCount+=1; // 加上本函数中的coin; minCount in [1, inf);
    // minCountOfAmounts[amount] in [-1, inf]
    minCountOfAmounts[amount] = min(minCountOfAmounts[amount], minCount);

    return minCountOfAmounts[amount];

}
int coinChange2(vector<int>& coins, int amount) {
    minCountOfAmounts.assign(amount+1, 10001);
    int minCount = backtrace_coinChange2(coins, amount);
    return minCount<10001? minCount: -1;
}
// 思路3：剪枝+记忆化搜索；写出很多bug; 
// 现在bug是因为剪枝思路有问题，不能用当前已使用硬币数>当前解来剪枝，因为有些子问题的求解不能中止，剪枝了会导致子问题求解错误；
// ! 下面的代码还是有bug，请勿使用
int BUGbacktrace_coinChange(vector<int> &coins, int amount, int count) {
    // 返回兑换amount需要最小零钱数或10001，10001表示兑换amount需要的最小零钱数超过了当前解；
    if(amount==0) { // ans
        minCountCoinChange = min(minCountCoinChange, count); // 更新更优解；
        return 0; // 不需要兑换0
    }
    if(minCountOfAmounts[amount]<10001) { // 记忆
        minCountCoinChange = min(minCountCoinChange, count+ minCountOfAmounts[amount]);
        return minCountOfAmounts[amount];
    }
    
    if(count<minCountCoinChange) { // count>=，则可以剪枝
        int minCount=10001;
        bool flag =true;
        for(int coin: coins) {
            if(amount>=coin) {
                int temp = BUGbacktrace_coinChange(coins, amount-coin, count+1);
                if(temp!=-1)
                    minCount = min(minCount, temp);
                else
                    flag = false;
            }
        }
        // 以下都是为了维护记忆；包括返回值；
        minCount+=1; // 加上本函数中的coin; minCount in [1, inf);
        // minCountOfAmounts[amount] in [-1, inf];
        if(flag)
            minCountOfAmounts[amount] = min(minCountOfAmounts[amount], minCount);

        // 下面是minCountOfAmounts初值为-1的维护minCountOfAmounts[amount]的有bug的代码，改正的话非常复杂且容易出错；
        // ! fix bug: minCountOfAmounts[amount]=minCount+1， 会导致改变之前求得的最小值被覆盖；
        // if(minCount<10001) // 有更优解；
        //     minCountOfAmounts[amount]=minCount+1; 
        // else
        //     minCountOfAmounts[amount]=10001; // 没有更优解，用10001代表剪枝；
        
        return minCountOfAmounts[amount];
    }
    else {
        return -1;
    }
}
int BUGcoinChange(vector<int>& coins, int amount) {
    minCountCoinChange = 10001;
    sort(coins.begin(), coins.end(), greater<int>());
    minCountOfAmounts.assign(amount+1, 10001); // ! 改变初值为10001有利于剪枝
    BUGbacktrace_coinChange(coins, amount, 0);
    return minCountCoinChange<10001? minCountCoinChange: -1;
}
// 官方记忆化搜索代码思路：记录所有探索过的子问题，包括有解子问题和无解子问题；
// * 最优思路：一维dp
// 零钱兑换II需要记录组合个数，则需要二维dp, 本题二维dp也能做；
// O(MN), M=amount.size(), n = coins.size(); 击败31%, 59%
int coinChange(vector<int>& coins, int amount) {
    // 子问题的定义最为关键，dp[i]为兑换amount=i需要的最少硬币个数；
    // dp[i]= min_j{ dp[i-coins[j]] } +1, i-coins[j]>0;
    // 显然dp[i]依赖于dp[0]-dp[i-1]之间的一些项
    vector<int> dp(amount+1, 10001);
    dp[0]=0;
    for(int i=1;i<=amount;++i) {
        for(int j=0;j<coins.size();++j) {
            if(i-coins[j]>=0) {
                dp[i]= min(dp[i-coins[j]]+1, dp[i]);
            }
        }
    }
    return dp[amount]<10001? dp[amount] : -1;
}

// 518. 零钱兑换II
// 求兑换组合个数；
// amount=0时空集也算一种，返回1;
// 击败9%, 11%
// 空间可优化到O(amount)
int change(int amount, vector<int>& coins) {
    // 二维dp
    // dp[i,j]表示使用前i(从0开始)种coin能够兑换j的组合数；
    // dp[i,j] = dp[i-1, j]       , 不使用coin[i]
    //          + dp[i, j-coin[i]], 使用coin[i]
    vector<vector<int>> dp(coins.size(), vector<int>(amount+1, 0));
    for(int k=0;k*coins[0]<=amount;++k) {
        dp[0][k*coins[0]]=1; // 很容易理解；
    }
    for(int i=0;i<coins.size();++i) {
        dp[i][0]=1; // 比较难理解
    }

    for(int i=1;i<coins.size();++i) {
        for(int j=1;j<=amount;++j) {
            dp[i][j]=dp[i-1][j]; // 不使用第i种coin
            if(j-coins[i]>=0) {
                // 可以使用第i种coin
                dp[i][j]+= dp[i][j-coins[i]];
            }
        }
    }
    return dp.back().back();
}
// 将上面二维dp的代码优化空间到O(amount)即标答
// 击败30%, 82%
int change2(int amount, vector<int>& coins) {
    // 原二维dp
    // dp[i,j]表示使用前i(从0开始)种coin能够兑换j的组合数；
    // dp[i,j] = dp[i-1, j]       , 不使用coin[i]
    //          + dp[i, j-coin[i]], 使用coin[i]
    // 一行一行遍历，则遍历到dp[i,j]时，如果只有一行存储dp[j]，则dp[j]刚好是dp[i-1,j]，dp[j-coin[i]]刚好是本行更新后的dp[i, j-coin[i]]
    vector<int> dp(amount+1, 0);
    dp[0]=1;

    for(int i=0;i<coins.size();++i) {
        for(int j=1;j<=amount;++j) {
            if(j-coins[i]>=0)
                dp[j]+= dp[j-coins[i]]; // 对比上面代码，可以发现就是把dp[i-1][j]累加到dp[i][j]上了；
        }
    }
    return dp.back();
}
// 由下可知，本题只能二维dp，二维dp可优化空间成一维；
// 一维dp不行；猜测原因是本题求的是组合数，一维dp无法区分先选coin i再选coin j和先选coin j再选coin i，会多次计数；也不是排列数，因为两个相同的coin也会重复计数；
// 二维dp可确保coin i和coin j的先后顺序，所以可以求组合数；

// ! 下面的一维dp是错的， 错在了组合数，相同的coin算了非常多次，感觉比排列数都多了；本身思路就错了；
int changeError(int amount, vector<int>& coins) {
    assert(0); // 错误
    // dp[i]表示j的组合个数；
    // dp[i]= \sum_j (dp[i-coin[j]]), i-coin[j]>=0
    // dp[0]=1;

    vector<int> dp(amount+1, 0);
    dp[0]=1;

    for(int i=1;i<=amount;++i) {
        for(int j=0;j<coins.size();++j) {
            if(i-coins[j]>=0)
                dp[i]+=dp[i-coins[j]];
        }
    }
    return dp.back();
}

// 347. 前K个高频元素
// 大小为k的小顶堆，O(nlogk), 击败49%，16%
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counts;
    for(int num: nums) {
        ++counts[num];
    }
    
    // k个元素的小顶堆
    vector<pair<int,int> > heap;
    auto greater = [](pair<int,int> count1, pair<int,int> count2){
        return count1.second > count2.second;
    };
    for(auto count: counts) {
        heap.push_back(count);
        push_heap(heap.begin(), heap.end(), greater);
        if(heap.size()==k+1) {
            pop_heap(heap.begin(), heap.end(), greater);
            heap.pop_back();
        }
    }
    vector<int> ans;
    for(auto p: heap) {
        ans.push_back(p.first);
    }
    return ans;
}

// 416. 分割等和子集（子序列）
// 回溯, 栈溢出
bool backtrace_canPartition(vector<int> &nums, int start, int target) {
    if(target==0) {
        return true;
    }
    
    if(backtrace_canPartition(nums, start+1, target)) {
        return true;
    }
    if(target>nums[start] && backtrace_canPartition(nums, start+1, target-nums[start])) {
        return true;
    }
    return false;
}
bool canPartition(vector<int>& nums) {
    int target = accumulate(nums.begin(), nums.end(), 0);
    if(target % 2 == 1) {
        return false;
    }

    target/=2;
    // 寻找子序列，和刚好为target;
    return backtrace_canPartition(nums, 0, target);
}
// dp, 0-1背包问题 (此题是NPC问题，无多项式解)
// dp[i,j]表示只用前i个元素是否有子序列的和为j
// dp[i,j] = dp[i-1, j], 不使用nums[i]
//         || dp[i-1, j-nums[i]], 使用nums[i]
// 击败5%, 49%
bool canPartitionDP(vector<int>& nums) {
    // nums.size()>=1
    int target = accumulate(nums.begin(), nums.end(), 0);
    if(target % 2 == 1) return false;
    target/=2;
    // 转换为是否存在子序列和为target=sum/2;
    vector<vector<bool>> dp(nums.size(), vector<bool>(target+1, false));
    dp[0][0]=true;
    if(nums[0]<=target) // ! nums[0]很可能>target, 例如[100];
        dp[0][nums[0]]=true;
    for(int i=1;i<nums.size();++i) {
        for(int j=0;j<=target;++j) {
            dp[i][j]=dp[i-1][j]; // 不使用nums[i]
            if(j>=nums[i]) { // ! 两者必须分开，不能按分析的那样在一个语句中，如下面注释所示；
                dp[i][j] = dp[i][j] || dp[i-1][j-nums[i]];
            }
            // ! BUG ! Don't use.
            // if(j>=nums[i]) {
            //     dp[i][j] = dp[i][j]=dp[i-1][j] || dp[i-1][j-nums[i]];
            // }
        }
    }
    return dp[nums.size()-1][target];
}


// 406. 根据身高重建队列
// my思路1: 观察发现重排的[hi, ki]中，ki=kj时(前面更高的个数相同)，必有hi<hj, if i<j; 否则显然后面的更高的个数会加1；
// ki即hi向前的逆序对个数；只不过相同也算；
// 我的做法：先按ki升序，再按hi升序；按上面顺序插入到ans中，每个元素插入时只需看ans前面有多少个更大的和ki关系，从而确定插入位置；
// 击败65%, 48%;
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    // 按ki升序插入
    sort(people.begin(), people.end(), [](vector<int> &a, vector<int> &b){
        if(a[1]<b[1])
            return true;
        else if(a[1]>b[1])
            return false;
        else {
            return a[0]<b[0];
        }
        // 等价于return a[1]<b[1] || a[1]==b[1] && a[0]<b[0]
    });

    vector<vector<int>> ans;
    for(int i=0;i<people.size();++i) {
        // insert people[i] to ans;
        int hi = people[i][0];
        int ki = people[i][1];

        int greaterBefore = 0;
        int j=0;
        while(j<ans.size()) {
            if(greaterBefore == ki) {
                if(ans[j][0]<hi) {
                    // people[i]插入到ans[j]后面
                }
                else { // hi <= ans[j][0]
                    // people[i]应该插入到ans[j]前面, 否则people[i]比ans[j]低，people[i]再往后会导致greaterBefore++;
                    break;
                }
            }
            else {
                assert(greaterBefore< ki);
                if(hi <= ans[j][0])
                    greaterBefore++;
            }
            j++;
        }
        if(j<ans.size())
            ans.insert(ans.begin()+j, people[i]);
        else
            ans.push_back(people[i]);
    }
    return ans;
}
// 标答：身高从高到低排列；即按hi降序，ki升序排列后依次插入；
// 显然, ki刚好等于其前面元素个数；因为后插入的元素高度小于等于之前插入所有元素，所以直接插入到第ki位即可
// 当然，ki>ans.size()时插入到队尾即可；
vector<vector<int>> reconstructQueueAns(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
        return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
    });
    vector<vector<int>> ans;
    for (const vector<int>& person: people) {
        assert(person[1]<=ans.size());
        // if(person[1]>ans.size()) { // ! 标答没这句话，分析知；不可能出现ki比ans现有元素个数大，因为插入顺序保证了比person大的都提前插入了
        //     ans.push_back(person);
        // }
        // else
        ans.insert(ans.begin() + person[1], person);
    }
    return ans;
}

// 448. 找到所有数组中消失的数字
// 给定n个数的nums数组，所有数均在[1,n]内，找出所有[1,n]中未出现数字；
// 思路1：直接法：O(n), O(n), 击败71%, 38%
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<bool> appear(nums.size(),false);
    for(int num:nums)
        appear[num-1]=true;
    vector<int> ans;
    for(int i=0;i<appear.size();++i) {
        if(!appear[i])
            ans.push_back(i+1);
    }
    return ans;
}
// 思路2：要求时间O(n), 空间O(1)(除返回数组外)；
// 利用nums来存取额外信息；
// 法1：由于nums[i] in [1, n]，所以可以用nums[i]+n表示i出现过
// 法2：由于nums[i]>0, 所以可以用-nums[i]表示i出现过
// 实现法2，击败71%, 79%;
vector<int> findDisappearedNumbersOnO1(vector<int>& nums) {
    // 实现法2
    for(int i=0;i<nums.size();++i) {
        // if(nums[i]<0) { // 之前遇到过i, -nums[i]才是原来的值
        //     nums[-nums[i]-1]=-abs(nums[-nums[i]-1]);
        // }
        // else {
        //     nums[nums[i]-1]=-abs(nums[nums[i]-1]);
        // }
        // if-else两句可合并为一句话，注意上面写法更容易理解；
        nums[abs(nums[i])-1]=-abs(nums[abs(nums[i])-1]);
    }
    vector<int> ans;
    for(int i=0;i<nums.size();++i) {
        if(nums[i]>0)
            ans.push_back(i+1);
    }
    return ans;
}

// 581. 最短无序连续子数组
// 所有子数组中，先找满足条件：对此子数组升序排序后，整个数组升序；求满足条件的所有子数组的最小长度；
// 思路1：暴力，从左到右遍历找左边界，第一个能和后面元素组成逆序对的元素；
// 然后从右到左找有边界即可；
// O(n^2), 击败6%, 46%
int findUnsortedSubarray(vector<int>& nums) {
    int left= 0, right = nums.size()-1;
    while(left<nums.size()) {
        int i=left+1; // ! 错写成i=0
        while(i<nums.size()) {
            if(nums[left]>nums[i]) // 逆序对
                break;
            i++;
        }
        if(i<nums.size()) // find逆序对
            break;
        left++;
    }
    if(left==nums.size()) // 整体有序
        return 0;
    // [0, left) 有序, 且小于等于右边所有元素；
    while(right>left) {
        int j=right-1;
        while(j>=left) { // ! 错写成right>left, j>left; 后者反例[2,1]
            if(nums[right]<nums[j])
                break;
            j--;
        }
        if(j>=left)
            break;
        right--;
    }
    // (right, end)有序，且大于等于左边所有元素
    // [left, right]需要排序
    return right-left+1;
}
// 思路2：使用单调栈求下一个更小元素和上一个更大元素, O(n)
// 则第一个存在下一个更小元素的记为left, 最后一个存在上一个更大元素的即right;
// ! 注意必须求所有元素的下一个更小元素才能确定left, 确定right同理，因为有相等情况存在，反例[1,3,2,2,2]
// 只将单调栈的第一个解弹出是错误的；
// O(n), O(n), 击败53%, 5%
int findUnsortedSubarrayOnOn(vector<int>& nums) {
    // 第一个存在下一个更小元素的记为left
    // 下一个更小即降序，所以应使用递增栈；
    // 从左到右遍历，弹出是解(*top > *i)；
    // 有相同元素，栈中存下标
    int n=nums.size();
    if(n<=1)
        return 0;
    
    stack<int> st;
    vector<int> temp(nums.size(), -1);
    for(int i=0;i<n;++i) {
        while(!st.empty() && nums[st.top()] > nums[i]) {
            // 解*top > *i;
            temp[st.top()]=i;
            st.pop();
        }
        st.push(i);
    }
    if(st.size()==n) // 全部升序
        return 0;
    int left=0;
    while(left<n) {
        if(temp[left]!=-1)
            break;
        left++;
    }
    
    // 上一个更大元素，递减栈；从右到左遍历，弹出是解(*top < *i)
    while(!st.empty()) {
        st.pop();
    }
    temp.clear();

    for(int i=n-1;i>=left;--i) {
        while(!st.empty() && nums[st.top()] < nums[i]) {
            // 解 *top < *i
            temp[st.top()]=i;
            st.pop();
        }
        st.push(i);
    }
    int right = n-1;
    while(right>=0) {
        if(temp[right]!=-1)
            break;
        right--;
    }
    return right-left+1;
}
// TODO: 思路3：标答：O(n), O(1)
// 将nums分成3部分numsA, numsB, numsC, 设numsB是我们要求的需要排序的最短子数组
// 则有for all numsA[i], for all numsB[j], for all numsC[k], numsA[i] < numsB[j] < numsC[k]
// * 例如left可以看成从右到左遍历，最后一个nums[i]> min{nums[i+1, n)}的i, 即从右到左最后一个不满足单调性质的i；
// * 例如right可以看成从左到到遍历，最后一个nums[i]< max{nums[0, i)}的i
// 利用此性质，和O(1)时间更新min的技巧，可以O(n), O(1)解决此问题；
// 且left, right可以一次遍历同时求出；


int main()
{
    cout<<"测试myVector1"<<endl;
    myVector1<int> myv1;
    myv1.print();
    myv1.push_back(1);
    myv1.push_back(3);
    myv1.push_back(2);
    myv1.print();

    cout<<"测试mypartition"<<endl;
    vector<int> nums{4,2,0,3,2,5};
    mypartitionOnO1(nums,3);
    printVector(nums);

    nums.assign({5,9,2,1,4,7,5,8,3,6});
    mypartitionOnO1(nums,5);
    printVector(nums);

    nums.assign({1,2,3,4,5,6,7,8,9,10});
    mypartitionOnO1(nums,3);
    printVector(nums);

    nums.assign({3,2,1});
    mypartitionOnO1(nums,2);
    printVector(nums);

    nums.assign({3});
    mypartitionOnO1(nums,3);
    printVector(nums);

    nums.assign({});
    mypartitionOnO1(nums,3);
    printVector(nums);


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
    nums.assign({1,3});
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

    cout<<"最长递增子序列"<<endl;
    nums.assign({10,9,2,5,3,7,101,18});
    cout<<lengthOfLIS_Onlogn(nums)<<endl;

    cout<<"数组中的第K个最大元素"<<endl;
    nums.assign({3,2,1,5,6,4});
    cout<<findKthLargest(nums, 2)<<endl;
    nums.assign({7,6,5,4,3,2,1});
    cout<<findKthLargest(nums, 2)<<endl;

    cout<<"除自身以外数组的乘积"<<endl;
    nums.assign({1,2,3,4});
    printVector(productExceptSelf(nums));
    nums.assign({-1,1,0,-3,3});
    printVector(productExceptSelf(nums));

    cout<<"完全平方数"<<endl;
    cout<<numSquares(12)<<endl;
    cout<<numSquares(13)<<endl;
    cout<<numSquaresDP(12)<<endl;
    cout<<numSquaresDP(13)<<endl;

    nums.assign({0,1,0,3,12});
    moveZeroes(nums);
    printVector(nums);

    cout<<"戳气球"<<endl;
    nums.assign({3,1,5,8});
    cout<<maxCoins(nums)<<endl;
    nums.assign({1,5});
    cout<<maxCoins(nums)<<endl;
    nums.assign({4,3,5,3,1});
    cout<<maxCoins(nums)<<endl;

    cout<<"零钱兑换"<<endl;
    nums.assign({1,2,5});
    cout<<coinChange(nums, 11)<<endl;
    nums.assign({2});
    cout<<coinChange(nums, 3)<<endl;
    nums.assign({1});
    cout<<coinChange(nums, 0)<<endl;
    nums.assign({1,2,5,10});
    cout<<coinChange(nums, 113)<<endl; // 13
    nums.assign({224,2,217,189,79,343,101});
    cout<<coinChange(nums, 2938)<<endl; // 11
    nums.assign({65,451,124,70,480,441});
    cout<<coinChange(nums, 4129)<<endl; // 10
    nums.assign({186,419,83,40}); 
    cout<<coinChange(nums, 6249)<<endl; // 25

    cout<<"零钱兑换II"<<endl;
    nums.assign({1,2,5});
    cout<<change2(5, nums)<<endl; // 4
    nums.assign({2});
    cout<<change2(3, nums)<<endl; // 0
    nums.assign({1,2,5,10});
    cout<<change2(35, nums)<<endl; // 140

    cout<<"前K个高频元素"<<endl;
    nums.assign({1,1,1,2,2,3});
    printVector(topKFrequent(nums, 2));
    nums.assign({1,1,1,2,2,3,3,3,3,3,3,3,3,3,3,3,9,9,9,9,8});
    printVector(topKFrequent(nums, 3));

    cout<<"分割等和子集"<<endl;
    nums.assign({1,5,11,5});
    cout<<canPartitionDP(nums)<<endl;
    nums.assign({1,2,3,5});
    cout<<canPartitionDP(nums)<<endl;
    nums.assign({100});
    cout<<canPartitionDP(nums)<<endl;

    cout<<"根据身高重建队列"<<endl;
    vector<vector<int>> people{{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    printVectorVector(people);
    printVectorVector(reconstructQueueAns(people));

    cout<<"找到所有数组中消失的数字"<<endl;
    nums.assign({4,3,2,7,8,2,3,1});
    printVector(findDisappearedNumbersOnO1(nums));
    nums.assign({1,1});
    printVector(findDisappearedNumbersOnO1(nums));

    cout<<"最短无序连续子数组"<<endl;
    nums.assign({2,6,4,8,10,9,15});
    cout<<findUnsortedSubarrayOnOn(nums)<<endl; // 5
    nums.assign({1,2,3,4});
    cout<<findUnsortedSubarrayOnOn(nums)<<endl; // 0
    nums.assign({2,1});
    cout<<findUnsortedSubarrayOnOn(nums)<<endl; // 2
    nums.assign({1,3,2,2,2});
    cout<<findUnsortedSubarrayOnOn(nums)<<endl; // 2

    return 0;
}