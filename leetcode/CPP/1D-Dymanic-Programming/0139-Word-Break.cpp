/*
    0139. Word Break    (Medium) 

    Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a
    space-separated sequence of one or more dictionary words. 

    Example 1:

    Input: s = "leetcode", wordDict = ["leet","code"]
    Output: true
    Explanation: Return true because "leetcode" can be segmented as "leet code".
    Example 2:

    Input: s = "applepenapple", wordDict = ["apple","pen"]
    Output: true
    Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
    Note that you are allowed to reuse a dictionary word.
    Example 3:

    Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    Output: false
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class DynamicProgramming1D {
    public: 
        bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
            // quick lookup of dictionary words
            std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());

            std::vector<bool> canSegment(s.size() + 1, false);
            
            // Base case: an empty string can be segmented
            canSegment[0] = true;

            // for all substring of s 
            for (size_t i = 1; i <= s.size(); i++) {
                // check all possible ending positions of the current substring 
                for (size_t j = 0; j < i; ++j) {
                    // if the substring [j:i] is in the wordSet and canSegment[j] is true 
                    if (canSegment[j] && wordSet.find(s.substr(j, i - j)) != wordSet.end()) {
                        canSegment[i] = true;
                        break;
                    }
                }
            }
            // Return whether the entire string can ne segmented 
            return canSegment[s.size()];
        }
};

int main () {

    DynamicProgramming1D dynamic;

    std::string s = "Alan Turing"; 
    std::vector<std::string> wordDict = {"Alan", " Turing"};
    std::cout << "Can \" " << s << "\" be segmented? " << (dynamic.wordBreak(s, wordDict) ? "true" : "false") << std::endl;

    std::string s1 = "leetcode";
    std::vector<std::string> wordDict1 = {"leet", "code"};
    std::cout << "Can \"" << s1 << "\" be segmented? " << (dynamic.wordBreak(s1, wordDict1) ? "true" : "false") << std::endl;
    // Output: true (Explanation: "leetcode" can be segmented as "leet code")
    
    std::string s2 = "applepenapple";
    std::vector<std::string> wordDict2 = {"apple", "pen"};
    std::cout << "Can \"" << s2 << "\" be segmented? " << (dynamic.wordBreak(s2, wordDict2) ? "true" : "false") << std::endl;
    // Output: true (Explanation: "applepenapple" can be segmented as "apple pen apple")
    
    std::string s3 = "catsandog";
    std::vector<std::string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};
    std::cout << "Can \"" << s3 << "\" be segmented? " << (dynamic.wordBreak(s3, wordDict3) ? "true" : "false") << std::endl;
    // Output: false (Explanation: "catsandog" cannot be segmented into dictionary words)

    return 0;
}