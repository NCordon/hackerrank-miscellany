//https://www.hackerrank.com/challenges/xoring-ninja/problem

#include <bits/stdc++.h>
using namespace std;

long MOD = 1E9 + 7;

long XorSum(const vector<long>& values) {
  long result = 0;
  // Value of XOR as key, count as value
  unordered_map<long, long> counts;
  // Introduce empty set
  counts[0] = 1;
  long current_xor;
  
  for (long value : values) {
    unordered_map<long, long> current_count;
    
    for (auto& prev_count : counts) {
      current_xor = prev_count.first ^ value;
      
      if(current_count.count(current_xor) == 0)
        current_count[current_xor] = 0;
      
      current_count[current_xor] = prev_count.second;
    }
    
    for(auto& this_count : current_count) {
      if(counts.count(this_count.first) == 0)
        counts[this_count.first] = 0;
      
      counts[this_count.first] = (counts[this_count.first] + this_count.second) % MOD;
    }
  }
  
  for (auto& total_count : counts) {
    result = (result + total_count.first * total_count.second) % MOD;
  }
  
  return result;
}

int main() {
  int T, n;
  cin >> T;
  
  for (int i = 0; i < T; i++) {
    cin >> n;
    vector<long> values(n);
    
    for (int j = 0; j < n; j++) {
      cin >> values[j];
    }
    
    cout << XorSum(values) << endl;    
  }
}

