/*
 _______        _____ ______  _____ __   _  ______      _  _  _ _____ __   _ ______   _____  _  _  _     
 |______ |        |   |     \   |   | \  | |  ____      |  |  |   |   | \  | |     \ |     | |  |  |     
 ______| |_____ __|__ |_____/ __|__ |  \_| |_____|      |__|__| __|__ |  \_| |_____/ |_____| |__|__|     


    0424. Longest Repeating Character Replacement (Medium)

    You are given a string s and an integer k. You can choose any character of the string and change it 
    to any other uppercase English character. You can perform this operation at most k times.

    Return the length of the longest substring conatining the same letter you can get after performing 
    the above opeartions. 

    Example 1:

    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.

    Example 2:

    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.
    There may exists other ways to achieve this answer too.
*/

#include <iostream>
#include <string>
#include <algorithm>

class SlidingWindow {
    public:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
        1.	Data Structures:
        •	charCount: An array to count the frequency of each character in the current window.
        •	start: An integer to keep track of the start of the current window.
        •	maxLength: An integer to keep track of the maximum length of the substring found.
        •	maxCharCount: An integer to keep track of the maximum frequency of a single character in the current window.
        2.	Iterating Through the String:
        •	Iterate through the string with the end pointer, representing the end of the current window.
        •	Update the frequency of the current character in charCount.
        •	Update maxCharCount to the highest frequency of any single character in the current window.
        3.	Adjusting the Start of the Window:
        •	If the number of characters that need to be replaced ((end - start + 1) - maxCharCount) exceeds k, 
        shrink the window from the left by moving the start pointer to the right and decrementing the count of the character at the start pointer.
        4.	Updating the Maximum Length:
        •	Update maxLength to the maximum value between the current maxLength and the length of the current window (end - start + 1).
        5.	Output:
        •	The characterReplacement function returns the length of the longest substring containing the same letter after performing at 
        most k replacements.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int characterReplacement(std::string s, int k) {
            // Array to count frequency of each character in the current window
            int charCount[26] = {0};
            int start = 0;
            int maxLength = 0;
            int maxCharCount = 0;

            for (int end = 0; end < s.length(); end++) {
                // Update the frequency of the current character
                charCount[s[end] - 'A']++;
                maxCharCount = std::max(maxCharCount, charCount[s[end] - 'A']);

                // if the number of characters to replace exceeds k, shrink the window from the left
                if ((end - start + 1) - maxCharCount > k) {
                    charCount[s[start] - 'A']--;
                    start++;
                }
                // select the max from the current max or the size of the window
                maxLength = std::max(maxLength, end - start + 1);
            }
            return maxLength;
        }
};

int main() {
    SlidingWindow solution;
    std::string s1 = "ABAB";
    int k1 = 2;
    std::string s2 = "AABABBA";
    int k2 = 1;

    std::cout << "Input: s = " << s1 << ", k = " << k1 << "\nOutput: " << solution.characterReplacement(s1, k1) << std::endl; // Output: 4
    std::cout << "Input: s = " << s2 << ", k = " << k2 << "\nOutput: " << solution.characterReplacement(s2, k2) << std::endl; // Output: 4

    return 0;
}