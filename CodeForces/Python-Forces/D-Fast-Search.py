#################################################################################################
#                                   D. Fast Search
#       
# You are given an array 𝑎 of 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛.
# 
# Your task is to response to the queries like "How many numbers' values are between 𝑙and 𝑟?".
# 
# Input
# The first line of the input contains 𝑛 — the length of the array (1 ≤ 𝑛 ≤ 10^5).
# 
# The second line contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (−10^9 ≤ 𝑎𝑖 ≤ 10^9).
# 
# The third line contains integer 𝑘 — the number of queries (1 ≤ 𝑘 ≤ 10^5).
# 
# The following 𝑘 lines contain a pair of integers 𝑙 𝑟 — query, described above (−10^9 ≤ 𝑙 ≤ 𝑟 ≤ 10^9).
# 
# Output
# The output must consist of 𝑘 integers — responses for the queries.
# 
# Example
# 
# input
# 5
# 10 1 10 3 4
# 4
# 1 10
# 2 9
# 3 4
# 2 2
# 
# output 
# 5 2 2 0 
#################################################################################################

from sys import stdin
import bisect

def read_input():
    n = int(input())            # read the first line
    A = list(map(int, input().strip().split())) # read the second line
    k = int(input())  # read the third line
    # TODO
    pass

def binary_search():
    n = int(input())
    A = list(map(int, input().strip().split()))
    k = int(input())
    A.sort()
    interval = []
    for _ in range(k):
        l, r = map(int, input().strip().split())
        
        def binary_search_left(A, x):
            l = 0; r = len(A) - 1
            while l <= r:
                m = l + (r - l) // 2
                if A[m] < x:
                    l = m + 1
                else:
                    r = m - 1 
            return l
        
        def binary_search_right(A, x):
            l = 0; r = len(A) - 1
            while l <= r:
                m = l + (r - l) // 2
                if A[m] <= x:
                    l = m + 1
                else:
                    r = m - 1
            return l 

        index_left = binary_search_left(A, l)
        index_right = binary_search_right(A, r)
        interval.append(index_right - index_left)
        print()
    for num in interval:
        print(num, end=" ")            
    
    
def binary_search_bisect():
    n = int(input())            # read the first line
    A = list(map(int, input().strip().split())) # read the second line
    # 10 1 10 3 4
    # 1 3 4 10 10
    A.sort()    # O(nlogn)
    k = int(input())  # read the third line
    interval = []
    for _ in range(k):
        #  1 10
        l, r = map(int, input().strip().split())
        index_left = bisect.bisect_left(A, l)
        index_right = bisect.bisect_right(A, r)
        interval.append(index_right - index_left)
    print()
    for num in interval:
        print(num, end=" ")
         
if __name__ == "__main__":
    binary_search()
    
    
    

