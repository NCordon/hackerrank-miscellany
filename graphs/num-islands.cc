// https://leetcode.com/problems/number-of-islands/description/
class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    int num_islands = 0;
    int n = (grid.empty() ? 0 : grid[0].size());
    vector<list<int>> adjacency(grid.size() * n);
    vector<bool> visited(grid.size() * n, false);
    int current;
        
    // Code board as a graph, where to vertexes are
    // joined by and edge iff they are both ones and
    // are adjacent positions in the board
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < n; ++j) {
        if(grid[i][j] == '1') {
          if (i > 0) {
            if (grid[i - 1][j] == '1') {
              adjacency[(i - 1) * n + j].push_back(i * n + j);
              adjacency[i * n + j].push_back((i - 1) * n + j);
            }
          }
                    
          if (j > 0) {
            if (grid[i][j - 1] == '1') {
              adjacency[i * n + j - 1].push_back(i * n + j);
              adjacency[i * n + j].push_back(i * n + j - 1);
            }
          }
        } else {
          visited[i * n + j] = true;
        }
      }
    }
        
    // Number of islands is the number of connected 
    // components in the graph
    for (int i = 0; i < visited.size(); ++i) {
      if(!visited[i]) {                
        stack<int> to_explore;
        to_explore.push(i);
                
        while(!to_explore.empty()) {
          current = to_explore.top();
          visited[current] = true;
          to_explore.pop();
                    
          for (int neighbor : adjacency[current]) {
            if(!visited[neighbor])
              to_explore.push(neighbor);
          }
        }
                
        num_islands++;
      }
    }
        
    return num_islands;      
  }
};
