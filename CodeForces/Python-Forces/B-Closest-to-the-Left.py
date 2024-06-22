#################################################################################################
# Given an array of n numbers, sorted in non-decreasing order, and k queries. 
# For each query, print the maximum index of an array element
# not greater than the given one.
#
# Input:
# The first of the input contains integers n and k (0 < n, k <= 10^5), the length of the array 
# and the number of queries. The second line contains n elements of the array, sorted in 
# non-decreasing order. The third line contains k queries. All array elemetns and queries are 
# integers, each of which does not exceed 2 * 10^9 in absolute value.
# 
# Output:
# For each of the k queries, print the maximum index of an array element not greater than the 
# given one. If there are non, print 0.
# 
# Example input:
# 5 5
# 3 3 5 8 9
# 2 4 8 1 10
# 
# Example output:
# 0
# 2
# 4
# 0
# 5
# 
#################################################################################################


from typing import List
import bisect

def read_input():
    n, k = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))
    assert len(a) == n 
    q = list(map(int, input().strip().split()))
    assert len(q) == k
    return a, q

def binary_search_bisect(A: List[int], Q: List[int]) -> List[int]:
    result = []
    for q in Q:
        # Find the insertion point for q in A to maintain sorted order.
        index = bisect.bisect_right(A, q)
        # index is the position where q would go to keep A sorted,
        # which means all elements to the left of this index are <= q.
        # So, the maximum index of an element not greater than q is index - 1.
        if index > 0:
            result.append(index)
        else:
            result.append(0)
    return result

def binary_search(A, Q):
    result = []
    for q in Q:
        l = 0; r = len(A) - 1
        found = False
        while l <= r:
            m = l + (r - l) // 2
            if A[m] == q:
                result.append(m + 1)
                found = True
                break
            elif A[m] < q:
                l = m + 1
            else:
                r = m - 1
        if not found:
            result.append(r + 1)
    return result

def closest_to_the_left():
    n, k = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))
    queues = list(map(int, input().strip().split()))
    for x in queues:        
        l = -1  # a[i] <= x
        r = n   # a[r] > x
        while (r > l + 1):
            m = (l + r) // 2
            if a[m] <= x:
                l = m 
            else:
                r = m 
        print(l + 1)
        
        
    
if __name__ == "__main__":
    # A, Q = read_input()
    # res = binary_search(A, Q)
    # print("\n")
    # for num in res:
    #     print(num)
    
    closest_to_the_left()