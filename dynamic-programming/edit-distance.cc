// https://leetcode.com/problems/edit-distance

class Solution {
public:
  int minDistance(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();
    vector<int> sol(m + 1);
    vector<int> prev(m + 1);
    iota(sol.begin(), sol.end(), 0);
      
    for (int i = 1; i <= n; ++i) {
      prev = sol;
      sol[0] = i;
        
      for (int j = 1; j <= m; ++j) {
        if (word1[i - 1] == word2[j - 1])
          sol[j] = prev[j - 1];
        else
          sol[j] = min(prev[j], min(prev[j - 1], sol[j - 1])) + 1;
      }
    }
      
    return sol[m];
  }
};
