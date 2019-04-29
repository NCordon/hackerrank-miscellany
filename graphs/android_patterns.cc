// https://leetcode.com/problems/android-unlock-patterns/
class Solution {
public:
  bool valid(int x, int y, vector<bool>& visited) {
    bool is_valid = true;

    // x must be lower or equal than y
    if (x > y) {
      is_valid = valid(y, x, visited);
    } else {    
      if (((x == 1 || x == 4 || x == 7) && y - x == 2) ||
          ((x == 1 || x == 2 || x == 3) && y - x == 6))
        is_valid = visited[(x + y)/2];
      else if ((x == 1 && y == 9) || (x == 3 && y == 7))
        is_valid = visited[5];
    }

    return is_valid;    
  }

  int compute_solutions(vector<bool>& visited, int last, int length, int m, int n) {
    int result = 0;
    visited[last] = true;
    
    if (length >= m && length <= n)
        result = 1;

    if (length < n) {
      for (int i = 1; i <= 9; ++i)
        if (!visited[i] && valid(last, i, visited))
          result += compute_solutions(visited, i, length + 1, m, n);
    }

    visited[last] = false;
    return result;
  }

  int numberOfPatterns(int m, int n) {
    vector<bool> visited(10, false);
    int result = 0;

    for (int i = 1; i <= 9; ++i)
      result += compute_solutions(visited, i, 1, m, n);

    return result;
  }
};
