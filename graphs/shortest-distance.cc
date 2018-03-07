// https://leetcode.com/problems/shortest-distance-from-all-buildings/description/
typedef pair<int,int> coord;

class Solution {
private:
  void VisitSurroundings(pair<coord, int> c, vector<vector<int> >& grid,
                         vector<vector<bool> >& visited,
                         vector<vector<int> >& times_visited,                           
                         queue<pair<coord, int>>& to_explore,
                         vector<vector<int> >& distance) {
    int rows = grid.size();
    int cols = grid[0].size();
    int i = c.first.first;
    int j = c.first.second;
        
    for (int k = i - 1; k <= i + 1; ++k) {
      for (int q = j - 1; q <= j + 1; ++q) {
        if (0 <= k && k < rows && 0 <= q && q < cols &&
            abs(k - i) + abs(q - j) <= 1) {
          if (grid[k][q] == 0 && !visited[k][q]) {
            to_explore.push({{k, q}, c.second + 1});
            distance[k][q] += c.second + 1;
            ++times_visited[k][q];
            visited[k][q] = true;
          }
        }
      }
    }
  }                           
    
public:
  int shortestDistance(vector<vector<int>>& grid) {
    queue<pair<coord, int> > to_explore;
    vector<vector<int> > times_visited(grid.size(),
                                       vector<int>(grid[0].size(), 0));
    vector<vector<int> > distance(grid.size(),
                                  vector<int>(grid[0].size(), 0));
    vector<vector<bool> > visited(grid.size(),
                                  vector<bool>(grid[0].size(), false));
    int result = -1;
    int num_buildings = 0;
        
    // Drop a person walking out of each building
    // to see distance to rest of the grid
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[i].size(); ++j) {
        if (grid[i][j] == 1) {
          ++num_buildings;
                    
          // reset everything to not visited
          for (auto& row : visited)
            fill(row.begin(), row.end(), false);
                    
          VisitSurroundings({{i,j}, 0}, grid, visited, 
                            times_visited, to_explore,
                            distance);
                    
          while(!to_explore.empty()) {
            auto c  = to_explore.front();
            to_explore.pop();
       
            VisitSurroundings(c, grid, visited, 
                              times_visited, 
                              to_explore, distance);
          }
        }
      }
    }
        
    // Compute best solution
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[i].size(); ++j) {
        // If we can build in current spot and can be reached from all the buildings,
        // update best solution
        if (grid[i][j] == 0 && times_visited[i][j] == num_buildings) {
          if(result == -1)
            result = distance[i][j];
          else
            result = min(result, distance[i][j]);
        }
      }
    }
        
    return result;        
  }
};
