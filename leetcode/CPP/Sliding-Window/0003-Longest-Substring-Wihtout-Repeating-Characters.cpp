/*
 _______        _____ ______  _____ __   _  ______      _  _  _ _____ __   _ ______   _____  _  _  _     
 |______ |        |   |     \   |   | \  | |  ____      |  |  |   |   | \  | |     \ |     | |  |  |     
 ______| |_____ __|__ |_____/ __|__ |  \_| |_____|      |__|__| __|__ |  \_| |_____/ |_____| |__|__|     
                                                                                                  
    Given a string s, find the length of the longest substring without repeating characters.        (Medium)

    Example 1:

    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.

    Example 2:

    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

    Example 3:

    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
    Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.    
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>



class SlidingWindow {
    public:
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	1.	Data Structures:
	•	charIndexMap: An unordered map to store the last seen index of each character.
	•	start: An integer to keep track of the start of the current window.
	•	maxLength: An integer to keep track of the maximum length of substrings without repeating characters.
	2.	Iterating Through the String:
	•	Iterate through the string with the end pointer, representing the end of the current window.
	•	For each character, check if it is in the map and if its last seen index is within the current window 
        (i.e., greater than or equal to start).
	3.	Adjusting the Start of the Window:
	•	If the character is found within the current window, move the start pointer to the right of the last seen index of that character.
	•	This ensures the window contains unique characters.
	4.	Updating the Map and Maximum Length:
	•	Update the map with the current character’s index.
	•	Calculate the length of the current window and update maxLength if this window is the longest found so far.
	5.	Output:
	•	The lengthOfLongestSubstring function returns the length of the longest substring without repeating characters 
        for the given input string. The main function demonstrates this with example inputs.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
        int lengthOfLongestSubstring(std::string s) {
            // Map to store the last index of each character seen
            std::unordered_map<char, int> charIndexMap;
            // Start of sliding window 
            int start = 0;
            // Length of the longest substring without repeating characters
            int maxLength = 0;

            // For each characeter in the string 
            for (int end = 0; end < s.length(); ++end) {
                char currentChar = s[end];

                // If the current character is found in the map and its last index is
                // greater than or equal to the start of the window 
                if (charIndexMap.find(currentChar) != charIndexMap.end() && charIndexMap[currentChar] >= start) {
                    // Move the start to one position right to avoid characters
                    start = charIndexMap[currentChar] + 1;
                }
                // Update the last index of the current character 
                charIndexMap[currentChar] = end;

                // update the maximum length of substring found 
                maxLength = std::max(maxLength, end - start + 1);
            }
            return maxLength;
        }
};

int main() {
    SlidingWindow sw;
    std::string s1 = "abcabcbb";
    std::string s2 = "bbbbb";
    std::string s3 = "pwwkew";

    std::cout << "Input: " << s1 << "\nOutput: " << sw.lengthOfLongestSubstring(s1) << std::endl; // Output: 3
    std::cout << "Input: " << s2 << "\nOutput: " << sw.lengthOfLongestSubstring(s2) << std::endl; // Output: 1
    std::cout << "Input: " << s3 << "\nOutput: " << sw.lengthOfLongestSubstring(s3) << std::endl; // Output: 3

    return 0;
}
