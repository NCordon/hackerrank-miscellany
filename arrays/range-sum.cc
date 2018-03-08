// https://leetcode.com/problems/range-sum-query-2d-mutable

class NumMatrix {
  vector<vector<int> > matrix;
  vector<vector<int> > cum_sum;
  
  void ComputeCumSum(int row) {
    cum_sum[row][0] = matrix[row][0];
    
    for (int i = 1; i < matrix[row].size(); ++i)
      cum_sum[row][i] = matrix[row][i] + cum_sum[row][i - 1];
  }
  
public:
  NumMatrix(vector<vector<int>> matrix) {
    this->matrix = matrix;
    cum_sum = matrix;
      
    for (int i = 0; i < matrix.size(); ++i)
      ComputeCumSum(i);
  }
    
  void update(int row, int col, int val) {
    matrix[row][col] = val;
    ComputeCumSum(row);
  }
    
  int sumRegion(int row1, int col1, int row2, int col2) {
    int result = 0;
      
    for (int r = row1; r <= row2; ++r)
      result += cum_sum[r][col2] - (col1 > 0 ? cum_sum[r][col1 - 1] : 0);
      
    return result;
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
