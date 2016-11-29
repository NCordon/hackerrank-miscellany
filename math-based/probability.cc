// Solves this: https://www.hackerrank.com/challenges/sherlock-and-probability

// Main problems tackled: integer overflow, not returning the solution fraction
// in with proper format, not reinitializing the queue after a single iteration

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// Assumes a>=b
long long int gcd(long long int a, long long int b){
  if(b==0)
    return a;
  if(a%b == 0) 
    return b;
  else
    return gcd(b,a%b);
}

int main() {
  int digit, separation, divisor;
  long long int sum, count, n, t, k;
  queue<int> prev;

  int antes;
  cin >> t;
    
  for(int i=0; i<t; i++){
    cin >> n >> k;
    prev = queue<int>();
    // Remove trailing linebreak
    cin.get();
        
    // Adjustment of k
    separation = min(k+1,n);        
    sum = 0;
    count = 0;
        
    for(int j=1; j<=n; j++){
      digit = cin.get() - '0';
            
      if (j <= separation){
        count += digit;
        prev.push(digit);
                
        if(j == separation)
          sum += count*count;
      }
      else{
        sum += (digit + (count-prev.front())*digit*2);
        count = (count-prev.front() + digit);
        prev.push(digit);
        prev.pop();
      }
    }   
    divisor = gcd(n*n, sum);
    cout << sum/divisor << "/" << n*n/divisor << endl;
  }
    
  return 0;
}
