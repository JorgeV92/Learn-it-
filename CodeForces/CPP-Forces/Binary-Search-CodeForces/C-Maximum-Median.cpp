///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                          C. Maximum Median
// 
// You are given an array 𝑎 of 𝑛 integers, where 𝑛 is odd. You can make the following operation with it:
// 
// Choose one of the elements of the array (for example 𝑎𝑖 ) and increase it by 1 (that is, replace it with 𝑎𝑖+1).
// You want to make the median of the array the largest possible using at most 𝑘 operations.
// 
// The median of the odd-sized array is the middle element after the array is sorted in non-decreasing order. 
// For example, the median of the array [1,5,2,3,5] is 3.
// 
// Input
// The first line contains two integers 𝑛 and 𝑘 (1 ≤ 𝑛 ≤ 2⋅10^5, 𝑛 is odd, 1 ≤ 𝑘 ≤ 10^9) — 
// the number of elements in the array and the largest number of operations you can make.
// 
// The second line contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (1 ≤ 𝑎𝑖 ≤ 10^9).
// 
// Output
// Print a single integer — the maximum possible median after the operations.
//
// Example
// input 
// 3 2
// 1 3 5
//
// output
// 5
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>


 void maximumMedian() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());

    auto good = [&](int x) {
        long long ops_needed = 0;
        for (int i  = (n - 1) / 2; i < n; i++) {
            ops_needed += std::max(0, x - a[i]);
        }
        return ops_needed <= k;
    };

    int l = 0, r = 2e9;
    while (l < r) {
        int m = l + (r - l + 1) / 2;
        if (good(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    std::cout << l << std::endl;
 }

 int main() {
    maximumMedian();
    return 0;
 }
