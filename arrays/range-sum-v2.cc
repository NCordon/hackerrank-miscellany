// https://leetcode.com/problems/range-sum-query-2d-mutable/
// Range sum with lazy propagation of updates

class NumMatrix {
  vector<vector<int> > matrix;
  vector<vector<int> > cum_sum;
  bool by_row;
  vector<bool> updated;
  
  void ComputeRowCumSum(int row) {
    cum_sum[row][0] = matrix[row][0];
    
    for (int i = 1; i < matrix[row].size(); ++i)
      cum_sum[row][i] = matrix[row][i] + cum_sum[row][i - 1];
  }
  
  void ComputeColCumSum(int col) {
    cum_sum[col][0] = matrix[0][col];
    
    for (int j = 1; j < matrix.size(); ++j)
      cum_sum[col][j] = matrix[j][col] + cum_sum[col][j - 1];
  }
  
public:
  NumMatrix(vector<vector<int>> matrix) {
    this->matrix = matrix;
    int rows = matrix.size();
    int cols;
      
    if (!matrix.empty()) {
      cols = matrix[0].size();
      if (rows >= cols) {
        by_row = true;
        cum_sum = vector<vector<int> > (rows, vector<int>(cols, 0));
        updated = vector<bool> (rows, true);
          
        for (int i = 0; i < rows; ++i)
          ComputeRowCumSum(i);
      } else {
        by_row = false;
        cum_sum = vector<vector<int> > (cols, vector<int>(rows, 0));
        updated = vector<bool> (cols, true);
          
        for (int j = 0; j < cols; ++j)
          ComputeColCumSum(j);
      }
    }
  }
    
  void update(int row, int col, int val) {
    matrix[row][col] = val;
      
    if (by_row)
      updated[row] = false;
    else
      updated[col] = false;
  }
    
  int sumRegion(int row1, int col1, int row2, int col2) {
    int result = 0;
      
    if (by_row) {
      for (int r = row1; r <= row2; ++r) {
        if (!updated[r]) {
          ComputeRowCumSum(r);
          updated[r] = true;
        }
          
        result += cum_sum[r][col2] - (col1 > 0 ? cum_sum[r][col1 - 1] : 0);
      }
    } else {
      for (int c = col1; c <= col2; ++c) {
        if (!updated[c]) {
          ComputeColCumSum(c);
          updated[c] = true;
        }
          
        result += cum_sum[c][row2] - (row1 > 0 ? cum_sum[c][row1 - 1] : 0);
      }
    }
      
    return result;
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
