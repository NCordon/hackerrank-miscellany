// https://www.hackerrank.com/challenges/non-divisible-subset/problem
#include <bits/stdc++.h>
using namespace std;


int main() {
  int n, k;
  cin >> n >> k;
  vector<int> rests(k);
  int max_size = 0;
  int current;
  
  for (int i = 0; i < n; i++) {
    cin >> current;
    rests[current % k]++;
  }
  
  for (int i = 0; i < k; i++) {
    if ((k - i) % k != i) {
      max_size += max(rests[i], rests[k - i]);
      rests[i] = rests[k - i] = 0;
    }
    else if(rests[i] > 0)
        max_size += 1;
  }
  
  cout << max_size << endl;
  
  return 0;
}
