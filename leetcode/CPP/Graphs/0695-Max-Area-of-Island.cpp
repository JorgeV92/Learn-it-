/*
    0695. Max Area of Island  (Medium)

    You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally 
    (horizontal or vertical). You may assume all four edges of the grid are surrounded by water. 

    The area of an island is the number of cells with a value 1 in the island.

    Return the maximum area of an island in grid. If there is no island, return 0.

    Example 1:

    Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],
                  [0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],
                  [0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]

    Output: 6
    Explanation: The answer is not 11, because the island must be connected 4-directionally.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

class Graph {
    public:
        int maxAreaOfIslandDFS(std::vector<std::vector<int>>& grid) {
            int maxArea = 0;    
            int rows = grid.size();
            int cols = grid[0].size();

            // DFS
            std::function<int(int, int)> dfs = [&](int r, int c) -> int {
                // check for out-of-bounds or water cells 
                if (r < 0 || r >= rows ||  c < 0 || c >= cols || grid[r][c] == 0) {
                    return 0;
                }

                // Mark the cell as visited by setting it to 0
                grid[r][c] = 0;

                // Calculate the area of the current island 
                int area = 1;    // Start with the current cell 
                area += dfs(r + 1, c);      // Down
                area += dfs(r - 1, c);      // Up
                area += dfs(r, c + 1);      // Right 
                area += dfs(r, c - 1);      // Left

                return area;           
            };

            // Iterate through each cell in the grid 
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    // if the cell is land (1), perform DFS to calcualte the area
                    if (grid[r][c] == 1) {
                        maxArea = std::max(maxArea, dfs(r, c));
                    }
                }
            }
            return maxArea;
        }

        int maxAreaOfIslandBFS(std::vector<std::vector<int>>& grid) {
            int maxArea = 0;
            int rows = grid.size();
            int cols = grid[0].size();

            // Directions array to explore all 4 possible directions (down, up, right, left)
            std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            // BFS 
            auto bfs = [&](int r, int c) {
                std::queue<std::pair<int, int>> q;
                q.push({r, c});
                grid[r][c] = 0;     // Mark cell
                int area = 0;

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    area++;     // Increment the area for each cell in the island

                    for (const auto& dir : directions) {
                        int newX = x + dir.first;
                        int newY = y + dir.second;

                        // check for out-of-bounds and if the cell is land
                        if (newX >= 0 && newX < rows && newY > 0 && newY < cols && grid[newX][newY] == 1) {
                            q.push({newX, newY});
                            grid[newX][newY] = 0;   // Mark the cell 
                        }
                    }
                }
                return area;
            };

            // iterate through each cell in the gird
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    // if the cell is land (1),  call BFS and calculate area
                    if (grid[r][c] == 1) {
                        maxArea = std::max(maxArea, bfs(r, c));
                    }
                }
            }
            return maxArea;
        }

};

int main() {
    Graph graph;

    std::vector<std::vector<int>> grid1 = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
    };

    // std::cout << "Maximum area of island in grid1 using DFS: " << graph.maxAreaOfIslandDFS(grid1) << std::endl;
    std::cout << "Maximum area of island in grid1 using BFS: " << graph.maxAreaOfIslandBFS(grid1) << std::endl;

    std::vector<std::vector<int>> grid2 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // std::cout << "Maximum area of island in grid2 using DFS: " << graph.maxAreaOfIslandDFS(grid2) << std::endl;
    std::cout << "Maximum area of island in grid2 using BFS: " << graph.maxAreaOfIslandBFS(grid2) << std::endl;

    return 0;
}