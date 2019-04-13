// https://leetcode.com/problems/pacific-atlantic-water-flow/
// O(1) solution since dimensions are constrained to be lower than 150
typedef unordered_map<int, unordered_set<int>> flow;
typedef pair<int, int> point;

class Solution {
public:
  void flow_from(point p,
                 int prev,
                 flow& result, 
                 vector<vector<int>>& matrix, 
                 int n, 
                 int m) {
    
    int x = p.first;
    int y = p.second;
      
    if (x >= 0 && x < n && y >= 0 && y < m) {
      if (result[x].count(y) == 0 && matrix[x][y] >= prev) {
        result[x].insert(y);
          
          for (int i : {-1, 1}) {
            flow_from({x + i, y}, matrix[x][y], result, matrix, n, m);
            flow_from({x, y + i}, matrix[x][y], result, matrix, n, m);
          }
      }
    }
  }
  
  vector<point> intersection(flow x, flow y) {
    vector<point> result;
    int row;
    
    for (auto it = x.begin(); it != x.end(); ++it) {
      row = it->first;
      
      for (auto col = (it->second).begin(); 
           col != (it->second).end(); 
           ++col) {
        if (y[row].count(*col) > 0)
          result.push_back({row, *col});
      }
    }
    
    return result;
  }
  
  vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = (n > 0 ? matrix[0].size() : 0);
    int prev = numeric_limits<int>::min();
    flow pacific_flow;
    flow atlantic_flow;
    
    for (int i = 0; i < m; ++i) {
      flow_from({0, i}, prev, pacific_flow, matrix, n, m);
      flow_from({n - 1, i}, prev, atlantic_flow, matrix, n, m);
    }
    
    for (int j = 0; j < n; ++j) {
      flow_from({j, 0}, prev, pacific_flow, matrix, n, m);
      flow_from({j, m - 1}, prev, atlantic_flow, matrix, n, m);
    }
    
    return intersection(pacific_flow, atlantic_flow);
  }
};
