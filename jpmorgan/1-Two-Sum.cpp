/*
    1. Two Sum

    Given an array of integers nums and an integer target, return indices of the two numbers such that 
    they add up to target.

    Example 1:

    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
*/
#include <iostream>
#include <vector>
#include <map>

class ArrayHash {
    public:
        std::vector<int> twoSum(std::vector<int>& arr, int target) {
            std::map<int, int> mp;
            for (int i = 0; i < arr.size(); i++) {
                int complement = target - arr[i];
                if (mp.count(complement)) {
                    return {mp[complement], i};
                }
                mp[arr[i]] = i;
            }
            return {};
        }
};

int main() {

    ArrayHash ah;
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    std::vector<int> result = ah.twoSum(nums, target);

    std::cout << "Output : [" << result[0] << ", " << result[1] << "]" << std::endl;

    return 0;
}