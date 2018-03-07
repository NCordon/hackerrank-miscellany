// https://leetcode.com/problems/longest-palindromic-substring/description/

/* 
   Idea: If we keep a matrix is_palindrome[i,j] indicating if s[i...(i+j)] is
   palindrome, then is_palindrome[i-1,j] = (s[i-1] == s[j] && is_palindrome[i,j-1])

   We can make a refinement to use a vector (O(n) in space) instead of a matrix (O(n²))
*/
class Solution {
public:
  string longestPalindrome(string s) {
    vector<bool> is_palindromic(s.size());
    vector<bool> prev_palindromic(s.size());
    int max_length = 0;
    string solution;
    pair<int, int> sol_indexes = {0, 1};
        
        
    for (int i = s.size() - 1; i >= 0; --i) {
      is_palindromic[0] = true;
            
      for (int j = 1; j < s.size() - i; ++j) {
        is_palindromic[j] = (s[i] == s[i + j]) && prev_palindromic[max(j - 2, 0)];
                
        if (is_palindromic[j] && j > max_length) {
          sol_indexes = {i, i + j + 1};
          max_length = j;
        }
      }
            
      prev_palindromic = is_palindromic;
    }
        
    if (!s.empty())
      solution = string(s.begin() + sol_indexes.first, s.begin() + sol_indexes.second);
        
    return solution;
  }
};
