///////////////////////////////////////////////////////////////////////////////////////////////
//                              Longest Increasing Subsequence 
//
//  original post https://www.topcoder.com/thrive/articles/longest-increasing-subsequence
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int LISMemoize(vector<int>& LISVector) {
    int n = LISVector.size();
    vector<int> mem(n);

    for (int i = 0; i < n; i++) {
        mem[i] = 1;
    }

    for (int j = 1; j < n; j++)  {
        for (int i = 0; i < j; i++) {
            if (LISVector[i] < LISVector[j]) {
                mem[j] = max(mem[j], mem[i] + 1);
            }
        }
    }
    int maxLIS = *max_element(mem.begin(), mem.end());
    return maxLIS;
}

int main() {

    vector<int> A = {15, -1, 8, 2, 5, 11, 7, 10};
    cout << LISMemoize(A);
    return 0;
}


