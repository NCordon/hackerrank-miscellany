// https://leetcode.com/problems/k-similar-strings
// O(M!) solution algorithmically and O(M) in space,
// where M is the number of mistmatches from A and B
// It passes the tests, but I think it could be
// improved algorithmically
class Solution {
public:
  int similarity_rec(string& A, string& B, vector<int>& positions, int pos_index) {
    int result = numeric_limits<int>::max();

    if (pos_index >= positions.size())
      result = 0;
    else {
      int i = positions[pos_index];
      int j;
      int rec_value;

      if (A[i] == B[i])
        result = similarity_rec(A, B, positions, pos_index + 1);
      else {
        for (int k = pos_index + 1; k < positions.size(); ++k) {
          j = positions[k];
          
          if (A[j] == B[i]) {
            swap(A[i], A[j]);
            rec_value = similarity_rec(A, B, positions, pos_index + 1);
            result = min(result, 1 + rec_value);
            swap(A[i], A[j]);
          }
        }
      }
    }

    return result;
  }

  int kSimilarity(string A, string B) {
    vector<int> positions;

    for (int i = 0; i < A.size(); ++i)
      if (A[i] != B[i])
        positions.push_back(i);

    
    return similarity_rec(A, B, positions, 0);
  }
};
