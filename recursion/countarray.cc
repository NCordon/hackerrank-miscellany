// https://www.hackerrank.com/challenges/construct-the-array/problem
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1E9 + 7;


/*
 Idea: Let's call N(n,k,x) = arrays that start in 1 and end in x, and have length k

N(n,k,x) =  k(k-1)^{n-1} (filling positions between 1 and x with unequal contiguous numbers) -
          - 2(k-1)^{n-3} (number of arrays that either start in x or end in k)
          + N(n - 2,k,x) (number of arrays with n-2 positions that start in 1 and end in x
*/
signed long long CountArray(int n, int k, int x, vector<long>& kpow) {
  long long result;
  
  if (n == 2) {
    result = (x == 1 ? 0 : 1);
    return result;
  } else if (n == 3) {
    result = (x == 1 ? k - 1 : k - 2);
    return result;
  } else {
    result = k * kpow[n - 3] % MOD;
    result = (result - 2 * kpow[n - 3]) % MOD;
    
    if (result < 0)
      result += MOD;
    
    result = (result + CountArray(n-2, k, x, kpow)) % MOD;
  }
  
  return result; 
}

int main() {
  int n;
  int k;
  int x;  
  cin >> n >> k >> x;
  vector<long> kpow(n - 2);
  kpow[0] = 1;
  
  for (int i = 1; i < kpow.size(); i++) {
    kpow[i] = (kpow[i - 1] * (k - 1)) % MOD;
  }
  
  long answer = CountArray(n, k, x, kpow);
  cout << answer << endl;
  return 0;
}
