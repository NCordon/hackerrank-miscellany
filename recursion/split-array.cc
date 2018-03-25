// https://leetcode.com/contest/weekly-contest-77/problems/split-array-with-same-average/
// O(2^n) where n is length of A. Still not good enough to pass all test cases
// Approach in the solution: O(2^{n/2})
class Solution {
public:
  bool splitArraySameAverage(vector<int>& A) {
    int sum = accumulate(A.begin(), A.end(), 0);
    int length = A.size();
    double average = sum * 1.0 / length;
    vector<list<int>> sums(length);
    sums[0].push_back({0});
    bool found = false;
    
    for (int i = 0; i < length && !found; ++i) {
      for (int k = min(i + 1, length - 1); k >= 1 && !found; --k) {        
        for (int& sum : sums[k - 1]) {
          sums[k].push_back({sum + A[i]});

          if ((sum + A[i]) / (k * 1.0) == average)
            found = true;
        }
      }
    }
    
    return found;
  }
};
