#include"DataStructure/Grid_2d.h"

/*
常用方法：
方向数组
暴力回溯遍历法, dfs
Z字形查找/对角线查找法：适用于有序矩阵搜索，不需要二分；
特殊: 最大矩形-单调栈，最大正方形-dp
*/

// 62. 不同路径
// 思路1. 回溯法或者遍历法，O(2^(m*n))，因为每个位置都有2种选择；(已实现，时间超限)
// 思路2. dp
int uniquePathsCount=0;
void dfs(int x, int y, int m, int n) {
    if(x==m-1 && y==n-1) {
        uniquePathsCount++;
        return;
    }
    // 方向数组：右下
    for(auto dir: direction2) {
        int new_x=x+dir[0];
        int new_y=y+dir[1];
        if(new_x<0 || new_x>=m) continue;
        if(new_y<0 || new_y>=n) continue;
        // using new_position (new_x, new_y)
        dfs(new_x, new_y, m,n);
    }
}
int uniquePaths(int m, int n) {
    uniquePathsCount=0;
    dfs(0,0,m,n);
    return uniquePathsCount;
}
// 思路2：dp[i,j]表示从(0,0)到(i,j)的路径数，有dp[i,j]=dp[i-1,j]+dp[i,j-1];
// 击败100%, 29%
int uniquePaths2(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n,1));
    for(int i=1;i<m;i++) {
        for(int j=1;j<n;j++) {
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[m-1][n-1];
}

// 64. 最小路径和
// 思路1. 遍历, O(2^(m*n))
// 思路2. dp O(m*n)
// 击败31%, 86%
int minPathSum(vector<vector<int>>& grid) {
    int m=grid.size(), n=grid[0].size();
    /*// 写法1. 利用方向数组，稍微复杂点；
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            int count_before=INT_MAX;
            for(auto dir: direction2) {
                // 利用右下方向和减法即为左上；
                int last_x = i-dir[0];
                int last_y = j-dir[1];
                if(last_x<0 || last_y<0) continue;
                if(grid[last_x][last_y]<count_before) // 取两者中最小值
                    count_before = grid[last_x][last_y];
            }
            if(count_before!=INT_MAX)
                grid[i][j]+=count_before;
        }
    }
    */
    
    // 写法2. 更清晰的写法，第一行和第一列分开计算；
    for(int i=1;i<m;i++) {
        grid[i][0]+=grid[i-1][0];
    }
    for(int j=1;j<n;j++) {
        grid[0][j]+=grid[0][j-1];
    }
    for(int i=1;i<m;i++) {
        for(int j=1;j<n;j++) {
            // min(左,上)
            grid[i][j]+= min(grid[i-1][j], grid[i][j-1]);
        }
    }
    
    return grid.back().back();
}

// 79. 单词搜索
// 上下左右: vector<vector<int>> direction4{{1,0},{0,1},{-1,0},{0,-1}};
// ! 使用direction4会超时；定义访问更快的结构；
int direction4_for_exist[4][2]={{1,0},{0,1},{-1,0},{0,-1}}; // 换用int数组直接击败83%, 20%
bool back_trace_exist(vector<vector<char>>& board, int i, int j, vector<vector<bool>> &flag, string &word, int start) {
    int m=board.size(), n=board[0].size();
    flag[i][j]=true;
    if(start==word.length()-1) {
        // 就差最后一个字符匹配了；
        for(int k=0;k<4;++k) {
            int new_x = i+direction4_for_exist[k][0];
            int new_y = j+direction4_for_exist[k][1];
            if(new_x<0 || new_x>=m || new_y<0 || new_y >=n || flag[new_x][new_y]==true) continue;
            if(board[new_x][new_y]==word[start]) {
                flag[i][j]=false; // ! return之前恢复原样，否则一些dfs过但不是解的位置的flag一直是true; 另一方面每次dfs前也不用重置为全false了；
                return true;
            }
        }
    }
    else {
        for(int k=0;k<4;++k) {
            int new_x = i+direction4_for_exist[k][0];
            int new_y = j+direction4_for_exist[k][1];
            if(new_x<0 || new_x>=m || new_y<0 || new_y >=n || flag[new_x][new_y]==true) continue;
            if(board[new_x][new_y]==word[start] && back_trace_exist(board, new_x,new_y, flag, word, start+1)) {
                flag[i][j]=false;
                return true;
            }
        }
    }

    flag[i][j]=false;
    return false;
}
bool exist(vector<vector<char>>& board, string word) {
    int m=board.size(), n=board[0].size();
    vector<vector<bool>> flag(m, vector<bool>(n));
    for(int i=0;i<m;++i) {
        for(int j=0;j<n;++j) {
            // for(auto &row: flag) { // ! for each修改vector时，需要引用;
            //     fill(row.begin(), row.end(), false);
            // }
            int start =1;
            if(word.size()==1 && board[i][j]==word[0])
                return true;
            if(board[i][j]==word[0] && back_trace_exist(board, i,j, flag, word, start))
                return true;
        }
    }
    return false;
}

// 85. 最大矩形
// 思路1：遍历法+略微优化；求每一个点从它开始向左的连续的1的个数，记录在left_num中，同样计算向上的连续1的个数记录在up_num中；
// 对left_num和up_num每一个都大于1的位置(可能形成长方形)，只需从该点开始向上最多尝试高up_num的矩形，计算这些矩形的最大值；
// O(mn^2)或O(m^2 n), 击败25%, 52%
int maximalRectangle(vector<vector<char>>& matrix) {
    // get_left_num;
    int m=matrix.size();
    if(m==0) return 0;
    int n=matrix[0].size();
    if(n==0) return 0;

    vector<vector<int>> left_num(m, vector<int>(n));
    vector<vector<int>> up_num(m, vector<int>(n));
    int ans=0;
    for(int i=0;i<m;++i) {
        for(int j=0;j<n;++j) {
            if(j==0)
                left_num[i][j]= matrix[i][j]=='1';
            else {
                if(matrix[i][j]=='1') {
                    left_num[i][j]=left_num[i][j-1]+1;
                }
                else {
                    left_num[i][j]=0;
                }
            }

            if(left_num[i][j]>ans)
                ans = left_num[i][j];
        }
    }

    for(int i=0;i<m;++i) {
        for(int j=0;j<n;++j) {
            if(i==0)
                up_num[i][j]= matrix[i][j]=='1';
            else {
                if(matrix[i][j]=='1') {
                    up_num[i][j]=up_num[i-1][j]+1;
                }
                else {
                    up_num[i][j]=0;
                }
            }

            if(up_num[i][j]>ans)
                ans = up_num[i][j];
        }
    }

    for(int i=0;i<m;++i) {
        for(int j=0;j<n;++j) {
            if(left_num[i][j]>=2 && up_num[i][j]>=2) {
                int minLeft = left_num[i][j];
                for(int k=1;k<up_num[i][j];++k) {
                    assert(i-k>=0);
                    if(minLeft>left_num[i-k][j])
                        minLeft=left_num[i-k][j];
                    
                    int area = minLeft * (k+1);
                    if(ans<area) {
                        ans = area;
                    }
                }
            }
        }
    }

    return ans;
}
// 思路2：单调栈，分析由left_num和up_num计算矩形面积的过程，可以转化成另一个问题——84. 柱状图中的最大矩形，见stack.cpp；
// 分析left_num的每一列，将其看成柱状图的输入，则刚好每一列都可以求出以该列为边的最大矩形，遍历所有列即为结果；
// 同理，up_num的每一行也可以转换成该问题；
// 复杂度：每行O(n)，共m行，O(mn)；
// TODO: 代码

// 221. 最大正方形, 85. 最大矩形变体，改成正方形；
// 思路1：类似85.的遍历法+优化，O(mn^2)或O(m^2 n)
// 思路2：dp, 正方形刚好可以递推; 
// ! 长方形不能递推，是因为面积a*b，有两个变量，这两个变量递推并不能保证构成新长方形, 且最大长方形面积可能对应多组{a,b}对
// dp[i,i]表示以点[i,j]为右下端点的正方形的最大边长；
// dp[i,i]= 0, if matrix[i][j]=='0'
//          min(dp[i-1, i-1], dp[i-1,i], dp[i,i-1])+1, if matrix[i][j]=='1'
// dp[0, i] = matrix[0][i]=='1', dp[i, 0] = matrix[i][0]=='1'
// O(mn), O(mn)击败98%, 5%
// TODO: 可选优化：空间可优化成O(min(m,n)); n>m则转置一下，然后一行行递推；需要特别处理下每行第一个元素；
int maximalSquare(vector<vector<char>>& matrix) {
    int m=matrix.size(), n = matrix[0].size(); // m, n >= 1
    vector<vector<int>> dp(m, vector<int>(n));
    int ans = 0;

    for(int i=0;i<m;++i) {
        dp[i][0]= matrix[i][0]=='1';
        if(dp[i][0]>ans) ans = dp[i][0];
    }
    for(int j=0;j<n;++j) { // ! n错写成m，小心!
        dp[0][j]= matrix[0][j]=='1';
        if(dp[0][j]>ans) ans = dp[0][j];
    }

    for(int i=1;i<m;++i) {
        for(int j=1;j<n;++j) {
            if(matrix[i][j]=='0') {
                dp[i][j]=0;
            }
            else {
                dp[i][j]= min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) +1; // ! dp[i-1][j-1]写成dp[i-1][i-1]，小心!
                if(dp[i][j]>ans) ans = dp[i][j];
            }
        }
    }
    return ans*ans;
}

// 240. 搜索二维矩阵 II
// 思路1: 二分查找，T(mn) = 3T(mn/4)+O(1), 根据主定理，T(mn) in O(n^(log_4 3)), 略小于O(mn), 击败10%, 16%
bool binarySearchMatrix(vector<vector<int>>& matrix, int target, int up, int down, int left, int right) {
    // 递归出口
    assert(up<=down && left<=right);
    if(up == down || left == right) {
        return false;
    }
    
    // 二分法
    int midx=(up+down)/2; // if up < down, then up <= midx < down
    int midy=(left+right)/2; // if left < right, then left <= midy < right
    if(matrix[midx][midy]==target) {
        cout<< "Found at (i, j) = (" << midx <<", "<<midy<<")"<<endl;
        return true;
    }
    else if(matrix[midx][midy]>target) {
        // 右下角>= matrix[midx][midy]>target, 不是解
        // 在 左上角 || 右上角 || 左下角
        // ! 二维情况请仔细画图，这些边界很容易搞错；
        return binarySearchMatrix(matrix, target, up, midx, left, midy) || 
                binarySearchMatrix(matrix, target, up, midx, midy, right) ||
                binarySearchMatrix(matrix, target, midx, down, left, midy);
    }
    else {
        // 左上角<= matrix[midx][midy]<target，不是解
        // 在 右下角 || 右上角 || 左下角
        // ! 注意和上面一种情况的右上角 || 左下角有一点区别，请画图仔细观察；
        return binarySearchMatrix(matrix, target, midx+1, down, midy+1, right) ||
                binarySearchMatrix(matrix, target, up, midx+1, midy+1, right) ||
                binarySearchMatrix(matrix, target, midx+1, down, left, midy+1);
    }
}
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    // Matrix在每行升序，每列升序；
    return binarySearchMatrix(matrix, target, 0, matrix.size(), 0, matrix[0].size());
}
// 思路2：Z字形查找
// * 从矩阵的右上角到左下角这条次对角线上，从右上角开始，if matrix[x][y]>target，则可以排除y列，如果<target，则可以排除x行；
// 也就是每次判断排除一行或一列，O(m+n)时间即可；击败61%, 14%
bool searchMatrixOmPlusn(vector<vector<int>>& matrix, int target) {
    // Matrix在每行升序，每列升序；
    int m = matrix.size(), n = matrix[0].size();
    int x= 0, y=n-1;
    while(x<m && y>=0) {
        if(matrix[x][y]==target) {
            return true;
        }
        else if(matrix[x][y]>target) {
            y--;
        }
        else {
            x++;
        }
    }
    return false;
}
// ! 类似题型：1351. 统计有序矩阵中的负数；




int main() {
    cout<<"方向数组示例"<<endl;
    printNextPositions4(0,0,3,3);
    printNextPositions4(1,2,4,4);
    printNextPositions4(2,3,4,4);

    cout<<"不同路径"<<endl;
    cout<<uniquePaths2(3,7)<<endl;
    cout<<uniquePaths2(3,2)<<endl;
    cout<<uniquePaths2(7,3)<<endl;

    cout<<"最小路径和"<<endl;
    vector<vector<int>> grid{{1,3,1},{1,5,1},{4,2,1}};
    cout<<minPathSum(grid)<<endl;

    cout<<"单词搜索"<<endl;
    vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    cout<<exist(board, "ABCCED")<<endl;
    cout<<exist(board, "SEE")<<endl;
    cout<<exist(board, "ABCB")<<endl;
    board.assign({{'A','B','C','E'},{'S','F','E','S'},{'A','D','E','E'}});
    cout<<exist(board, "ABCESEEEFS")<<endl;
    board.assign({{'C','A','A'},{'A','A','A'},{'B','C','D'}});
    cout<<exist(board, "AAB")<<endl;

    cout<<"最大矩形"<<endl;
    vector<vector<char>> matrix{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    cout<< maximalRectangle(matrix)<<endl;

    cout<<"最大正方形"<<endl;
    cout<< maximalSquare(matrix)<<endl;

    matrix.assign({{'0','1'},{'1','0'}});
    cout<< maximalSquare(matrix)<<endl;

    cout<<"搜索二维矩阵II"<<endl;
    vector<vector<int>> intMatrix{{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    cout<<searchMatrix(intMatrix, 5)<<endl;
    cout<<searchMatrix(intMatrix, 15)<<endl;
    cout<<searchMatrix(intMatrix, 20)<<endl;
    cout<<searchMatrix(intMatrix, 30)<<endl;

    return 0;
}