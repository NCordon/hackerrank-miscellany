// https://leetcode.com/problems/valid-number/
class Solution {
public:
  string trim(string s) {
    int start = s.find_first_not_of(' ');
    int end = s.find_last_not_of(' ');
    
    if (start != string::npos && end != string::npos)
      return s.substr(start, end - start + 1);
    else
      return "";
  }
  
  // would return -1 if not valid
  // or the int of the first charcter not
  // matching the requirement
  int leading_decimal(string s) {
    bool valid = false;
    bool with_point = false;
    int i = 0;
    
    if (i < s.size() && s[0] == '+' || s[0] == '-')
      i = 1;
    
    while (i < s.size() && ('0' <= s[i] && s[i] <= '9' || !with_point)) {
      if ('0' <= s[i] && s[i] <= '9') {
        ++i;
        valid = true;
      } else {
        with_point = true;
        
        if (s[i] == '.')
          ++i;
      }
    }

    if (valid)
      return i;
    else
      return -1;
  }
  
  bool trailing_integer(string s, int i) {
    bool valid = false;
    
    if (i < s.size() && s[i] == '+' || s[i] == '-')
      ++i;
    
    while (i < s.size() && '0' <= s[i] && s[i] <= '9') {
      ++i;
      valid = true;
    }
    
    if (i < s.size())
      valid = false;
    
    return valid;
  }
  
  bool is_number(string s) {
    s = trim(s);
    bool result = true;
    int exp_idx;
    
    exp_idx = leading_decimal(s);
    result = exp_idx > 0;

    if (result && exp_idx < s.size()) {
      result = s[exp_idx] == 'e';
        
      if (result)
        result = trailing_integer(s, exp_idx + 1);
    }
    
    return result;
  }
};
