/*
    0647. Palindromic Substrings 

    Given a string s, return the number of palindromic substrings in it. 

    A string is a palindrome when it reads the same backwards as forward.

    A substring is a contiguous sequence of characters within the string. 

    Example 1:

    Input: s = "abc"
    Output: 3
    Explanation: Three palindromic strings: "a", "b", "c".
*/

#include <iostream>
#include <vector>
#include <string>

class DynamicProgramming1D {
    public:
        int countSubstrings(std::string s) {
            int count = 0;

            // Lambda function to expand around the center and count palindromes
            auto expandAroundCenter = [&](int left, int right) {
                while (left >= 0 && right < s.size() && s[left] == s[right]) {
                    // Found a palindrome substring 
                    count++;
                    // expand further 
                    left--;
                    right++;
                }
            };

            // Loop through each character and its gap with the next character 
            for (int i = 0; i < s.size(); i++) {
                // Odd length palindromes (single center)
                expandAroundCenter(i, i);
                // Even length palindromes (center is between i and i+1)
                expandAroundCenter(i, i+1);
            }
            return count;
        }

        int countSubstringsDP(std::string s) {
            int n = s.length();
            std::vector<std::vector<bool>> palindrome(n, std::vector<bool>(n, false));

            int count = 0;

            for (int len = 1; len <= n; len++) {
                for (int i = 0; i < n - len + 1; i++) {
                    if (s[i] == s[i + len - 1] && (len <= 2 || palindrome[i + 1][i + len - 2])) {
                        palindrome[i][i + len - 1] = true;
                        count++;
                    }
                }
            }
            return count;
        }
};

int main() {
    std::string s = "abc";
    std::string t = "aaa";
    DynamicProgramming1D dynamic;
    int result = dynamic.countSubstringsDP(s);
    int result2 = dynamic.countSubstringsDP(t);
    std::cout << "Palindrome substrings Test 1: " << result << std::endl;
    std::cout << "Test 2 : " << result2 << std::endl;

    return 0;
}