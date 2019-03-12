// https://leetcode.com/contest/weekly-contest-127/problems/clumsy-factorial/
// O(N) solution
class Solution {
public:
  int clumsy(int N) {
    int result = 0;
    int op;
    int current = 1;
    int multiply = 1;
    int factor;
    
    for (int i = 0; i < N; ++i) {
      op = i % 4;
      factor = N - i;
      
      if (op == 0) {
        current = multiply * factor;
      } else if (op == 1) {
        current *= factor;
      } else if (op == 2) {
        current /= factor;
      } else if (op == 3) {
        result += current;
        result += factor;
        multiply = -1;
      }
    }
    
    if (op != 3)
      result += current;
    
    return result;
  }
};
