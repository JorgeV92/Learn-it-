/*
    392. is Subsequence (Easy)

    Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

    A subsequence of a string is a new string that is formed from the original string by deleting some
    (can be none) of the characters without distributing the relative positions of the remaining characters.
    (i.e., "ace" is a subsequence of "abcde" while "aec" is not).


    Example 1:

    Input: s = "abc", t = "ahbgdc"
    Output: true
*/

#include <iostream>
#include <string>


class ArrayHashing {
    public:
        bool isSubsequence(std::string s, std::string t) {
            int m = s.size();
            int n = t.size();
            int i = 0, j = 0;
            // Traverse both strings
            while (i < m && j < n) {
                // If the characters match, move to the next character in s
                if (s[i] == t[j]) {
                    i++;
                }
                // Always move to the next character in t
                j++;
            }
            return i == m;
        }
};

int main() {

    std::string s = "abc";
    std::string t = "ahbgdc";

    ArrayHashing arrHash; 
    bool result = arrHash.isSubsequence(s, t);

    std::cout << "Is Subsequence? " << (result ? "true" : "false") << std::endl;

    return 0;
}