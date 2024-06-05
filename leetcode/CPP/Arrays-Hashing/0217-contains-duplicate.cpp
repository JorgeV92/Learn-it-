/*
    217. Contains Duplicate (Easy)

    Given an integer array nums, return true if any value appears at least twice 
    in the array, and return false if every element is distinct.


    Example 1:

    Input: nums = [1,2,3,1]
    Output: true
*/

#include <iostream>
#include <vector>
#include <set>

class ArrayHashing {
    public:

    bool containsDuplicate(std::vector<int>& arr) {
        std::set<int> arr_set(arr.begin(), arr.end());

        if (arr_set.size() == arr_set.size()) {
            return false;
        } else {
            return true;
        }
    }
        
};


int main () {

    std::vector<int> v1{1,2,3,1};

    ArrayHashing arrHash;

    bool result = arrHash.containsDuplicate(v1);
        
    for (int val : v1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Contains duplicate? " << (result ? "false" : "true") << std::endl; 

    return 0;
}
