// https://leetcode.com/problems/minimum-path-sum/

class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
      
    vector<int> current(cols, 0);
    vector<int> prev(cols, numeric_limits<int>::max());
    prev[cols - 1] = 0;
      
    for (int i = rows - 1; i >= 0; --i) {
      current[cols - 1] = grid[i][cols - 1] + prev[cols - 1];
        
      for (int j = cols - 2; j >= 0; --j)
        current[j] = grid[i][j] + min(prev[j], current[j + 1]);
        
        
      prev = current;
    }
      
    return current[0];
  }
};
