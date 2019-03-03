// https://leetcode.com/problems/max-consecutive-ones-iii/
// O(n) solution where n is the length of A
class Solution {
public:
  int longest_ones(vector<int>& A, int K) {
    int max_length = 0;
    int current_length;
    int i = 0;
    int j = 0;
    int k;
    int used_shifts = 0;
    bool found;
    
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] == 0) {
        if (used_shifts == K) {
          found = false;
          
          while (j <= i && !found) {
            if (A[j] == 0)
              found = true;
            
            ++j;
          }
          
          --used_shifts;
        }
        
        ++used_shifts;
      }
      
      current_length = i - j + 1;
      
      if (current_length > max_length)
        max_length = current_length;
    }
    
    return max_length;
  }
};
