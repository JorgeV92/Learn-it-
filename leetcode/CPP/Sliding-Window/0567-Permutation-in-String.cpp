/*
 _______        _____ ______  _____ __   _  ______      _  _  _ _____ __   _ ______   _____  _  _  _     
 |______ |        |   |     \   |   | \  | |  ____      |  |  |   |   | \  | |     \ |     | |  |  |     
 ______| |_____ __|__ |_____/ __|__ |  \_| |_____|      |__|__| __|__ |  \_| |_____/ |_____| |__|__|     


    0567. Permutation in String     (Medium)

    Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

    In other words, return true if one or s1's permutations is the substring of s2.

    Example 1:

    Input: s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").


    Example 2:

    Input: s1 = "ab", s2 = "eidboaoo"
    Output: false
*/

#include <iostream>
#include <string>
#include <vector>

class SlidingWindow {
    public:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	1.	Data Structures:
	•	s1Count: A frequency array to count the occurrences of each character in s1.
	•	s2Count: A frequency array to count the occurrences of each character in the current window of s2.
	2.	Initialization:
	•	Initialize the frequency arrays for s1 and the first window of s2 (the first s1.length() characters of s2).
	3.	Sliding Window:
	•	Slide the window over s2 from the beginning to the end.
	•	For each new character entering the window, update s2Count by incrementing the count of the new character.
	•	For each character leaving the window, update s2Count by decrementing the count of the old character.
	4.	Comparison:
	•	At each step, compare the frequency arrays s1Count and s2Count. If they are equal, it means the current window 
    in s2 is a permutation of s1, and we return true.
	5.	Final Check:
	•	After the loop, perform a final comparison for the last window.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool checkInclusion(std::string s1, std::string s2) {
            if (s1.length() > s2.length()) return false;
            // Frequency arrays for characters in s1 and current window in s2
            std::vector<int> s1Count(26, 0), s2Count(26, 0);

            // Initialize the frequency arrays for the first window in s2
            for (int i = 0; i < s1.length(); ++i) {
                s1Count[s1[i] - 'a']++;
                s2Count[s2[i] - 'a']++;
            }
            // Sliding window over s2
            for (int i = s1.length(); i < s2.length(); ++i) {
                // Check if the current window matches the frequency array of s1
                if (s1Count == s2Count) return true;

                // Slide the window: remove the character going out of the window
                s2Count[s2[i - s1.length()] - 'a']--;
                // Add the character coming into the window
                s2Count[s2[i] - 'a']++;
            }
            // Check the last window
            return s1Count == s2Count;
        }
};


int main() {
    SlidingWindow solution;
    std::string s1 = "ab";
    std::string s2_1 = "eidbaooo";
    std::string s2_2 = "eidboaoo";

    std::cout << "Input: s1 = " << s1 << ", s2 = " << s2_1 << "\nOutput: " << solution.checkInclusion(s1, s2_1) << std::endl; // Output: true
    std::cout << "Input: s1 = " << s1 << ", s2 = " << s2_2 << "\nOutput: " << solution.checkInclusion(s1, s2_2) << std::endl; // Output: false

    return 0;
}