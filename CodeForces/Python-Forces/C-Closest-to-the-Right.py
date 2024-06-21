###########################################################################################################################
# Given an array of 𝑛 numbers, sorted in non-decreasing order, and 𝑘 queries. 
# For each query, print the minimum index of an array element not less than the given one.
# 
# Input
# The first line of the input contains integers 𝑛 and 𝑘 (0 < 𝑛, 𝑘 ≤ 10^5 ), the length of the a
# rray and the number of queries. The second line contains 𝑛
#  elements of the array, sorted in non-decreasing order. The third line contains 𝑘 
# queries. All array elements and queries are integers, each of which does not exceed 2⋅10^9 in absolute value.
# 
# Output
# For each of the 𝑘 queries, print the minimum index of an array element not less than the given one. 
# If there are none, print 𝑛+1.
# 
# Example input:
# 5 5
# 3 3 5 8 9
# 2 4 8 1 10
# 
# Example output:
# 1
# 3
# 4
# 1
# 6
# 
###########################################################################################################################

from typing import List
import bisect

def read_input() -> (List[int], List[int]):
    n, k = map(int, input().split())
    A = list(map(int, input().split()))
    Q = list(map(int, input().split()))
    return A, Q

def binary_search_bisect(A: List[int], Q: List[int]) -> None:
    min_indices = []
    for q in Q:
        index = bisect.bisect_left(A, q)
        if index < len(A):
            min_indices.append(index + 1)
        else:
            min_indices.append(len(A) + 1)
    
    for num in min_indices:
        print(num)
def binary_search(A: List[int], Q: List[int]) -> None:
    min_indices = []
    for q in Q:
        l, r = 0, len(A) - 1
        result = len(A) + 1
        while l <= r:
            m = l + (r - l) // 2
            if A[m] >= q:
                result = m + 1  # Store the 1-based index
                r = m - 1
            else:
                l = m + 1
        min_indices.append(result)
    
    for num in min_indices:
        print(num)
    
if __name__ == "__main__":
    A, Q = read_input()
    binary_search(A, Q)