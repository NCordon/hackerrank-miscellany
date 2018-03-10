// https://leetcode.com/problems/sqrtx
// O(log x) implementation of sqrt
class Solution {
public:
  int mySqrt(int x) {
    long left = 0;
    long right = x;
    long middle;
    long result = 0;

    while (left <= right) {
      middle = (left + right) / 2;

      if (x - middle * middle >= 0 &&
          middle * middle > result * result)
        result = middle;

      if (middle * middle < x)
        left = middle + 1;
      else
        right = middle - 1;
    }

    return result;
  }
};
