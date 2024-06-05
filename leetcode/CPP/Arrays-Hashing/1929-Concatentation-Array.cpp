/*
    1929. Concatenation of Array (Easy)

    Given arn integer array nums of length n, you want to create an array ans of length 2n where
    ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed)

     Example 1:

    Input: nums = [1,2,1]
    Output: [1,2,1,1,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
    - ans = [1,2,1,1,2,1]
*/

#include <iostream>
#include <vector>

class ArrayHashing {
    public:
        std::vector<int> getConcatenation(std::vector<int>& arr) {
            int n = arr.size();
            std::vector<int> ans(2*n);

            for (int i = 0; i < n; i++) {
                // set the element in ans at postion i to be the same as nums[i]
                ans[i] = arr[i];
                // Set the element in ans at position i + n to be the same as nums[i]
                ans[i + n] = arr[i]; 
            }
            return ans;
        }
};

int main() {

    std::vector<int> v1 {1, 3, 2, 1};
    ArrayHashing arrHash; 

    std::vector<int> result = arrHash.getConcatenation(v1); 

    std::cout << "Concatenation of Array test : ";

    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}