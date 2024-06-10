/*
    0091. Decode Ways (Medium)

    A message containing letters form A-Z can be encoded into numbers using the following mapping;

        'A' -> "1"
        'B' -> "2"
            .
            .
            .
        'Z' -> "26"

    To decode an encoded message, all the digits must be grouped then mapped back into letters using 
    the reverse of the mapping above (there may be multiple ways). For exampke "11106" can be mapped into:

        - "AAJf" with grouping [1 1 10 6]
        - "KJF" with grouping [11 10 6] 

    Note that the grouping [1 11 06] is invalid because "06" cannot be mapped into 'F' sine "6" is 
    different from "06".

    Given a string s containing only digits, return the number of ways to decode it. 

    Example 1:

    Input: s = "12"
    Output: 2
    Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
*/

#include <iostream>
#include <string>
#include <vector>

class DynamicProgramming1D {
    public:
        int numDecodings(std::string s) {
            // If the string is empty or starts with '0' return 0
            if (s.empty() || s[0] == '0') return 0;

            int n = s.size();

            // number of ways to decode each substring
            std::vector<int> decodings(n+1, 0);

            // Base case
            decodings[0] = 1;   // There is one way to decode an empty string 
            decodings[1] = 1;   // There is one way to decode a string of length 1 if it's not 0

            for (int i = 2; i <= n; i++) {
                // check the last single digit
                if (s[i - 1] != '0') {
                    decodings[i] += decodings[i - 1];
                }

                // check the last two digits 
                int twoDigit = std::stoi(s.substr(i - 2, 2));
                if (twoDigit >= 10 && twoDigit <= 26) {
                    decodings[i] += decodings[i - 2];
                }
            }
            return decodings[n];
        }
};

int main() {

    std::string s = "12";
    std::string s2 = "226";
    DynamicProgramming1D dynamic; 
    std::cout << "Decoded Ways : " << dynamic.numDecodings(s2) << std::endl;

    return 0;
}