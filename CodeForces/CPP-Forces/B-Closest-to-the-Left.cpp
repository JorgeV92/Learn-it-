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
    // For manual test only
    // std::vector<int> A = {3, 3, 5, 8, 9};
    // std::vector<int> Q = {2, 4, 8, 1, 10};

    int n, k;
    std::vector<int> A, Q;
    readInput(n, k, A, Q);
    std::cout << std::endl;
    binary_search(A, Q);
    return 0;
}