// Solution to: https://leetcode.com/problems/maximal-square/

#include <stack>

class Solution {
public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int current_width = 0;
    int max = 0;
    int last_pos;
    bool search = false;
    vector<int> col_height((!matrix.empty() ? matrix[0].size() + 1 : 1), 0 );
    stack<int> prev_heights;
    stack<int> positions;
        
    for (int i=0; i<matrix.size(); i++){
      positions = stack<int>();
      prev_heights = stack<int>();
      matrix[i].push_back(0);
            
      for(int j=0; j<matrix[i].size(); j++){
        col_height[j] = (matrix[i][j] == '1' ? (col_height[j] + 1) : 0);
        last_pos = j;
                
        while(!prev_heights.empty() and prev_heights.top() > col_height[j]){
          current_width = j - positions.top();
                    
          if(current_width >= prev_heights.top())
            if(prev_heights.top() > max)
              max = prev_heights.top();
                    
          last_pos = positions.top();
          prev_heights.pop();
          positions.pop();
        }
                
        prev_heights.push(col_height[j]);
        positions.push(last_pos);
      }
    }
    return max*max;
  }
};
