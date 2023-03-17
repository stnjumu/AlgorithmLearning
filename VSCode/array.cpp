#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<string>
using namespace std;

template<class T>
void printVector(vector<T> nums, string name = "vector") {
    cout<<name<<" = ";
    for(auto n:nums)
        cout<<n<<" ";
    cout<<endl;
}
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

int main()
{
    cout<< "接雨水"<<endl;
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};
    cout<< trap1(height)<<endl;

    height.assign({4,2,0,3,2,5});
    cout<< trap1(height)<<endl;

    height.assign({4,2,3});
    cout<< trap1(height)<<endl;

    vector<vector<int>> matrix{{1,2,3},{4,5,6},{7,8,9}};
    printVector(spiralOrder(matrix));

    matrix.assign({{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    printVector(spiralOrder(matrix));

    matrix.assign({{7},{9},{6}});
    printVector(spiralOrder(matrix));

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

    return 0;
}