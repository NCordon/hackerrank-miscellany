// https://www.hackerrank.com/challenges/abbr/problem
#include <bits/stdc++.h>
#include <cctype>
using namespace std;

bool abbreviation(string a, string b) {
  bool can_abbreviate = true;
  bool prev_abbreviate;
  vector<bool> sub_abbreviate(a.size() + 2, false);
  vector<bool> old_abbreviate(a.size() + 2, false);
    
  /*
  N(i,j) = (a_i lowercase && N(i+1,j)) || 
           (a_i == b_j || uppercase(a_i) == b_j) && N(i+1,j+1))
           
  A = [a_0, ..., a_{n-1}]
  B = [b_0, ..., b_{m-1}]
  
  Test cases:
   daBcd
   ABC
  */
  if(a.size() < b.size()){
    can_abbreviate = false;
  }
  else{
    old_abbreviate[a.size()] = true;
    
    // Computes N(i, m)
    for(int i = a.size() - 1; i >= 0; i--){
      old_abbreviate[i] = old_abbreviate[i + 1] && islower(a[i]);
    }
    
    
    for(int j = b.size() - 1; j >= 0; j--){
      prev_abbreviate = false;
      can_abbreviate = false;
      
      for(int i = a.size(); i >= 0; i--){
        if(i < a.size()){
          can_abbreviate = (a[i] == b[j] || toupper(a[i]) == b[j]) && 
                           old_abbreviate[i + 1];
        }
        
        can_abbreviate = (islower(a[i]) && prev_abbreviate) || can_abbreviate;
        prev_abbreviate = can_abbreviate;
        sub_abbreviate[i] = can_abbreviate;
      }
      
      old_abbreviate = sub_abbreviate;
    }
  }
  
  return can_abbreviate;
}

int main() {
  int q;
  cin >> q;
  for(int a0 = 0; a0 < q; a0++){
    string a;
    cin >> a;
    string b;
    cin >> b;
    bool result = abbreviation(a, b);
    if(result)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
