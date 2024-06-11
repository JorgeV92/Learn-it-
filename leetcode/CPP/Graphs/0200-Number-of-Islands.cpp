/*
    0200. Number of Islands 

    Given an m x n 2D binary grid `grid` which representes a map of `1`s (land) and `0`s (water),
    return the number of islands.

    As island is surrounded by water and is formed by connecting adjacent lands horizontally or 
    vertically. You may assume all four edges of the grid are all surrouneded by water. 

    Example 1:

    Input: grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
    Output: 1
*/

#include <iostream>
#include <vector>
#include <functional>
#include <queue>

class Graph {
    public:
        int numIslandsDFS(std::vector<std::vector<char>>& grid) {
            if (grid.empty()) return 0;

            int m = grid.size();
            int n = grid[0].size();
            int numIslands = 0;

            std::function<void(int, int)> dfs = [&](int i, int j) -> void {
                // check for out-of-bounds or water cell 
                if ( i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
                    return;
                }

                // Mark the cell as visited by setting it to '0'
                grid[i][j] = '0';

                // expand all 4 possible diresntion (up, down, left, right)
                dfs(i + 1, j);      // down 
                dfs(i - 1, j);      // up 
                dfs(i, j + 1);      // right
                dfs(i, j - 1);      // left
            };

            // iterate through each cell in the grid
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    // if the cell is '1' (land), we found an island
                    if (grid[i][j] == '1') {
                        numIslands++;
                        dfs(i, j);
                    }
                }
            }
            return numIslands;
        }

        int numIslandsBFS(std::vector<std::vector<char>>& grid) {
            if (grid.empty()) return '0';

            int m = grid.size();
            int n = grid[0].size();
            int numIslands = 0;

            std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            auto bfs = [&](int i, int j) {
                std::queue<std::pair<int, int>> q;
                q.push({i, j});
                grid[i][j] = '0';   

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (auto& dir : directions) {
                        int newX = x + dir.first;
                        int newY = y + dir.second;

                        if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] == '1') {
                            grid[newX][newY] = '0';
                            q.push({newX, newY});
                        }
                    }
                }
            };

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == '1') {
                        numIslands++;
                        bfs(i, j);
                    }
                }
            }
            return numIslands;
        }
};


int main() {
    std::vector<std::vector<char>> gird {{'1','1','0','0','0'},
                                        {'1','1','0','0','0'},
                                        {'0','0','1','0','0'},
                                        {'0','0','0','1','1'}};

    Graph g; 

    int result = g.numIslandsBFS(gird);

    std::cout << "Number of Islands : " << result << std::endl;

    return 0;
}