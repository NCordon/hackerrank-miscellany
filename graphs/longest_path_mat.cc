// https://leetcode.com/problems/longest-increasing-path-in-a-matrix
// Based on topological sort
// O(n) where n is the size of the matrix, since we build a graph with the matrix
// where there is an edge i->j iff I can move from matrix[i] < matrix[j].
// Since topological sort is O(|E| + |V|) where E is the number of edges of the graph,
// and here it is a multiple of n, our algorithm runs in O(n)
typedef vector<vector<int>> Matrix;
typedef pair<int, int> Tuple;

struct pair_hash {
  int operator()(pair<int,int> const& pair) const {
    return pair.first ^ pair.second;
  }
};

typedef unordered_set<Tuple, pair_hash> HashSet;

class Solution {
public:
  void visit(int x, int y, int n, int m, Matrix& matrix,
             Matrix& max_length, HashSet& unvisited) {
    if (unvisited.count({x, y})) {
      unvisited.erase({x, y});
      vector<Tuple> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
      int u, v;
      
      for (Tuple dir : directions) {
        u = x + dir.first;
        v = y + dir.second;
        
        if (0 <= u && u < n && 0 <= v && v < m && matrix[x][y] < matrix[u][v]) {
          visit(u, v, n, m, matrix, max_length, unvisited);
          max_length[x][y] = max(max_length[x][y], 1 + max_length[u][v]);
        }
      }
    }
  }
  
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m;
    int result = 0;
    
    if (n > 0)
      m = matrix[0].size();
    
    Matrix max_length(n, vector<int>(m, 1));
    HashSet unvisited;
    
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        unvisited.insert({i, j});
    
    while (!unvisited.empty()) {
      Tuple current = *(unvisited.begin());
      visit(current.first, current.second, n, m, matrix, max_length, unvisited);
    }
    
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (max_length[i][j] > result)
          result = max_length[i][j];
    
    return result;
  }     
};
