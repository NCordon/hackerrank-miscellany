// https://leetcode.com/problems/longest-absolute-file-path/
// O(n) solution where n is the size of the input

class Solution {
public:
  int lengthLongestPath(string input) {
    stack<int> lengths;
    stack<int> levels;
    bool folder;
    int i = 0;
    int current_length;
    int current_level;
    int path_length;
    int max_path = 0;
    levels.push(-1);
    lengths.push(0);
    
    while (i < input.size()) {
      folder = true;
      current_length = 0;
      current_level = 0;
      
      if (input[i] == '\n')
        ++i;
      
      while (input[i] == '\t') {
        ++current_level;
        ++i;
      }   
      
      while (i < input.size() && input[i] != '\n') {
        if (input[i] == '.')
          folder = false;
        
        ++current_length;
        ++i;
      }
      
      while (levels.top() >= current_level) {
        levels.pop();
        lengths.pop();
      }
      
      if (current_level > 0)
        ++current_length;
      
      if (folder) {
        levels.push(current_level);
        lengths.push(lengths.top() + current_length);
      } else {
        path_length = current_length + lengths.top();
        
        if (path_length > max_path)
          max_path = path_length;
      }
    }
    
    return max_path;
  }
};
