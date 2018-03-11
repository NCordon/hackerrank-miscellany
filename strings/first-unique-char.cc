// https://leetcode.com/problems/first-unique-character-in-a-string/

class Solution {
public:
    int firstUniqChar(string s) {
      vector<int> counts(26);
      
      for (char c : s)
        ++counts[c - 'a'];
      
      for (int i = 0; i < s.size(); i++)
        if (counts[s[i] - 'a'] == 1)
          return i;
      
      return -1;
    }
};
