// https://www.hackerrank.com/challenges/ctci-recursive-staircase/problem
#include <bits/stdc++.h>

using namespace std;

int main(){
    int s;
    cin >> s;
    for(int a0 = 0; a0 < s; a0++){
        int n;
        cin >> n;
        vector<int> climb_ways(n + 1, 0);
        climb_ways[0] = 1;
      
        for(int i = 1; i <= n; i++){
          for(int step = 1; i - step >= 0 && step <= 3; step++){
            climb_ways[i] += climb_ways[i - step];
          }
      }
        cout << climb_ways[n] << endl;
    }
    return 0;
}
