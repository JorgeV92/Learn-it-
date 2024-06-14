'''
 _______ _     _  _____   ______ _______ _______ _______ _______       _____  _______ _______ _     _     
 |______ |_____| |     | |_____/    |    |______ |______    |         |_____] |_____|    |    |_____|     
 ______| |     | |_____| |    \_    |    |______ ______|    |         |       |     |    |    |     |     
                                                                                                       


     1091. Shortest Path in Binary Matrix    (Medium)

    Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. if 
    there is no clear path, return -1

    A clear path in a binary matrix is a path from the top-left (0, 0) to the bottom-right 
    cell (n-1, n-1) such that:

        - All the visited cells of the path are 0
        - All the adjacent cells of the path are 8-directionally connected (they are different and 
        they share an edge or a corner.)

    The length of a clear path is the number of visited cells of this path.
'''

from collections import deque
from typing import List, Tuple

class ShortestPath:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if n == 0 or grid[0][0] != 0 or grid[n-1][n-1] != 0:
            return -1  # No clear path if start or end is blocked
        
        # Directions for 8-directional movemenet 
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (-1, 1), (1, -1), (-1, -1)]
        
        # Queue to perform BFS, start top-left corner
        q = deque([(0, 0)])
        grid[0][0] = 1 # Mark the starting cell as visited
        
        pathLength = 1
        
        # BFS 
        while q:
            size = len(q)
            for _ in range(size):
                x, y = q.popleft()
                # if we reached the bottom-right corner
                if x == n - 1 and y == n - 1:
                    return pathLength
                
                # Explore all 8-directional moves
                for dx, dy in directions:
                    newX, newY = x + dx, y + dy
                    
                    # check if the new cell is within bounds and not visited
                    if 0 <= newX < n and 0 <= newY < n and grid[newX][newY] == 0:
                        q.append((newX, newY))
                        grid[newX][newY] = 1 # Mark the cell as visited 
            pathLength += 1
            
        return -1 # No clear path found
    
if __name__ == "__main__":
    sp = ShortestPath()
    
    grid1 = [
        [0, 1, 0],
        [1, 0, 0],
        [0, 0, 0]
    ]
    print(f"Shortest path length in gird1: {sp.shortestPathBinaryMatrix(grid1)}")
    
    grid2 = [
        [0, 1],
        [1, 0]
    ]
    print(f"Shortest path length in grid2: {sp.shortestPathBinaryMatrix(grid2)}")


    grid3 = [
        [1, 0],
        [0, 0]
    ]
    print(f"Shortest path length in grid3: {sp.shortestPathBinaryMatrix(grid3)}")
    
