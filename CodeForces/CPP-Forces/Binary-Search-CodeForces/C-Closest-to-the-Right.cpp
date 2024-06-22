//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of 𝑛 numbers, sorted in non-decreasing order, and 𝑘 queries. 
// For each query, print the minimum index of an array element not less than the given one.
// 
// Input
// The first line of the input contains integers 𝑛 and 𝑘 (0 < 𝑛, 𝑘 ≤ 10^5 ), the length of the a
// rray and the number of queries. The second line contains 𝑛
//  elements of the array, sorted in non-decreasing order. The third line contains 𝑘 
// queries. All array elements and queries are integers, each of which does not exceed 2⋅10^9 in absolute value.
// 
// Output
// For each of the 𝑘 queries, print the minimum index of an array element not less than the given one. 
// If there are none, print 𝑛+1.
// 
// Example input:
// 5 5
// 3 3 5 8 9
// 2 4 8 1 10
// 
// Example output:
// 1
// 3
// 4
// 1
// 6
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

void readInput(int& n, int& k, std::vector<int>& A, std::vector<int>& Q) {
    std::cin >> n >> k;
    A.resize(n);
    Q.resize(k);

    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    for (int j = 0; j < k; j++) {
        std::cin >> Q[j];
    }
}

void binary_search_bisect(std::vector<int>& A, std::vector<int>& Q) {
    std::vector<int> min_indices;
    for (int i = 0; i < Q.size(); i++) {
        auto index = std::lower_bound(A.begin(), A.end(), Q[i]) - A.begin();
        if (index < A.size()) {
            min_indices.push_back(index + 1);
        } else {
            min_indices.push_back(A.size() + 1);
        }
    }
    for (const int& index : min_indices) {
        std::cout << index << std::endl;
    }
}

int main() {

    int n, k;
    std::vector<int> A, Q;
    readInput(n, k, A, Q);
    std::cout << std::endl;
    binary_search_bisect(A, Q);
    return 0;
}