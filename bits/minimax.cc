// https://www.hackerrank.com/challenges/yet-another-minimax-problem/problem
#include <bits/stdc++.h>

using namespace std;

// Test cases 1 2 3 4
// 001 010 011 100
int minimax(vector <int> a){
  int left_shifts = 0, right_shifts = 0;
  int mask;
  // O(nlog n)
  sort(a.begin(), a.end());
  int last_element = a.back();
  int first_element = a.front();
  int minimum;
  
  if(first_element != last_element){
    minimum = numeric_limits<int>::max();

    while((last_element >>= 1) != 0)
      left_shifts++;
  
    mask = (1 << left_shifts);
    last_element = a.back();

    while((first_element & mask) == (last_element & mask)){
      mask >>= 1;
      right_shifts++;
    }
    mask = (1 << (left_shifts - right_shifts + 1)) - 1;
  
    for(int& element : a){
      element &= mask;
    }
  
    vector<int>::iterator right_pos = lower_bound(
      a.begin(), a.end(), (1 << (left_shifts - right_shifts))
    );
    int right_posi = right_pos - a.begin();
  
    for(int i = right_posi; i < a.size(); i++){
      for(int j = 0; j < right_posi; j++){
        minimum = min(a[i] ^ a[j], minimum);
      }
    }
  }
  else{
    minimum = first_element;
  }
  
  return minimum;  
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int a_i = 0; a_i < n; a_i++){
    cin >> a[a_i];
  }
  int result = minimax(a);
  cout << result << endl;
  return 0;
}
