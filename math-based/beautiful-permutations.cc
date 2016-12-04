#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

long int factorial_mod(int n, int max_two_products, vector<long long int> &factorial){
  long long int result = 1;
  int max_calculated = (factorial.size() - 1);
  result = factorial[min(max_calculated, n)];

  for (int i=(max_calculated+1); i<=n; i++){
    result *= i;
    result %= (1000000007);
    factorial.push_back(result);
  }
  
  for (int i=0; i<max_two_products; i++){
    result *= 5000000004;
    result %= 1000000007;
  }

  return (result%(1000000007));
}

int main(){
  long long int n, q, m;
  list<int> numbers;
  long long int result;
  int mult = -1, current;
  vector<long long int> factorial(1,1);
  
  cin >> q;
  
  for(int i=0; i<q; i++){
    cin >> n;
    // Cleans last iteration values
    numbers.clear();
    result = 0;

    // Reads current vector
    for(int j=0; j<n; j++){
      cin >> current;
      numbers.push_back(current);
    }
    
    numbers.sort();
    numbers.unique();
    m = n-numbers.size();
    
    result = factorial_mod(n, m, factorial);

    if (m > 0)
      result -= (m%1000000007)*factorial_mod(n-1, m-1, factorial);      

    
    for(int j=0; j<m-1; j++){
      result -= (mult*((m-j)%1000000007)*((m-j-1)%1000000007)*factorial_mod(n-j-2, m-j-1, factorial));
      mult *= -1;
    }
    
    cout << result << endl;     
  }
      
  return 0;
}
