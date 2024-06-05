/*
    Greedy 

    53. Maximum Subarray 

    Given an integer array nums, find the subarray with the largest sum, and return its sum.

    Example 1:

    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: The subarray [4,-1,2,1] has the largest sum 6.

*/

#include <iostream>
#include <algorithm>
#include <vector>

class Greedy {
    public: 
        int maxSubArray(std::vector<int>& arr) {
            int maxCurrent = arr[0];
            int maxGlobal = arr[0];

            for (size_t i = 1; i < arr.size(); i++) {
                maxCurrent = std::max(arr[i], maxCurrent + arr[i]);
                if (maxCurrent > maxGlobal) {
                    maxGlobal = maxCurrent;
                }
            }
            return maxGlobal;
        }
};

int main () {

    Greedy gd;

    std::vector<int> arr1 = {-2,1,-3,4,-1,2,1,-5,4};
    std::cout << "Max Subarray Sum : " << gd.maxSubArray(arr1) << std::endl; 

    return 0;
}