// https://leetcode.com/contest/weekly-contest-118/submissions/detail/199326992/
// O(n²) solution
class Solution {
public:
  void flipVector(vector<int>& A, int k) {
    int i = 0;
    int j = k - 1;
    int aux;
    
    while (i < j) {
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
      
      ++i;
      --j;
    }
  }
  
  
  vector<int> pancakeSort(vector<int>& A) {
    int len = A.size();
    vector<int> result;
    int flip;
    bool found;
    
    for (int i = 1; i <= len; ++i) {
      found = false;
  
      for (int j = 0; j < len && !found; ++j) {
        if (A[j] == i) {
          found = true;
          flip = j + 1;
        }
      }

      if (i > 1) {
        result.push_back(flip - 1);
        flipVector(A, flip - 1);
      }
      
      result.push_back(flip);
      flipVector(A, flip);
    }
    
    result.push_back(len);
    
    return result;
  }
};
