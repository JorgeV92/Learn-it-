/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 0001. Two Sum
// 
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// 
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// 
// You can return the answer in any order.
// 
// Example 1:
// 
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
// 
// Example 2:
// 
// Input: nums = [3,2,4], target = 6
// Output: [1,2]
// Example 3:
// 
// Input: nums = [3,3], target = 6
// Output: [0,1]
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Array_Hash {
    public:
        vector<int> twoSum(vector<int>& A, int t) {
            unordered_map<int, int> mp; 
            for (int i = 0; i < A.size(); i++) {
                int complement = t - A[i];
                if (mp.find(complement) != mp.end()) {
                    return {mp[complement], i};
                }
                mp[A[i]] = i;
            }
            return {};
        }
};


void printResult(const vector<int>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Array_Hash solution;
    
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = solution.twoSum(nums1, target1);
    printResult(result1); // Output: [0, 1]
    
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = solution.twoSum(nums2, target2);
    printResult(result2); // Output: [1, 2]
    
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = solution.twoSum(nums3, target3);
    printResult(result3); // Output: [0, 1]

    return 0;
}