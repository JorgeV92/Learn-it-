/*
    0198. House Robber

    You are a professional robber planning to rob houses along a street. Each house has
    a certain amount of money stashed, the only constraint stopping you from robbing each of them
    is that adjacent houses have security systems connected and it will automatically contact the 
    police if two adjecent houses were broken into on the same night.

    Given an integer array nums representing the amount of money of each house, return maximum amount 
    of money you can rob tonight without alerting the police. 

    Example 1:

    Input: nums = [1,2,3,1]
    Output: 4
    Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
    Total amount you can rob = 1 + 3 = 4.
*/

#include <iostream>
#include <vector>

class DynamicProgramming1D {
    public:
        int rob(std::vector<int>& nums) {
            int n = nums.size();
            if (n == 0) return 0;
            if (n == 1) return nums[0];

            std::vector<int> maxRobAmount(n);
            maxRobAmount[0] = nums[0];
            maxRobAmount[1] = std::max(nums[0], nums[1]);

            for (int i = 2; i < n; i++) {
                maxRobAmount[i] = std::max(maxRobAmount[i - 1], maxRobAmount[i - 2] + nums[i]);
            }
            
            return maxRobAmount[n-1];
        }

        int robSpace(std::vector<int>& nums) {
            int robCurrent = 0;     // Max money if the current house is robbed
            int skipCurrent = 0;    // Max money if the current house is not robbed

            for (int i = 0; i < nums.size(); i++) {
                // If we rob the current house, add its value to the max value of skipping 
                // the previous house 
                int robNext = skipCurrent + nums[i];
                // If we skip the current house, take the max value of either
                // robbing or skipping the previous house
                int skipNext = std::max(skipCurrent, robCurrent);

                robCurrent = robNext;
                skipCurrent = skipNext;
            }
            return std::max(robCurrent, skipCurrent);
        }
};

int main() {
    std::vector<int> nums {1, 2, 3, 1};
    DynamicProgramming1D dynamic;

    std::cout << "House Robber Max Amount : " << dynamic.robSpace(nums) << std::endl;

    return 0;
}