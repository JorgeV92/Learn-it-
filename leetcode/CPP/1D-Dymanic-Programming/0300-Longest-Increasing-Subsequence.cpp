/*
 ______   _____        _____  __   _ _______
 |     \ |_____]      |     | | \  | |______
 |_____/ |            |_____| |  \_| |______
                                          

    0300-Longest-Increasing-Subsequence     (Medium)
    
    Given an integer array nums, return the length of the lomgest strickly increasing subsequence.
    
    Example 1:

    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
    
    Example 2:

    Input: nums = [0,1,0,3,2,3]
    Output: 4
    
    Example 3:

    Input: nums = [7,7,7,7,7,7,7]
    Output: 1    
*/

#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////
// This solution has a time complexity of O(n^2), where n is the length of the input list
///////////////////////////////////////////////////////////////////////////////////////////////

class DynamicProgramming1D {
    public:
        int lengthOfLIS(std::vector<int>& nums) {
            if (nums.empty()) return 0;

            std::vector<int> LIS(nums.size(), 1);

            for (size_t i = 1; i < nums.size(); i++) {
                for (size_t j = 0; j < i; j++) {
                    if (nums[i] > nums[j]) {
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// If the current number (nums[i]) is larger than any previous number (nums[j] where j ranges 
// from 0 to i-1), it indicates that we can lengthen the increasing subsequence that ends 
// at index i. Therefore, we update LIS[i] to be the greater of its current value (LIS[i]) and 
// LIS[j] + 1. This update means that at index i, the length of the subsequence is now the maximum 
// between its existing length and the length of the subsequence ending at index j plus one, accounting 
// for the current element
/////////////////////////////////////////////////////////////////////////////////////////////////////////
                        LIS[i] = std::max(LIS[i], LIS[j] + 1);
                    }
                }
            }
            return *std::max_element(LIS.begin(), LIS.end());

        }
};

int main() {
    DynamicProgramming1D dynamic;
    std::vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    std::vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    std::vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};

    std::cout << dynamic.lengthOfLIS(nums1) << std::endl;  // Output: 4
    std::cout << dynamic.lengthOfLIS(nums2) << std::endl;  // Output: 4
    std::cout << dynamic.lengthOfLIS(nums3) << std::endl;  // Output: 1

    return 0;
}