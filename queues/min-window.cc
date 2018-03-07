// https://leetcode.com/problems/minimum-window-substring

class Solution {
public:
  string minWindow(string s, string t) {
    unordered_map<char, int> target;
    unordered_map<char, queue<int>> positions;
    int i = 0, j, best_i = 0, best_j = numeric_limits<int>::max();
    string result;
    
    for (char c : t) {
      if (target.count(c) == 0)
        target[c] = 0;
      
      ++target[c];
    }
    
    while(target.count(s[i]) == 0 && i < s.size())
      ++i;
    
    for (j = i; j < s.size(); ++j) {
      if (target.count(s[j]) > 0) {
        --target[s[j]];
        
        if(positions.count(s[j]) == 0)
          positions[s[j]] = queue<int>();
        
        positions[s[j]].push(j);
        
        if (target[s[j]] == 0)
          target.erase(s[j]);
        
        if (target.empty()) {
          if (j - i < best_j - best_i) {
            best_i = i;
            best_j = j;
          }
        }
      } else if (positions.count(s[j]) > 0) {
        positions[s[j]].pop();
        positions[s[j]].push(j);
        
        while (positions.count(s[i]) == 0 || positions[s[i]].front() != i)
          ++i;
        
        if (target.empty()) {
          if (j - i < best_j - best_i) {
            best_j = j;
            best_i = i;
          }
        }
      }
    }
    
    if (best_j != numeric_limits<int>::max())
      result = string(s.begin() + best_i, s.begin() + best_j + 1);
    
    return result;
    
  }
};
