#include"DataStructure/Grid_2d.h"

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

    return 0;
}