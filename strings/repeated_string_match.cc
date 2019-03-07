// https://leetcode.com/problems/repeated-string-match/solution/
// O(n² + m) solution where n is the length of A and m is the length of B
// Disclaimer: really awful solution!
class Solution {
public:
  bool is_substring(string& A, string& B) {
    bool substring = false;
    
    for (int i = 0; i < (A.size() - B.size() + 1) && !substring; ++ i) {
      substring = true;

      for (int j = 0; j < B.size() && substring; ++j)
        substring = B[j] == A[i + j];
    }
  
    return substring;
  }
  
  int repeated_string_match(string A, string B) {
    int len = A.size();
    int result = -1;
    bool substring = false;
    int i = 0;
    int A_index;
    int last_addressable = B.size() - len + 1;
    
    if (len < B.size()) {
      // Check first len positions of B
      while (i < len && !substring) {
        substring = true;
        
        for (int j = 0; j < len && substring; ++j)
          if (i + j < B.size())
            substring = B[i + j] == A[j];
        
        if (!substring)
          ++i;
      }
      
      if (substring) {
        
        // Check first part of B
        for (int k = 0; k < i && substring; ++k)
          substring = B[k] == A[len - i + k];
        
        if (substring) {
          result = (i > 0 ? 1 : 0);
          
          // Check rest of B
          for (int k = 0; k < (B.size() - i) && substring; ++k) {
            A_index = k % len;
            
            if (A_index == 0)
              ++result;
            
            substring = B[i + k] == A[A_index];
          }
          
          if (!substring)
            result = -1;
        }
      }
    } else {
      if (is_substring(A, B))
        result = 1;
      else {
        string double_A = A + A;
      
        if (is_substring(double_A, B))
          result = 2;
      }
    }
    
    return result;
  } 
};
