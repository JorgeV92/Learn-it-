///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              A. Packing Rectangles
//
// There are 𝑛 rectangles of the same size: 𝑤 in width and ℎ in length. It is required to 
// find a square of the smallest size into which these rectangles can be packed. Rectangles cannot be rotated.
//
// Input
// The input contains three integers 𝑤, ℎ, 𝑛 (1 ≤ 𝑤, ℎ ,𝑛 ≤ 10^9).
//
// Output
// Output the minimum length of a side of a square, into which the given rectangles can be packed.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

bool canFit(ll s, ll w, ll h, ll n) {
    return (s / w) * (s / h) >= n;
}

void packingRectangles() {
    ll w, h, n;
    cin >> w >> h >> n;
    
    ll l = 0;
    // ll r = max(w, h) * n; // i gues this we cant simply do this 
    ll r = 1;
    while (!canFit(r, w, h, n)) r *= 2;

    while (l < r) {
        ll m = (l + r) / 2;
        if (canFit(m, w, h, n)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << endl;
}

int main () {
    packingRectangles();
    return 0;
}