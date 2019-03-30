// https://leetcode.com/problems/valid-parentheses/solution/
// O(n) solution where n is the length of s
class Solution {
public:
  char opening_for(char parenthesis) {
    if (parenthesis == '}')
      return '{';
    else if (parenthesis == ')')
      return '(';
    else
      return '[';
  }
  
  bool isValid(string s) {
    stack<char> opening;
    bool valid = true;
    
    for (int i = 0; i < s.size() && valid; ++i) {
      if (s[i] == '{' || s[i] == '(' || s[i] == '[')
        opening.push(s[i]);
      else {
        valid = !opening.empty() && opening.top() == opening_for(s[i]);
        
        if (valid)
          opening.pop();
      }
    }
    
    return valid && opening.empty();
  }
};
