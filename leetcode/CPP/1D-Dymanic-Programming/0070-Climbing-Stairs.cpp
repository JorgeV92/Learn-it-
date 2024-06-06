/*
    0070. Climbing Stairs   (Easy)

    You are climbing a staircase. It takes n steps to reach the top. 

    Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? 

    Example 1:

    Input: n = 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps
*/

#include <iostream>
#include <vector>

class DynamicProgramming1D {
    public:
        int climbStairs(int n) {
            if (n <= 1) return 1;   // Base case for 1 step
            if (n == 2) return 2;   // Baase case for 2 steps

            int prev1 = 1;      // Ways to reach the step n-1
            int prev2 = 2;      // Ways to reach the step n-2
            int current;

            for (int i = 3; i <= n; i++) {
                current = prev1 + prev2;    // Ways to reach the current step
                prev1 = prev2;              // Update prev1 to prev2
                prev2 = current;            // Update prev2 to current 
            }
            return current;
        }

        int climbStairsDP(int steps) {
            // Base cases: 1 way to climb 0 or 1 step
            if (steps == 0 || steps == 1) {
                return 1;
            }

            // A vector to store the number of ways to climb to each step 
            std::vector<int> waysToClimb(steps + 1);
            waysToClimb[0] = waysToClimb[1] = 1;

            // Compute the number of ways to climb to each step from 2 to steps
            for (int step = 2; step <= steps; ++step) {
                waysToClimb[step] = waysToClimb[step - 1] + waysToClimb[step - 2];
            }

            return waysToClimb[steps];
        }
};

int main() {
    int n = 2;

    DynamicProgramming1D dynamic;
    
    int result = dynamic.climbStairs(n);
    int result_dynamic = dynamic.climbStairsDP(n);

    std::cout << "Climbing Stairs no DP : " << result << std::endl;

    std::cout << "Climbing Stairs with DP : " << result_dynamic << std::endl;

    return 0;
}