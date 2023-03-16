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

    return 0;
}