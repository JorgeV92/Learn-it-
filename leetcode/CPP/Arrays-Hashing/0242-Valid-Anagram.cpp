/*
    242. Valid Anagram (Easy)

    Given two strings s and t, return true if t is an anagram of s, and false otherwise.

    An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
    typically using all the original letters exactly once. 

    Example 1:

    Input: s = "anagram", t = "nagaram"
    Output: true
*/
#include <iostream>
#include <string>
#include <map>

class ArrayHashing {
    public:
        bool isAnagram(std::string s, std::string t) {
            std::map<char, int> mapsS, mapsT;

            // count the characters in both strings
            for (int i = 0; i <s.length(); i++) {
                mapsS[s[i]]++;
                mapsT[t[i]]++;
            } 

            // compare the cahracter counts
            for (auto& pair : mapsS) {
                char c = pair.first;
                int count = pair.second;

                if (mapsT[c] != count) {
                    return false;
                }
            }
            return true; 
        }
};


int main() {

    std::string s = "anagram", t = "nagaram";

    ArrayHashing arrHash;

    bool result = arrHash.isAnagram(s, t);

    std::cout << "Test Valid Anangram : " << (result ? "true" : "false") << std::endl; 

    return 0;
}