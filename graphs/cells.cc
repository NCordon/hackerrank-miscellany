// https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int get_biggest_region(vector< vector<int> > grid){
  stack<pair<int,int>> to_explore;
  int length;
  int max_length = -1;
  int row, col;
  int new_row, new_col;
  
  for(int i = 0; i < grid.size(); i++){
    for(int j = 0; j < grid[i].size(); j++){
      length = 0;
      
      if(grid[i][j] == 1){
        to_explore.push(make_pair(i,j));      
        length++;
        grid[i][j] = 0;
        
        while(!to_explore.empty()){
          row = to_explore.top().first;
          col = to_explore.top().second;
          to_explore.pop();
          
          for(int k = -1; k <= 1; k++){
            for(int l = -1; l <= 1; l++){
              new_row = row + k;
              new_col = col + l;
              
              if(new_row < grid.size() && new_col < grid[i].size() &&
                 grid[new_row][new_col] == 1){
                to_explore.push(make_pair(new_row, new_col));
                length++;
                grid[new_row][new_col] = 0;
              }
            }
          }
        }
      }
      max_length = max(length, max_length);
    }
  }
  
  return max_length;
}

int main(){
  int n;
  cin >> n;
  int m;
  cin >> m;
  vector< vector<int> > grid(n,vector<int>(m));
  for(int grid_i = 0;grid_i < n;grid_i++){
    for(int grid_j = 0;grid_j < m;grid_j++){
      cin >> grid[grid_i][grid_j];
    }
  }
  cout << get_biggest_region(grid) << endl;
  return 0;
}
