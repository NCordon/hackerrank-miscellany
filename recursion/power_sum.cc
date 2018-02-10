// https://www.hackerrank.com/challenges/the-power-sum/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long power_sum(int x, int n, int old){
  int result = 0;
  int current;
  
  for(int i = old; i < x; i++){
    current = pow(i, n);

    if(current == x)
      result += 1;
    else if(current < x)
      result += power_sum(x - current, n, i + 1);
  }
  
  return result;
}

int main() {
  int x, n;
  cin >> x >> n;
  long long result = power_sum(x, n, 1);
  
  cout << result << endl;
  return 0;
}
