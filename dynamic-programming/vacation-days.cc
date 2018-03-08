// https://leetcode.com/problems/maximum-vacation-days/
// O(K N²) solution, with K number of weeks, N number of cities
class Solution {
public:
  int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
    int num_weeks = days[0].size();
    int num_cities = days.size();
    vector<int> sol(num_cities, 0);
    vector<int> prev(num_cities, 0);
    int maximum, current;
      
    // Compute first week
    for (int i = 0; i < num_cities; ++i) {
      flights[i][i] = 1;
        
      if (flights[0][i] == 0)
        sol[i] = current = numeric_limits<int>::min();
      else
        sol[i] = days[i][0];
    }
      
    for (int j = 1; j < num_weeks; ++j) {
      prev = sol;
        
      for (int i = 0; i < num_cities; ++i) {
        maximum = numeric_limits<int>::min();
          
        for (int k = 0; k < num_cities; ++k) {
          if (flights[k][i] == 0)
            current = numeric_limits<int>::min();
          else
            current = prev[k] + flights[k][i] * days[i][j];
           
          maximum = max(maximum, current);
        }
          
        sol[i] = maximum;
      }
    }
      
    return *max_element(sol.begin(), sol.end());
  }
};
