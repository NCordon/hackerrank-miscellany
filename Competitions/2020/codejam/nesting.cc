#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
using namespace std;

string nested(string s) {
  int open = 0;
  string result;
  
  for (char digit: s) {
    int d = digit - '0';

    while (d > open) {
      result += '(';
      ++open;
    }
    while (d < open) {
      result += ')';
      --open;
    }
    
    result += digit;
  }

  while (open > 0) {
    result += ')';
    --open;
  }

  return result;
}

int main() {
  int t;
  // read number of cases
  cin >> t;
  
  for (int i = 1; i <= t; ++i) {
    string s;
    cin >> s;
    cout << "Case #" << i << ":" << " " << nested(s) << endl;
  }
}
