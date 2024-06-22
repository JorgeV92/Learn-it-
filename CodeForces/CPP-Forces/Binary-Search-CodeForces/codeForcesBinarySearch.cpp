#include <iostream>
#include <string>
#include <vector>

void readInformation(int& n, int& k, std::vector<int>& a, std::vector<int>& q) {
    std::cin >> n >> k;
    a.resize(n);
    q.resize(k);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < k; ++i) {
        std::cin >> q[i];
    }
}

std::vector<std::string> binary_search(std::vector<int>& A,
                                       std::vector<int>& Q) {
    std::vector<std::string> result;

    for (int i = 0; i < Q.size(); i++) {  // for each query
        int l = 0, r = A.size() - 1;      // calcualte middle index
        bool found = false;               // flag to check if number is found
        while (l <= r) {
            int m = l + (r - l) / 2;  // middle index
            if (A[m] == Q[i]) {       // is the query the middle value
                result.push_back("YES");
                found = true;
                break;
            } else if (A[m] < Q[i]) {  // ignore left half
                l = m + 1;
            } else {  // ignore right half
                r = m - 1;
            }
        }
        if (!found) result.push_back("NO");
    }
    return result;
}

int main() {
    ////////////////////////////////////////////////////////
    // Sample Input:
    //
    // 10 10
    // 1 61 126 217 2876 6127 39162 98126 712687 1000000000
    // 100 6127 1 61 200 -10000 1 217 10000 1000000000
    ///////////////////////////////////////////////////////////

    int n, k;
    std::vector<int> A, Q;

    // Read input data
    readInformation(n, k, A, Q);

    // Process queries and output results
    std::vector<std::string> result = binary_search(A, Q);
    std::cout << std::endl;
    for (const std::string& s : result) {
        std::cout << s << std::endl;
    }

    return 0;
}