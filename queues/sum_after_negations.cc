// https://leetcode.com/contest/weekly-contest-127/problems/maximize-sum-of-array-after-k-negations/
// O(K*log(n)) solution
// This is in the queue section because make_heap, push_heap
// and pop_heap are used in priority queues implementation
bool greater_than(const int& a, const int& b) {
  return a > b;
}

class Solution {
public:
  int largestSumAfterKNegations(vector<int>& A, int K) {
    make_heap(A.begin(), A.end(), greater_than);
    int current;
    int result = 0;
    
    for (int i = 0; i < K; ++i) {
      current = A.front();
      pop_heap(A.begin(), A.end(), greater_than);
      A.pop_back();
      A.push_back(-current);
      push_heap(A.begin(), A.end(), greater_than);
    }
    
    for (int i = 0; i < A.size(); ++i) {
      result += A[i];
    }
    
    return result;
  }
};
