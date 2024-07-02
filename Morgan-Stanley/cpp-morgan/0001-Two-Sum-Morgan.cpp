#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> twoSum(vector<int>& A, int t) {
    map<int, int> mp;
    for (int i = 0; i < A.size(); i++) {
        int complement = t - A[i];
        if (mp.find(complement) != mp.end()) {
            return {mp[complement], i};
        } 
        mp[A[i]] = i;
    }
    return {};
}