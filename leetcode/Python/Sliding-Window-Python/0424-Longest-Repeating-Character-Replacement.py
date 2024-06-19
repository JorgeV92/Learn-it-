'''
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
'''

class SlidingWindow:
    def characterReplacement(self, s: str, k: int) -> int:
        char_count = [0] * 26
        start = 0
        max_length = 0
        max_char_count = 0
        
        for end in range(len(s)):
            char_count[ord(s[end]) - ord('A')] += 1
            max_char_count = max(max_char_count, char_count[ord(s[end]) - ord('A')])
            
            if (end - start + 1) - max_char_count > k:
                char_count[ord(s[start]) - ord('A')] -= 1
                start += 1
                
            max_length = max(max_length, end - start + 1)
            
        return max_length

if __name__ == "__main__":    
    sw = SlidingWindow()
    s1 = "ABAB"
    k1 = 2
    s2 = "AABABBA"
    k2 = 1

    print(f"Input: s = {s1}, k = {k1}\nOutput: {sw.characterReplacement(s1, k1)}")  # Output: 4
    print(f"Input: s = {s2}, k = {k2}\nOutput: {sw.characterReplacement(s2, k2)}")  # Output: 4