// 49. Group Anagrams 
/*
    Given an array  of strings strs, group the anagrams together.

    An Anagram is a word or phrase formed by rearranging the letters 
    of a different word or phrase, typically using all the original 
    letters exatcly once. 


    Example 1:

    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>


class ArrayHashing {
    public:
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
            // A hash map to store grouped anagrams 
            std::unordered_map<std::string, std::vector<std::string>> anagramMap;

            // Lambda to sort characters in a string 
            auto sortString = [](std::string s) {
                std::sort(s.begin(), s.end());
                return s;
            };

            // Iterate over each string in the input 
            for (const std::string& str : strs) {
                // Sort the string 
                std::string sortedStr = sortString(str);
                // Group the original string in the hash map
                anagramMap[sortedStr].push_back(str);
            }

            std::vector<std::vector<std::string>> result;
            for (const auto& entry : anagramMap) {
                result.push_back(entry.second);
            }

            return result;
        }
};

int main() {
    std::cout << "49. Grouped Anagrams Test program " << std::endl;

    std::vector<std::string> strs{"eat","tea","tan","ate","nat","bat"};

    std::cout << "Input : ";

    for (const auto& str : strs) {
        std::cout << str << " ";
    }

    std::cout << std::endl;

    std::vector<std::vector<std::string>> result;

    ArrayHashing arrHash;

    result = arrHash.groupAnagrams(strs);

    auto printResult = [&]() {
        for (const auto& group : result) {
            std::cout << "[";
            for (size_t i = 0; i < group.size(); i++) {
                std::cout << group[i];
                if ( i < group.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "] "; 
        }
    };

    std::cout << "Output : ";

    printResult();

}

