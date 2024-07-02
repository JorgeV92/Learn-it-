#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& A, int t) {
    int l = 0, r = A.size() - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        // check if the middle elem is the t 
        if (A[m] == t) return m;

        // Determine which side is properly sorted 
        if (A[l] <= A[m]) {
            // Left side is sorted
            if (A[l] <= t && t < A[m]) {
                // Traget is in the left side
                r = m - 1;
            } else {
                // Target is in the right side
                l = m + 1;
            }
        } else {
            // Right side is sorted
            if (A[m] < t && t <= A[r]) {
                // Target is in the right side
                l = m + 1;
            } else {
                // Target is in the left side
                r = m - 1;
            }
        }   
    }
    // Target not found
    return -1;
}