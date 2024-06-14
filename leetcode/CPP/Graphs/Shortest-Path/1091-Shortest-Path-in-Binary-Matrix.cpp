/*
    1091. Shortest Path in Binary Matrix    (Medium)

    Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. if 
    there is no clear path, return -1

    A clear path in a binary matrix is a path from the top-left (0, 0) to the bottom-right 
    cell (n-1, n-1) such that:

        - All the visited cells of the path are 0
        - All the adjacent cells of the path are 8-directionally connected (they are different and 
        they share an edge or a corner.)

    The length of a clear path is the number of visited cells of this path.
*/

#include <iostream>    // std::cout
#include <vector>      // std::vector
#include <queue>       // std::queue
#include <utility>     // std::pair

class ShortestPath {
    public:
        int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
            int n = grid.size();
            if (n == 0 || grid[0][0] != 0 || grid[n-1][n-1] != 0) {
                return -1;  // No clear path if start or end is blocked
            }

            // Directions for 8-directional movement 
            std::vector<std::pair<int, int>> directions = {{1,0}, {-1, 0}, {0, 1}, {0, -1}, 
                                                            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

            // Queue to perform BFS, start top-left corner
            std::queue<std::pair<int, int>> q;
            q.push({0, 0}); 
            grid[0][0] = 1;     // Mark the starting cell as visited 

            int pathLength = 1;

            // BFS 
            while (!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; i++) {
                    auto [x ,y] = q.front(); q.pop();  
                    // If we reached the bottom-right corner
                    if (x == n-1 && y == n-1) {
                        return pathLength;
                    }

                    // Explore all 8-directional movec
                    for (const auto& [dx, dy] : directions) {
                        int newX = x + dx;
                        int newY = y + dy;

                        // Check if the new cell is within bounds and not visited 
                        if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == 0) {
                            q.push({newX, newY});
                            grid[newX][newY];   // Mark the cell as visited
                        }
                    }               
                }
                ++pathLength;
            }
            return -1;  // No clear path found
        }
};

int main() {
    ShortestPath sp;
    
    std::vector<std::vector<int>> grid1 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}
    };
    std::cout << "Shortest path length in grid1: " << sp.shortestPathBinaryMatrix(grid1) << std::endl;
    // Output: 3

    std::vector<std::vector<int>> grid2 = {
        {0, 1},
        {1, 0}
    };
    std::cout << "Shortest path length in grid2: " << sp.shortestPathBinaryMatrix(grid2) << std::endl;
    // Output: 2

    std::vector<std::vector<int>> grid3 = {
        {1, 0},
        {0, 0}
    };
    std::cout << "Shortest path length in grid3: " << sp.shortestPathBinaryMatrix(grid3) << std::endl;
    // Output: -1

    return 0;
}