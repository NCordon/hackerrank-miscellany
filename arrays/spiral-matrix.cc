// https://leetcode.com/problems/spiral-matrix

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    int last_col;
    int num_iterations = (matrix.size() - 1) / 2;
    int last_row = matrix.size();
      
    for (int i = 0; i <= num_iterations; ++i) {
      last_col = matrix[i].size() - i - 1;
      --last_row;
        
      for (int j = i; j <= last_col; ++j)
        result.push_back(matrix[i][j]);
        
      if (last_col >= 0 && last_col >= i)
        for (int k = i + 1; k <= last_row - 1; ++k)
          result.push_back(matrix[k][last_col]);
        
      if (last_row > i)
        for (int j = last_col; j >= i; --j)
          result.push_back(matrix[last_row][j]);
        
      if (last_col > i)
        for (int k = last_row - 1; k >= i + 1; --k)
          result.push_back(matrix[k][i]);
    }
      
    return result;
  }
};
