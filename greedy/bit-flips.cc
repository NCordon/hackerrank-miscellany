// https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/
// Let's call N(A[0,...n]) = minimum number of bit flips to turn A[0,...n]
// into [1, 1, 1, ...].
// - If A has length k, then if all the elemnts of A are 0
//   return 1 flip, if all are ones, return 0 flips, else -1.
// - If A's size is greater than k, then:
//   * If A starts by 1, solution is N(A[1,...n])
//   * If A starts by 0, flip k first bits of A, let's call it B,
//     and solution is 1 + N(B[1,...n])
class Solution {
public:
  int recFlipCount(vector<int>& A, int K, int index) {
    int result;
    
    if (A.size() - index == K) {
      bool any_zero = false;
      bool any_one = false;
      
      for (int i = index; i < A.size(); ++i) {
        if (A[i] == 0)
          any_zero = true;
        if (A[i] == 1)
          any_one = true;
      }
      
      // All zeroes
      if (any_zero && !any_one)
        result = 1;
      // All ones
      else if (any_one && !any_zero)
        result = 0;
      else
        result = -1;
    } else {
      if (A[index] == 0) {
        for (int i = 0; i < K; ++i)
          A[index + i] = (A[index + i] == 0 ? 1 : 0);
        
        int count = recFlipCount(A, K, index + 1);
        
        if (count == -1)
          result = count;
        else
          result = 1 + count;
      } else {
        result = recFlipCount(A, K, index + 1);
      }
    }
    
    return result;
  }
  
  int minKBitFlips(vector<int>& A, int K) {
    return recFlipCount(A, K, 0);    
  }
};
