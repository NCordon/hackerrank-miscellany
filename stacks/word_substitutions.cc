// https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/submissions/
// O(n) solution where n is the length of S
class Solution {
public:
  bool isValid(string S) {
    int i = 0;
    int size = S.size();
    bool valid = size % 3 == 0;
    stack <char> to_look;
    char current;
    
    for (int i = 0; i < size && valid; ++i) {
      if (S[i] == 'a') {
        to_look.push('c');
        to_look.push('b');
      } else if (!to_look.empty()) {
        current = to_look.top();
        to_look.pop();
        valid = (S[i] == current);
      } else {
        valid = false;
      } 
    } 
    
    return (valid && to_look.empty());
  }
};
