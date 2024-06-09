/*
    0005. Longest Panlindromic Substring 

    Given a string s, return longest palindromic sbstirng in s.

    Example 1:

    Input: s = "babad"
    Output: "bab"
    Explanation: "aba" is also a valid answer.
*/

#include <iostream>
#include <string>
#include <vector>

class DynamicProgramming1D {
    public:
        // Expand Around the Center
        std::string longestPalindromeCenter(std::string s) {
            if (s.empty()) return "";
            int start = 0, end = 0;

            auto expandAroundCenter = [&](int left, int right) {
                // Expand outwards as long as the characters at the left and right indices are the same
                while (left >= 0 && right < s.size() && s[left] == s[right]) {
                    left--;         // Move left pointer to the left
                    right++;        // Move the right pointer to the right 
                }
                return right - left - 1;  // Length of the palindrome 
            };

            for (int i = 0; i < s.size(); i++) {
                // Check for odd-length palindromes with center at i
                int len1 = expandAroundCenter(i, i);       
                // Check for even-length palindromes with centers at i and i + 1
                int len2 = expandAroundCenter(i, i + 1);   
                int len = std::max(len1, len2);
                // If the found palindrome is longer than the previously found ones, update start and end 
                if (len > end - start) {
                    // i center of the current palindrome
                    // (len - 1) / 2: Calculates the distance from the center i to the start of the palindrome
                    start = i - (len - 1) /2;
                    // i center of palindrome 
                    // len / 2: Calculates the distance from the center i to the end of the palindrome.
                    end = i + len / 2;
                }
            }
            return s.substr(start, end - start + 1);
        }

        // Dynamic Programming 
        std::string longestPalindromeDP(std::string s) {
            if (s.length() <= 1) return s;

            int maxLength = 1;  
            int startIndex = 0;
            int endIndex = 0;
            std::vector<std::vector<bool>> isPalindrome(s.length(), std::vector<bool>(s.length(), false));

            for (int i = 0; i < s.length(); i++) {
                isPalindrome[i][i] = true;      // Single character palindromes 

                // Check for palindromic substrings ending at index i
                for(int j = 0; j <i; ++j) {
                    // s[j] == s[i] means the characters at index j and i are the same 
                    // (i - j <= 2) means the substring is either two characters or three characters with 
                    // middle one already a palindrome
                    // isPalindrome[j + 1][i - 1] means the substring inside the current bounds is already 
                    // a palindrome  
                    if (s[j] == s[i] && (i - j <= 2 || isPalindrome[j + 1][i - 1])) {
                        isPalindrome[j][i] = true;
                        if (i - j + 1 > maxLength) {
                            maxLength = i - j + 1;
                            startIndex = j; 
                            endIndex = i;
                        }
                    }
                }
            }
            return s.substr(startIndex, endIndex - startIndex + 1);
        }
};


int main () {
    std::string s = "babad";
    DynamicProgramming1D dynamic;
    
    std::string result = dynamic.longestPalindromeDP(s);

    std::cout << "Longest Palindromic Substring : " << result << std::endl;

    return 0;
}