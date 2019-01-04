// https://leetcode.com/submissions/detail/198846267/
/* Let n be the length of the query string and m the length of the regexp
   If we define match(i, j) = true iff regexp[0...j[ matches query[0...i[
   Then:
     match(0, j) = true until regexp[j] != '*'
     match(i, 0) = false i > 1
     match(i, j) should be defined in terms of match[i - 1][j - 1], 
                 match[i - 1][j] and match[i][j - 1]
*/
class Solution {
public:
  bool isMatch(string query, string regexp) {
    int n = query.size();
    int m = regexp.size();
    vector<vector<bool>> match(n + 1, vector<bool>(m + 1, false));
    
    bool empty_match = true;
    match[0][0] = true;
    
    for (int j = 0; j < m; ++j) {
      if (regexp[j] != '*')
        empty_match = false;
      
      match[0][j + 1] = empty_match;
    }
    
    for (int i = 0; i < n; ++i)
      match[i + 1][0] = false;
    
    for (int j = 1; j <= m; ++j) {
      for (int i = 1; i <= n; ++i) {
        if (regexp[j - 1] == '*')
          match[i][j] = match[i - 1][j - 1] || match[i][j - 1] || match[i - 1][j];
        else if (regexp[j - 1] == '?')
          match[i][j] = match[i - 1][j - 1];
        else
          match[i][j] = match[i - 1][j - 1] && (query[i - 1] == regexp[j - 1]);
      }
    }
    
    return match[n][m];
  }
};
