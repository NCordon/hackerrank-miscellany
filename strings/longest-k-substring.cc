// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
class Solution {
  bool ValidSubstring(int k, vector<int>& count) {
    bool valid = true;
    
    for (int i = 0; i < count.size() && valid; ++i)
      if(count[i] > 0 && count[i] < k)
        valid = false;
    
    return valid;
  }
public:
  int longestSubstring(string s, int k) {
    vector<int> count(26, 0);
    int best_length = 0;
      
    for (int i = 0; i < s.size() && s.size() - i > best_length; ++i) {
      fill(count.begin(), count.end(), 0);
        
      for (int j = i; j < s.size(); ++j) {
        ++count[s[j] - 'a'];
        if (ValidSubstring(k, count) && j - i + 1 > best_length)
          best_length = j - i + 1;
      }
    }
      
    return best_length;
  }
};
