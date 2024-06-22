//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of n numbers, sorted in non-decreasing order, and k queries. 
// For each query, print the maximum index of an array element
// not greater than the given one.
//
// Input:
// The first of the input contains integers n and k (0 < n, k <= 10^5), the length of the array 
// and the number of queries. The second line contains n elements of the array, sorted in 
// non-decreasing order. The third line contains k queries. All array elemetns and queries are 
// integers, each of which does not exceed 2 * 10^9 in absolute value.
// 
// Output:
// For each of the k queries, print the maximum index of an array element not greater than the 
// given one. If there are non, print 0.
// 
// Example input:
// 5 5
// 3 3 5 8 9
// 2 4 8 1 10
// 
// Example output:
// 0
// 2
// 4
// 0
// 5
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

void readInput(int &n, int &k, std::vector<int>& A, std::vector<int>& Q) {
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
    std::vector<int> max_indices;
    for (int i = 0; i < Q.size(); i++) {
       auto it = std::upper_bound(A.begin(), A.end(), Q[i]) - A.begin();
       if (it > 0) {
            max_indices.push_back(it);
       } else {
        max_indices.push_back(0);
       }
    }
    for (const int& index : max_indices) {
        std::cout << index << std::endl;
    }
}

void binary_search(std::vector<int>& A, std::vector<int>& Q) {
    std::vector<int> max_indices;
    for(int i = 0; i < Q.size(); i++) {
        int l = 0, r = A.size() - 1;
        bool found = false;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (A[m] == Q[i]) {
                max_indices.push_back(m + 1);
                found = true;
                break;
            } else if (A[m] < Q[i]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (!found) max_indices.push_back(r + 1);
    }
    for (const int& index : max_indices) {
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