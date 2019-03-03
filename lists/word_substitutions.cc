/* https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/
   O(n²) solution where n is the length of the string S

   In each iteration,
     erase as much abc substrings as we can,
   until the string becomes empty
   If we erase something, the solution is valid
*/
class Solution {
public:
  bool is_valid(string S) {
    list<char> input;
    bool valid = S.size() % 3 == 0 && !S.empty();
    
    for (char c : S)
      input.push_back(c);
    
    while (!input.empty() && valid) {
      valid = false;
      auto a = input.begin(); 
      auto b = input.begin(); 
      auto c = input.begin();
      
      while (a != input.end()) {
        if (*a == 'a') {
          b = a;
          ++b;
          c = b;
          ++c;
          
          if (b != input.end() && c != input.end() && 
              *b == 'b' && *c == 'c') {
            b = input.erase(a);
            c = input.erase(b);
            a = input.erase(c);
            valid = true;
          } else {
            ++a;
          }
        } else {
          ++a;
        }
      }
    }
    
    return valid;
  }
};
