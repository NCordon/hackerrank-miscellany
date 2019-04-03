// https://leetcode.com/problems/shortest-palindrome/
// O(n) solution using KMP prefix table
class Solution {
public:
  vector<int> prefix_table(string s) {
    int n = s.size();
    vector<int> f(n);
    int t;
    
    if (n > 0)
      f[0] = 0;
    
    for (int i = 1; i < n; ++i) {
      t = f[i - 1];
      
      while (t > 0 && s[i] != s[t])
        t = f[t - 1];
      
      if (s[i] == s[t])
        ++t;
      
      f[i] = t;
    }
    
    return f;
  }
  
  string shortest_palindrome(string s) {
    string result = s;
    int n = s.size();
    
    if (!s.empty()) {
      string revs = s;
      reverse(revs.begin(), revs.end());
    
      int palindrome_length = prefix_table(s + "#" + revs).back();
      result = revs.substr(0, n - palindrome_length) + result;
    }
    
    return result;
  }
};
