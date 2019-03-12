// https://leetcode.com/contest/weekly-contest-127/problems/minimum-domino-rotations-for-equal-row/
// O(N) solution where N is the length of A and B
class Solution {
public:
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    vector<bool> present(7, true);
    present[0] = false;
    vector<int> in_all;
    int result;
    int A_swaps;
    int B_swaps;
    
    for (int i = 0; i < A.size(); ++i) {
      for (int j = 1; j <= 6; ++j)
        if (A [i] != j && B[i] != j)
          present[j] = false;
    }
    
    for (int i = 1; i <= 6; ++i)
      if (present[i])
        in_all.push_back(i);
    
    if (in_all.size() == 0)
      result = -1;
    else {
      result = numeric_limits<int>::max();
      
      for (int elem : in_all) {
        A_swaps = 0;
        B_swaps = 0;
        
        for (int i = 0; i < A.size(); ++i) {
          if (A[i] != elem)
            A_swaps++;
          if (B[i] != elem)
            B_swaps++;
        }
        
        result = min(result, min(A_swaps, B_swaps));
      }
    }
    
    return result;
  }
};
