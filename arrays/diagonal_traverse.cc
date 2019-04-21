// https://leetcode.com/problems/diagonal-traverse/
typedef pair<int, int> Position;
typedef pair<int, int> Direction;

class Solution {
public:
  vector<int> find_diagonal_order(vector<vector<int>>& matrix) {
    Position position = {0, 0};
    Direction next = {0, 1};
    Direction advance = {-1, 1};
    int n = matrix.size();
    int m = 0;
    int x, y;
    int increment;
    vector<int> result;
    
    if (n > 0) {
      m = matrix[0].size();

      // Iterate all the diagonals
      for (int i = 0; i < (n + m - 1); ++i) {
        x = position.first;
        y = position.second;

        // Adjust current position to be in the matrix
        if (x >= n) {
          increment = (x - n + 1);
          x += increment * advance.first;
          y += increment * advance.second;
        }
        
        if (y >= m) {
          increment = (y - m + 1);
          x += increment * advance.first;
          y += increment * advance.second;
        }        
        
        while (0 <= x && x < n && 0 <= y && y < m) {
          result.push_back(matrix[x][y]);
          x += advance.first;
          y += advance.second;
        }

        position = {position.second + next.first, 
                    position.first + next.second};
        next = {next.second, next.first};
        advance = {advance.second, advance.first};
      }
    }
    
    return result;
  }
};
