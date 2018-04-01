// https://leetcode.com/problems/remove-duplicate-letters
// O(n) solution (because at much we are going to pop n times from positions)

/*
Idea:
 We add a letter x to our result if it is in the string (to_use), 
 it's the minimum letter yet not used, and all the letters yet 
 not used exist at the right of x
*/
class Solution {
public:
  string removeDuplicateLetters(string s) {
    vector<stack<int>> positions(26);
    vector<vector<bool>> at_right(s.size() + 1, 
                                  vector<bool>(26, false));
    unordered_set<char> to_use;
    string result;
    char current;
    bool found;
    int last_used = -1;
    int pos;
    
    for (int i = s.size() - 1; i >= 0; --i) {
      at_right[i] = at_right[i + 1];
      at_right[i][s[i] - 'a'] = true;
      to_use.insert(s[i]);
      positions[s[i] - 'a'].push(i);
    }
    
    while (!to_use.empty()) {
      found = false;
      
      for (int i = 0; i < 26 && !found; ++i) {
        current = 'a' + i;
        
        if (to_use.count(current)) {
          while (positions[i].top() <= last_used)
            positions[i].pop();
            
          pos = positions[i].top();
          
          found = true;
          
          for (char c : to_use)
            if (!at_right[pos][c - 'a'])
              found = false;
        }
      }
      last_used = pos;
      result += current;
      to_use.erase(current);
    }
    
    return result;
  }
};
