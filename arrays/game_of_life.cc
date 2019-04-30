// https://leetcode.com/problems/game-of-life/
// O(n) algorithmically, in-place in space
class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    int num_rows = board.size();
    int num_cols;
    int live_around;
    int dead_around;
    int lives_current = 1;
    int lives_next = 2;
    
    if (num_rows > 0)
      num_cols = board[0].size();
    
    for (int i = 0; i < num_rows; ++i) {
      for (int j = 0; j < num_cols; ++j) {
        live_around = 0;
        dead_around = 0;
        
        for (int r : {-1, 0, 1}) {
          for (int c : {-1, 0, 1}) {
            if ((r != 0 || c != 0) && 
                0 <= i + r && i + r < num_rows &&
                0 <= j + c && j + c < num_cols) {
              if ((board[i + r][j + c] & lives_current) == 1)
                ++live_around;
              else 
                ++dead_around;
            }
          }
        }
        
        if ((board[i][j] & lives_current) == 1) {
          if (live_around == 2 || live_around == 3)
            board[i][j] |= lives_next;
        } else {
          if (live_around == 3)
            board[i][j] |= lives_next;
        }   
      }
    }
    
    // unmask the matrix
    for (int i = 0; i < num_rows; ++i)
      for (int j = 0; j < num_cols; ++j)
        board[i][j] >>= 1;
  }
};
