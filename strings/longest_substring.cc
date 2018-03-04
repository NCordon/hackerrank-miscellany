// https://leetcode.com/articles/longest-substring-without-repeating-characters/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> previous_chars;
        int slide = 0;
        int max_length = 0;
        int first_repeated;
        
        for (int i = 0; i < s.size(); ++i) {
            if (previous_chars.count(s[i]) == 0) {
                ++slide;
                max_length = max(slide, max_length);
            }
            else {
                first_repeated = previous_chars[s[i]];
                
                for (int j = i - slide; j < first_repeated; ++j) {
                    previous_chars.erase(s[j]);
                }
                
                slide = i - first_repeated;
            }
            
            previous_chars[s[i]] = i;
        }
        
        return max_length;        
    }
};
