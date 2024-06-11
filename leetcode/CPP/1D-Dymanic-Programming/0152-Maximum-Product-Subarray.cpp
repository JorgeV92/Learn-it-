/*
    0152. Maximum Product Subarray

    Given an integer array nums, find subarray thay has the largest product, and return the product.

    Example 1:

    Input: nums = [2,3,-2,4]
    Output: 6
    Explanation: [2,3] has the largest product 6.

    Example 2:

    Input: nums = [-2,0,-1]
    Output: 0
    Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

#include <iostream>
#include <vector>

class DynamicProgramming1D {
    public:
        int maxProduct(std::vector<int>& nums) {
            if (nums.empty()) return 0;

            int maxProduct = nums[0];
            int minProduct = nums[0];
            int globalMaxProduct = nums[0];

            for (size_t i = 1; i < nums.size(); i++) {
                // if the current element is negative, swap maxProduct and minProduct 
                if (nums[i] < 0) {
                    std::swap(maxProduct, minProduct);
                }

                maxProduct = std::max(nums[i], maxProduct * nums[i]);
                minProduct = std::min(nums[i], minProduct * nums[i]);

                globalMaxProduct = std::max(globalMaxProduct, maxProduct);
            }
            return globalMaxProduct;
        }
};

int main() {
   DynamicProgramming1D dynamic;
    
    std::vector<int> nums1 = {2, 3, -2, 4};
    std::cout << "Maximum product for nums1: " << dynamic.maxProduct(nums1) << std::endl;
    // Output: 6 (Explanation: [2, 3] has the largest product 6)
    
    std::vector<int> nums2 = {-2, 0, -1};
    std::cout << "Maximum product for nums2: " << dynamic.maxProduct(nums2) << std::endl;
    // Output: 0 (Explanation: The result cannot be 2, because [-2, -1] is not a subarray)
    
    std::vector<int> nums3 = {-2, 3, -4};
    std::cout << "Maximum product for nums3: " << dynamic.maxProduct(nums3) << std::endl;
    // Output: 24 (Explanation: [-2, 3, -4] has the largest product 24)
    
    std::vector<int> nums4 = {0, 2};
    std::cout << "Maximum product for nums4: " << dynamic.maxProduct(nums4) << std::endl;
    // Output: 2 (Explanation: [2] has the largest product 2)
    
    return 0;
}