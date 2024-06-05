/*
    1299. Replace Elements with Greatest Element on Right Side (Easy)

    Given an array arr, replace every element in that array with the greatest element among the 
    elements to its right, and replace the last element with -1


*/

#include <iostream>
#include <vector>
#include <algorithm>

class ArrayHashing {
    public:
        std::vector<int> replaceElements(std::vector<int>& arr) {
            int n = arr.size();
            if (n == 0) return {};

            int max_from_right = -1;

            for (int i = n - 1; i >= 0; --i) {
                int current = arr[i];
                arr[i] = max_from_right;
                max_from_right = std::max(max_from_right, current);
            }
            return arr;
        }   
};

int main() {

    std::vector<int> result;
    ArrayHashing arrHash;
    std::vector<int> v1{17,18,5,4,6,1};

    std::cout << "Replace Elements with Greatest Element on Right Side\n";
    std::cout << "Input : ";

    for (int val : v1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    result = arrHash.replaceElements(v1);

    std::cout << "Output : ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    return 0;
}