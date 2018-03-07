//https://www.hackerrank.com/challenges/the-great-xor/problem

#include <bits/stdc++.h>
using namespace std;


// Test cases: x = 2, x = 10, x = 1
long GreaterXors(long x) {
  long current = x;
  long count = 1;
  long result = 0;
  long last_bit;
  
  while (current != 0) {
    last_bit = current % 2;
    
    if (last_bit == 0) {
      result += count;
    }
    
    current >>= 1;
    count <<= 1;
  }
  
  return result;
}

int main() {
  long q;
  long x;
  
  cin >> q;
  
  for (int i = 0; i < q; i++) {
    cin >> x;
    
    cout << GreaterXors(x) << endl;
  }
  
  return 0;
}

