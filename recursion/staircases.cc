// https://www.hackerrank.com/challenges/ctci-recursive-staircase/problem
#include <bits/stdc++.h>

using namespace std;

int main(){
  int s;
  cin >> s;
  vector<int> climb_ways{1};
  int current_climb_ways;
  
  for(int a0 = 0; a0 < s; a0++){
    int n;
    cin >> n;

    for(int i = climb_ways.size(); i <= n; i++){
      current_climb_ways = 0;
      
      for(int step = 1; i - step >= 0 && step <= 3; step++){
        current_climb_ways += climb_ways[i - step];
      }
      climb_ways.push_back(current_climb_ways);
    }
    cout << climb_ways[n] << endl;
  }
  return 0;
}
