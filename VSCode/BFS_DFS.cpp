#include<iostream>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<stack>
using namespace std;

// 695. 岛屿最大面积 (完成)
// 200. 岛屿数量 (完成)
// 463. 岛屿周长
// 994. 腐烂的橘子
// 矩阵中的单词：https://leetcode.cn/problems/ju-zhen-zhong-de-lu-jing-lcof/

int dfs_get_island_area(vector<vector<int>> &grid, int i, int j, vector<vector<bool>> &searched) {
    int cnt = 1;
    searched[i][j] = true;
    // 上
    if (i>0 && grid[i-1][j]==1 && !searched[i-1][j])
    {
        cnt += dfs_get_island_area(grid, i-1, j, searched);
    }
    // 下
    if (i<grid.size()-1 && grid[i+1][j]==1 && !searched[i+1][j])
    {
        cnt += dfs_get_island_area(grid, i+1, j, searched);
    }
    
    // 左
    if (j>0 && grid[i][j-1]==1 && !searched[i][j-1])
    {
        cnt += dfs_get_island_area(grid, i, j-1, searched);
    }
    // 右
    if (j<grid[0].size()-1 && grid[i][j+1]==1 && !searched[i][j+1])
    {
        cnt += dfs_get_island_area(grid, i, j+1, searched);
    }
    return cnt;
}

int bfs_get_island_area(vector<vector<int>> &grid, int i, int j, vector<vector<bool>> &searched) {
    searched[i][j] = true;
    int cnt = 0;
    stack<pair<int, int>> s;
    s.push({i,j});

    while(!s.empty()) {
        auto p = s.top();
        cnt++;
        s.pop();
        // searched[p.first][p.second]=true;
        i = p.first;
        j = p.second;

        if (i>0 && grid[i-1][j]==1 && !searched[i-1][j])
        {
            searched[i-1][j] = true;
            s.push({i-1,j});
        }
        // 下
        if (i<grid.size()-1 && grid[i+1][j]==1 && !searched[i+1][j])
        {
            searched[i+1][j] = true;
            s.push({i+1,j});
        }
        
        // 左
        if (j>0 && grid[i][j-1]==1 && !searched[i][j-1])
        {
            searched[i][j-1] = true;
            s.push({i,j-1});
        }

        // 右
        if (j<grid[0].size()-1 && grid[i][j+1]==1 && !searched[i][j+1])
        {
            searched[i][j+1] = true;
            s.push({i,j+1});
        }
    }
    return cnt;
}

int find_max_island_DFS(vector<vector<int>> &grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    
    int m = grid.size(), n= grid[0].size();
    vector<vector<bool>> searched;

    for (size_t i = 0; i < m; i++)
    {
        vector<bool> v(n, false);
        searched.push_back(v);
    }
    
    int max = 0;
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            if(!searched[i][j] && grid[i][j]==1) {
                int i_size = dfs_get_island_area(grid, i, j, searched);
                if (max < i_size)
                {
                    max = i_size;
                }
            }
        }
        
    }
    return max;
}

int find_max_island_BFS(vector<vector<int>> &grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    
    int m = grid.size(), n= grid[0].size();
    vector<vector<bool>> searched;

    for (size_t i = 0; i < m; i++)
    {
        vector<bool> v(n, false);
        searched.push_back(v);
    }
    
    int max = 0;
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            if(!searched[i][j] && grid[i][j]==1) {
                int i_size = bfs_get_island_area(grid, i, j, searched);
                if (max < i_size)
                {
                    max = i_size;
                }
            }
        }
        
    }
    return max;
}

void bfs_island(vector<vector<int>> &grid, int i, int j, vector<vector<bool>> &searched) {
    searched[i][j] = true;
    stack<pair<int, int>> s;
    s.push({i,j});

    while(!s.empty()) {
        auto p = s.top();
        s.pop();
        // searched[p.first][p.second]=true;
        i = p.first;
        j = p.second;

        if (i>0 && grid[i-1][j]==1 && !searched[i-1][j])
        {
            searched[i-1][j] = true;
            s.push({i-1,j});
        }
        // 下
        if (i<grid.size()-1 && grid[i+1][j]==1 && !searched[i+1][j])
        {
            searched[i+1][j] = true;
            s.push({i+1,j});
        }
        
        // 左
        if (j>0 && grid[i][j-1]==1 && !searched[i][j-1])
        {
            searched[i][j-1] = true;
            s.push({i,j-1});
        }

        // 右
        if (j<grid[0].size()-1 && grid[i][j+1]==1 && !searched[i][j+1])
        {
            searched[i][j+1] = true;
            s.push({i,j+1});
        }
    }
}

int find_island_num_BFS(vector<vector<int>> &grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    
    int m = grid.size(), n= grid[0].size();
    vector<vector<bool>> searched;

    for (size_t i = 0; i < m; i++)
    {
        vector<bool> v(n, false);
        searched.push_back(v);
    }
    
    int cnt = 0;
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            if(!searched[i][j] && grid[i][j]==1) {
                bfs_island(grid, i, j, searched); // 使用find_max_island_BFS也可；
                cnt++;
            }
        }
        
    }
    return cnt;
}

int main()
{
    cout<< "求岛屿最大面积"<<endl;
    vector<vector<int>> grid{
            {0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}
        };
    cout<<find_max_island_DFS(grid)<<endl;
    cout<<find_max_island_BFS(grid)<<endl;

    cout<< "求岛屿个数"<<endl;
    vector<vector<int>> grid2{
            {1,1,1,1,0},
            {1,1,0,1,0},
            {1,1,0,0,0},
            {0,0,0,0,0}
        };
    cout<<find_island_num_BFS(grid2)<<endl;
    vector<vector<int>> grid3{
            {1,1,0,0,0},
            {1,1,0,0,0},
            {0,0,1,0,0},
            {0,0,0,1,1}
        };
    cout<<find_island_num_BFS(grid3)<<endl;
    return 0;
}