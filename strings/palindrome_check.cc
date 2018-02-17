// https://www.hackerrank.com/challenges/richie-rich/problem
#include <bits/stdc++.h>
using namespace std;

string MaxPalindromeCheck(string check, int n, int k){
  string result = check;
  int compulsory_changes = 0;
  int extra_changes;
  
  for (int i = 0; i < n/2; i++) {
    if (check[i] != check[n - 1 - i])
      compulsory_changes++;
  }
  
  if (compulsory_changes > k)
    result = "";
  else {
    extra_changes = k - compulsory_changes;
    
    for (int i = 0; i < n/2; i++) {
      if (check[i] == check[n-i-1]) {
        if (check[i] != '9' && extra_changes > 1) {
          result[i] = result[n-i-1] = '9';
          extra_changes -= 2;
        }
      }
      else {
        // We have to use only an extra change and a compulsory one
        if (extra_changes > 0 && check[i] != '9' && check[n-i-1] != '9') {
          result[i] = result[n-i-1] = '9';
          extra_changes--;
        }
        else
          result[i] = result[n-i-1] = max(check[i] - '0', check[n-i-1] - '0') + '0';
      }
    }
    
    if (n % 2 != 0 && extra_changes > 0)
      result[n/2] = '9';
  }
  
  return result;
}


int main() {
  int n, k;
  string check;
  string palindrome_check;
  
  cin >> n >> k >> check;
  palindrome_check = MaxPalindromeCheck(check, n, k);
  
  if(palindrome_check.empty())
    cout << -1;
  else
    cout << palindrome_check;
}
