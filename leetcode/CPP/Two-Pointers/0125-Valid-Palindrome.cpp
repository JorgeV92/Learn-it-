/*
    125. Valid Palindrome 

    A phrase is a palindrome if, after converting all uppercaase letters into lowercase letters and 
    removing all non-alphanumeric characters, it reads the same forward and backwrd. Alphanumeric 
    characters include letters and numbers.

    Given a string s, return true if it is a palindrome, or false otherwise.

    Example 1:

    Input: s = "A man, a plan, a canal: Panama"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.
*/

#include <iostream>
#include <string>
#include <cctype>

class TwoPointers {
    public:
        bool isPalindrome(std::string s) {
            // Normalize the string 
            std::string normalized = "";
            for (char c : s) {
                if (std::isalnum(c)) {
                    normalized += std::tolower(c);
                }
            }

            // Check if the normalized string is a palindrome
            int left = 0;
            int right = normalized.size() - 1;

            while (left < right) {
                if (normalized[left] != normalized[right]) {
                    return false;
                }
                left++;
                right--;

            }
            return true;
        }
};

int main() {
    std::string s = "A man, a plan, a canal: Panama";
    TwoPointers tp; 

    bool result = tp.isPalindrome(s);
    std::cout << "Check valid Palindrome? " << (result ? "true" : "false") << std::endl;

    return 0;
}


