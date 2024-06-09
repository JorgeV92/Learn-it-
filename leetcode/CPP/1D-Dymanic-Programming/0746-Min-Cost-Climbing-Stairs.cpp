/*
    0746. Min Cost Climbing Stairs

    You are given an integer array cost where cost[i] is the cost ith step on a staicase. Once you 
    pay the cost, you can either climb one or two steps.

    You can either start from the step with index 0, or the step with index 1.

    return the minimum cost to reach the top of the floor. 

    Example 1:

    Input: cost = [10,15,20]
    Output: 15
    Explanation: You will start at index 1.
    - Pay 15 and climb two steps to reach the top.
    The total cost is 15.
*/

#include <iostream>
#include <vector>

class DynamicProgramming1D {
    public:
        int minCostClimbingStairs(std::vector<int>& cost) {
            int n = cost.size();
            if (n == 0) return 0;
            if (n == 1) return cost[0];

            // Dynamic Programming array to store the minimum cost 
            std::vector<int> minCost(n);
            minCost[0] = cost[0];
            minCost[1] = cost[1];

            for (int i = 2; i < n; i++) {
                minCost[i] = cost[i] + std::min(minCost[i-1], minCost[i-2]);
            }
            return std::min(minCost[n-1], minCost[n - 2]);
        }
};

int main() {

    std::vector<int> cost {10, 15, 20};
    DynamicProgramming1D dynamic;

    std::cout << "Min cost climbing stairs : " << dynamic.minCostClimbingStairs(cost) << std::endl;

    return 0;
}