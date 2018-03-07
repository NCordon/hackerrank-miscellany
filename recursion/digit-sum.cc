// https://www.hackerrank.com/challenges/recursive-digit-sum/problem
#include <bits/stdc++.h>

using namespace std;

long long digit_sum(string& n, int k){
  long long current = 0;
  long long partial_sum;
  string ciphers;
  
  if(n.size() == 1){
    if(k == 1)
      return n.front() - '0';
    else{
      ciphers = string(k, n.front());
    } 
  }
  else{
    partial_sum = 0;
    
    for(unsigned long long i = 0; i < n.size(); i++){
      partial_sum += n[i] - '0';
      
      if(partial_sum > numeric_limits<int>::max()){
        ciphers = to_string(partial_sum);
        current += digit_sum(ciphers, k);
        partial_sum = 0;
      }
    }
    if(partial_sum > 0)
      ciphers = to_string(partial_sum);
      current += digit_sum(ciphers, k);

    ciphers = to_string(current);
  }
  
  return digit_sum(ciphers, 1);
}

int main() {
  string n;
  int k;
  cin >> n >> k;
  int result = digit_sum(n, k);
  cout << result << endl;
  return 0;
}
