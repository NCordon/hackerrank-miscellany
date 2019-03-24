// https://leetcode.com/problems/decode-ways/
// O(n) solution algorithmically where n is the length of s, O(1) in space
// Idea:
// Let's call N(0, n-1) = number of ways to decode s[0,..., n-1]
// Then N(0, n-1) = N(1, n-1) + N(2, n-1) if (10 <= s[0,1] <= 26)
// The recursion bottoms up in N(n-1, n-1) = 1 if s[n-1] > 0
//                             N(n-1, n-1) = 0 if s[n-1] == 0

class Solution {
public:
  int numDecodings(string s) {
    int num_decodes = (s.empty() ? 0 : 1);
    int num_next_decodes = 0;
    int n = s.size();
    int temp;
    int digit;
    
    for (int i = 0; i < n; ++i) {
      temp = num_decodes;
      num_decodes = (s[i] > '0' ? num_decodes : 0) + num_next_decodes;
      num_next_decodes = 0;
      
      if (i < (n - 1)) {
        istringstream iss (s.substr(i, 2));
        iss >> digit;
        
        if (digit >= 10 && digit <= 26)
          num_next_decodes = temp;
      }
    }
    
    return num_decodes;
  }
};
