// https://leetcode.com/problems/max-increase-to-keep-city-skyline/description/
// O(rows * cols)
class Solution {
public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    vector<int> max_rows(grid.size()), max_cols(grid[0].size());
    int increase = 0;
    
    for (int i = 0; i < grid.size(); ++i)
      max_rows[i] = *max_element(grid[i].begin(), grid[i].end());
    
    for (int j = 0; j < grid[0].size(); ++j) {
      int maximum = numeric_limits<int>::min();
      
      for (int i = 0; i < grid.size(); ++i) {
        if (grid[i][j] > maximum)
          maximum = grid[i][j];
      }
      
      max_cols[j] = maximum;
    }
    
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        increase += min(max_rows[i], max_cols[j]) - grid[i][j];
      }
    }
    
    return increase;
  }
};
