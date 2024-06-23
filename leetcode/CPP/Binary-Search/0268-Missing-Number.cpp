//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  0268. Missing Number 
//
// Given an array nums containing n distinct numbers in the range [0, n], return the only number in the 
// range that is missing from the array.
// 
// Example 1:
// 
// Input: nums = [3,0,1]
// Output: 2
// Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number 
// in the range since it does not appear in nums.
// 
// Example 2:
// 
// Input: nums = [0,1]
// Output: 2
// Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number 
// in the range since it does not appear in nums.
// 
// Example 3:
// 
// Input: nums = [9,6,4,2,3,5,7,0,1]
// Output: 8
// Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 
//  is the missing number in the range since it does not appear in nums.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BinarySearch {
    public:
        int missignNumber(vector<int>& A) {
            if (A.empty()) return 0;
            sort(A.begin(), A.end());

            int l = 0, r = A.size();
            cout << "size of the array: " << r << endl;
            while (l < r) {
                int m = l + (r - l ) / 2;
                if (A[m] > m) {
                    r = m;      // the missing number is somewhere in the left of the array including m 
                } else {        // A[m] == m the missing number is somewhere in the right excluding m 
                    l = m + 1;  // all elemenst on the left are equal A[m] == m
                }
            }
            return l;
        }
};

int main () {
    vector<int> A = {0 ,1};
    BinarySearch bs;
    cout << bs.missignNumber(A) << endl;
    return 0;
}