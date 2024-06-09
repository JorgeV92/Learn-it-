/*
    0213. House Robber II

    You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed.
     All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. 
     Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two 
     adjacent houses were broken into on the same night.

    Given an integer array nums representing the amount of money of each house, return the maximum amount of money you 
    can rob tonight without alerting the police.


    Example 1:

    Input: nums = [2,3,2]
    Output: 3
    Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
*/

#include <iostream>
#include <vector>

class DynamicProgramming1D {
    public:
        int rob(std::vector<int>& nums) {
            int n = nums.size();
            if (n == 0) return 0;
            if (n == 1) return nums[0];

            //Maximum amount robbed in a linear configuration 
            auto robLinear = [](std::vector<int>& nums, int start, int end) {
                int robCurrent = 0, skipCurrent = 0;
                for (int i = start; i <= end; i++) {
                    int robNext = skipCurrent + nums[i];
                    int skipNext = std::max(skipCurrent, robCurrent);
                    robCurrent = robNext;
                    skipCurrent = skipNext;
                }
                return std::max(robCurrent, skipCurrent);
            };

            // Scenario 1: Exclude the last house 
            int moneyExcludingLast = robLinear(nums, 0, n - 2);

            // Scenario 2: Exlude the first house 
            int moneyExcludeFirst = robLinear(nums, 1, n - 1);

            return std::max(moneyExcludeFirst, moneyExcludingLast);
        }
};