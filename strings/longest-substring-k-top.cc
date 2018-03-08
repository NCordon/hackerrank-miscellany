// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters

class Solution {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> ocurrences;
    int distinct = 0;
    int i = 0;
    int best_length = 0;
      
    for (int j = 0; j < s.size(); ++j) {
      if (ocurrences.count(s[j]) == 0) {
        ++distinct;
        ocurrences[s[j]] = 0;
      }
        
      ++ocurrences[s[j]];
        
      while (distinct > k && i <= j) {
        --ocurrences[s[i]];
          
        if (ocurrences[s[i]] == 0) {
          --distinct;
          ocurrences.erase(s[i]);
        }
          
        ++i;
      }
        
      if (j - i + 1 > best_length)
        best_length = j - i + 1;
    }
      
    return best_length;
  }
};
