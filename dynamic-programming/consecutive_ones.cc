/* https://leetcode.com/problems/max-consecutive-ones-iii/
   O(n) solution where n is the length of A
   Dynamic programming approach

   N(i, l) = max length of vector we can take starting at i and doing l shifts
             (l <= k, 0 <= i <= A.size() - 1)

   N(i, l) = if (A[i] == 1) 
                N(i + 1, l) + 1
             else
                0 if l == 0
                else N(i + 1, l - 1) + 1  
*/
class Solution {
public:
  int longest_ones(vector<int>& A, int K) {
    int current = A.size() - 1;
    vector<vector<int>> max_length(A.size() + 1, vector<int>(K + 1, 0));
    int result = 0;
    
    while (current >= 0) {
      if (A[current] == 1) {
        for (int i = 0; i <= K; ++i)
          max_length[current][i] = max_length[current + 1][i] + 1;
      } else {
        max_length[current][0] = 0;
        
        for (int i = 1; i <= K; ++i)
          max_length[current][i] = max_length[current + 1][i - 1] + 1;
      }
      
      --current;
    }
    
    for (int i = 0; i < A.size(); ++i) {
      if (max_length[i][K] > result)
        result = max_length[i][K];
    }
    
    return result;
  }
};
