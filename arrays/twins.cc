// https://www.hackerrank.com/contests/w26/challenges/twins
// O(m log(log(m)))
#include <bits/stdc++.h>
using namespace std;

// test cases: 
//   3 13
//   1 3
int main(){
  int n,m;
  cin >> n >> m;
  vector<bool> primes(m + 1, true);
  int count = 0;
  bool prev_prime = false;
  
  primes[1] = false;
  primes[2] = primes[3] = true;
  
  // Modified Erathostenes' sieve
  for(int i = 3; i <= m; i += 2){
    if(primes[i]){
      for(int j = 3; j <= m/i; j += 2)
        primes[i * j] = false;
    }
  }

  if(n % 2 == 0)
    n++;
  
  for(int i = n; i <= m; i += 2){
    if(primes[i]){
      if(prev_prime)
        count++;
      prev_prime = true;
    }
    else
      prev_prime = false;
  }
  
  cout << count << endl;
  return 0;
}
