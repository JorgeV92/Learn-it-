'''
 ______  _____ __   _ _______  ______ __   __      _______ _______ _______  ______ _______ _     _
 |_____]   |   | \  | |_____| |_____/   \_/        |______ |______ |_____| |_____/ |       |_____|
 |_____] __|__ |  \_| |     | |    \_    |         ______| |______ |     | |    \_ |_____  |     |
                                                                                                 
                                                                                                 
    0153. Find Minimum in Rotated Sorted Array  (Medium)
    
    Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For exmpale, the array 
    nums = [0, 1, 2, 4, 5, 6, 7] might become: 
    
        - [4,5,6,7,0,1,2] if it was rotated 4 times.
        - [0,1,2,4,5,6,7] if it was rotated 7 times.
        
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums of unique elements, return the minimum element of this array.
'''

from typing import List

class BinarySearch:
    def findMin(self, nums: List[int]) -> int:
        """
        Finds the minimum element in a rotated sorted array.
        
        :param nums: List[int] - A rotated sorted list of unique integers.
        :return: int - The minimum element in the list.
        """
        left_index = 0  # Initialize the left boundary of the search space
        right_index = len(nums) - 1 # Initialize the right boundary of the search space
        
        # if the list is not rotated (or rotated len(nums) times), the first element is the samllest 
        if nums[left_index] <= nums[right_index]:
            return nums[left_index]
        
        while left_index <= right_index:
            middle_index = (left_index + right_index) // 2      # Calculate the middle index
            
            # if the middle element is greater than the rightmost element, the smallest value is in the 
            # right half
            if nums[middle_index] > nums[right_index]:
                left_index = middle_index + 1
            else:   # otherwise, the smallest value is in the left half including the middle element     
                right_index = middle_index - 1
                
        # After the loop, left_index should point to the smallest value
        return nums[left_index]
    
if __name__ == "__main__":
    nums = [4, 5, 6, 7, 0, 1, 2]
    search_instance = BinarySearch()
    result = search_instance.findMin(nums)
    print(result)  # Output: 0