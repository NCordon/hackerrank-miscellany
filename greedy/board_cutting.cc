//https://www.hackerrank.com/challenges/board-cutting
#include <bits/stdc++.h>

using namespace std;
long long MOD = 1E9 + 7;

long long board_cutting(vector<long long> cost_x, vector<long long> cost_y){
  sort(cost_x.begin(), cost_x.end(), greater<long long>());
  sort(cost_y.begin(), cost_y.end(), greater<long long>());
  long long remain_sumx = accumulate(cost_x.begin(), cost_x.end(), 0);
  long long remain_sumy = accumulate(cost_y.begin(), cost_y.end(), 0);
  long long x_cuts = 1;
  long long y_cuts = 1;
  long long i = 0;
  long long j = 0;
  long long cost = 0;

  copy(cost_x.begin(), cost_x.end(), ostream_iterator<long long>(cerr, " "));
  cerr << endl;
  copy(cost_y.begin(), cost_y.end(), ostream_iterator<long long>(cerr, " "));
  cerr << endl;
  
  while(i < cost_x.size() || j < cost_y.size()){
    if(y_cuts * remain_sumx > x_cuts * remain_sumy){
      cost += y_cuts * cost_x[i];
      remain_sumx -= cost_x[i];
      x_cuts++;
      i++;
    }
    else{
      cost += x_cuts * cost_y[j];
      remain_sumy -= cost_y[j];
      y_cuts++;
      j++;
    }
  }
  
  return cost;
}

int main() {
  int q;
  cin >> q;
  
  for(int a0 = 0; a0 < q; a0++){
    long long m;
    long long n;
    cin >> m >> n;
    vector<long long> cost_y(m-1);
    
    for(long long cost_y_i = 0; cost_y_i < m-1; cost_y_i++){
      cin >> cost_y[cost_y_i];
    }
    
    vector<long long> cost_x(n-1);
    
    for(long long cost_x_i = 0; cost_x_i < n-1; cost_x_i++){
      cin >> cost_x[cost_x_i];
    }
    
    long long result = board_cutting(cost_x, cost_y);
    cout << result << endl;
  }
  

  return 0;
}
