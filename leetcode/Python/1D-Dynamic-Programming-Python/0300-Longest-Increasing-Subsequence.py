'''
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
'''
##############################################################################################
#   This solution has a time complexity of O(n^2), where n is the length of the input list
##############################################################################################
from typing import List

class DynamicProgramming1D:
    def lengthOfLIS(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        n = len(nums)
        
        LIS = [1] * n
        
        for i in range(1, n):
            for j in range(i):                
##########################################################################################################
# If the current number (nums[i]) is larger than any previous number (nums[j] where j ranges 
# from 0 to i-1), it indicates that we can lengthen the increasing subsequence that ends 
# at index i. Therefore, we update LIS[i] to be the greater of its current value (LIS[i]) and 
# LIS[j] + 1. This update means that at index i, the length of the subsequence is now the maximum 
# between its existing length and the length of the subsequence ending at index j plus one, accounting 
# for the current element
#########################################################################################################             
                if nums[i] > nums[j]:
                    LIS[i] = max(LIS[i], LIS[j] + 1)
                    
        return max(LIS)

if __name__ == "__main__":
    dynamic = DynamicProgramming1D()
    nums1 = [10, 9, 2, 5, 3, 7, 101, 18]
    nums2 = [0, 1, 0, 3, 2, 3]
    nums3 = [7, 7, 7, 7, 7, 7, 7]
    print(dynamic.lengthOfLIS(nums1))
    print(dynamic.lengthOfLIS(nums2))
    print(dynamic.lengthOfLIS(nums3))