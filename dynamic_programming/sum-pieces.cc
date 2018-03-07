// https://www.hackerrank.com/challenges/summing-pieces/problem
#include <bits/stdc++.h>
using namespace std;

unsigned long long MOD = 1E9 + 7;

unsigned long long sum_pieces(vector<unsigned long long>& A){
  unsigned long long sum = 0;
  unsigned long long sum_coefs = 1;
  unsigned long long adjust_sum2 = 0;
  unsigned long long adjust_sum = 1;
  unsigned long long possibilities = 1;
  unsigned long long old_poss = 0;
  
  for(unsigned long long i = 0; i < A.size(); i++){    
    sum = (2 * sum) % MOD;
    sum = (sum + adjust_sum2) % MOD;
    sum = (sum + ((adjust_sum * A[i]) % MOD)) % MOD;
    sum = (sum + ((old_poss * A[i]) % MOD)) % MOD;

    adjust_sum = (adjust_sum + sum_coefs) % MOD;
    adjust_sum = (adjust_sum + ((2 * old_poss) % MOD)) % MOD;
    sum_coefs = (sum_coefs + old_poss) % MOD;

    adjust_sum2 = (adjust_sum2 + (((possibilities * A[i]) % MOD))) % MOD;
    possibilities = (possibilities * 2);
    old_poss = (possibilities / 2) % MOD;
    possibilities %= MOD;
  }
  
  return sum;
}

int main() {
  long long n;
  cin >> n;
  vector<unsigned long long> A(n);
  
  for(int i = 0; i < n; i++)
    cin >> A[i];
  
  unsigned long long result;
  
  result = sum_pieces(A);
  cout << result << endl;
  return 0;
}
