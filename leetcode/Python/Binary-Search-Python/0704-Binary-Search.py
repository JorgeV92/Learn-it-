'''
 ______  _____ __   _ _______  ______ __   __      _______ _______ _______  ______ _______ _     _
 |_____]   |   | \  | |_____| |_____/   \_/        |______ |______ |_____| |_____/ |       |_____|
 |_____] __|__ |  \_| |     | |    \_    |         ______| |______ |     | |    \_ |_____  |     |
                                                                                                 
                                                                                                 
    0704 Binary Search  (Easy)
    
    Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to 
    search target in nums. If target exists, then return its index. Otherwise, return -1.
    
    Example 1:

    Input: nums = [-1,0,3,5,9,12], target = 9
    Output: 4
    Explanation: 9 exists in nums and its index is 4
    
    Example 2:

    Input: nums = [-1,0,3,5,9,12], target = 2
    Output: -1
    Explanation: 2 does not exist in nums so return -1
'''
from typing import List

class BinarySearch:
    def search(self, nums: List[int], target: int) -> int:
        """
        Performs binary search on a sorted list of integers to find the target value.
        
        :param nums: List[int] - A list of integers sorted in ascending order.
        :param target: int - The integer value to search for.
        :return: int - The index of the target if found, otherwise -1.
        """
        left_index = 0  # Initialize the left boundry of the search space 
        right_index = len(nums) - 1 # Initialzie the right boundary of the search space
        
        while left_index <= right_index:
            middle_index = (left_index + right_index) // 2  # Calculate the  middle index
            middle_value = nums[middle_index]               # Get the value at middle index
            
            if middle_value == target:
                return middle_index # If the middle value is the target, return the index
            elif middle_value < target:
                left_index = middle_index + 1   # if target is greater, ignore the left half
            else:
                right_index = middle_index - 1  # if the target is smaller, ignore the right half
            
        return -1   # Target is not founf in the lsit
    
    
if __name__ == "__main__":
    nums = [-1,0,3,5,9,12]
    target = 9
    search_instance = BinarySearch()
    result = search_instance.search(nums, target)
    print(result)  # Output: 4

            

        

