// https://leetcode.com/problems/valid-palindrome/
class Solution {
public:
  bool is_palindrome(string s) {
    int i = 0; 
    int j = s.size() - 1;
    bool is_palindrome = true;
    
    while (i < j && is_palindrome) {
      if (!isalpha(s[i]) && !isdigit(s[i]))
        ++i;
      else if (!isalpha(s[j]) && !isdigit(s[j]))
        --j;
      else {
        is_palindrome = tolower(s[i]) == tolower(s[j]);
        ++i; 
        --j;
      }
    }
    
    return is_palindrome;
  }
};
