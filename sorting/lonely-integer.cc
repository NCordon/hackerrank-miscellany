// Solution to https://www.hackerrank.com/challenges/lonely-integer

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
  int n, found = -1, element;
  vector<int> values;
  make_heap(values.begin(), values.end());
    
  // Read number of elements
  cin >> n;
    
  // Read vector of numbers
  for(int i=0; i<n; i++){
    cin >> element;
    values.push_back(element);
    push_heap(values.begin(), values.end());
  }
    
  sort_heap(values.begin(), values.end());
    
  for(int i=0; i<n and found<0; i+=2){        
    if(values[i] != values[i+1] or (i+1)==n)
      found = i;
  }
    
  // Result
  cout << values[found];
    
  return 0;
}
