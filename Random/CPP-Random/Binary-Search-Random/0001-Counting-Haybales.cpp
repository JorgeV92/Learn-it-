//////////////////////////////////////////////////////////////////////////////////////////////
// Original post https://usaco.org/index.php?page=viewproblem2&cpid=666
//
//Farmer John has just arranged his N haybales (1≤N≤100,000) at various points along the 
// one-dimensional road running across his farm. To make sure they are spaced out appropriately, 
// please help him answer Q queries (1≤Q≤100,000), 
// each asking for the number of haybales within a specific interval along the road.
// INPUT FORMAT (file haybales.in):
// The first line contains N and Q.
// The next line contains N distinct integers, each in the range 0…1,000,000,000
// indicating that there is a haybale at each of those locations.
// 
// Each of the next Q lines contains two integers A and B (0≤A≤B≤1,000,000,000 ) 
// giving a query for the number of haybales between A and B, inclusive.
// 
// OUTPUT FORMAT (file haybales.out):
// You should write Q lines of output. For each query, output the number of 
// haybales in its respective interval.
// SAMPLE INPUT:
// 4 6
// 3 2 7 5
// 2 3
// 2 4
// 2 5
// 2 7
// 4 6
// 8 10
// SAMPLE OUTPUT:
// 2
// 2
// 3
// 4
// 1
// 0
//////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> bales(n);
    for (int &i : bales) {
        cin >> i;
    }
    cout << endl;
    sort(bales.begin(), bales.end());

    auto atMost = [&](int x) {
        int l = 0, r = n;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (bales[m] <= x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return l;
    };
    
    for (int i = 0; i < q; i++) {
        int q_start, q_end;
        cin >> q_start >> q_end;
        cout << atMost(q_end) - atMost(q_start - 1) << endl;
        cout.flush();
    }
    cout << endl;
    return 0;
}