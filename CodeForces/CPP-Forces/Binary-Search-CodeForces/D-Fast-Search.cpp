////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   D. Fast Search
//       
// You are given an array 𝑎 of 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛.
// 
// Your task is to response to the queries like "How many numbers' values are between 𝑙and 𝑟?".
// 
// Input
// The first line of the input contains 𝑛 — the length of the array (1 ≤ 𝑛 ≤ 10^5).
// 
// The second line contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (−10^9 ≤ 𝑎𝑖 ≤ 10^9).
// 
// The third line contains integer 𝑘 — the number of queries (1 ≤ 𝑘 ≤ 10^5).
// 
// The following 𝑘 lines contain a pair of integers 𝑙 𝑟 — query, described above (−10^9 ≤ 𝑙 ≤ 𝑟 ≤ 10^9).
// 
// Output
// The output must consist of 𝑘 integers — responses for the queries.
// 
// Example
// 
// input
// 5
// 10 1 10 3 4
// 4
// 1 10
// 2 9
// 3 4
// 2 2
// 
// output 
// 5 2 2 0 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>

void fastSearch() {
    int n, k;
    std::vector<int> A;

    std::cin >> n;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());

    std::cin >> k;

    for (int i = 0; i < k; i++) {
        int l, r;
        std::cin >> l >> r;


        auto custom_lower_bound = [&]() {
            int low = 0; 
            int high = n; 
            while (low < high) {
                int m = (low + high) / 2;
                if (A[m] < l) {
                    low = m + 1;
                } else {
                    high = m;
                }
            }
            return low;
        };

        auto custom_upper_bound = [&]() {
            int low = 0;
            int high = n;
            while (low < high) {
                int m = (low + high) / 2;
                if (A[m] <= r) {
                    low = m + 1;
                } else {
                    high= m;
                }
            }
            return low;
        };
        int lower= custom_lower_bound();
        int upper = custom_upper_bound();
        std::cout << upper - lower << " ";
    }
    std::cout << std::endl;
}

void fastSearch2() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());

    int k;
    std::cin >> k;

    while (k--) {
        int l, r;
        std::cin >> l >> r;

        auto lower = std::lower_bound(a.begin(), a.end(), l);
        auto upper = std::upper_bound(a.begin(), a.end(), r);

        std::cout << (upper - lower) << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    fastSearch2();
}