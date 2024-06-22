///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                B. Ropes
// There are 𝑛 ropes, you need to cut 𝑘 pieces of the same length from them. 
// Find the maximum length of pieces you can get.
// 
// Input
// The first line contains two integers 𝑛 and 𝑘 (1 ≤ 𝑛, 𝑘 ≤ 10000). 
// Next 𝑛 lines contain one number each, the length of the rope 𝑎𝑖 (1 ≤ 𝑎 𝑖≤ 10^7).
// /
// Output
// Output one real number, maximum length of pieces you can get. The answer will be considered 
// correct if the relative or absolute error does not exceed 10^−6.
// 
// Example
// iunput 
//4 11
// 802
// 743
// 457
// 539
// 
// output 
// 200.5
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

bool canCut(const vector<int>& ropes, int k, double length) {
    int count = 0;
    for (int rope : ropes) {
        count += static_cast<int>(rope / length);
    }
    return count >= k;
}

double findMaxLength(vector<int>& ropes, int k) {
    double l = 0.0;
    double r = *max_element(ropes.begin(), ropes.end());
    double mid;

    while (r- l > 1e-7) {
        mid = l + (r - l) / 2;
        if (canCut(ropes, k, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return l;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> ropes(n);
    for (int i = 0; i < n; ++i) {
        cin >> ropes[i];
    }

    double result = findMaxLength(ropes, k);
    cout << fixed << setprecision(6) << result << endl;

    return 0;
}