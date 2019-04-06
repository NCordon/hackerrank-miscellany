#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;
  
int main() {
  int T;
  vector<int> used_primes;
  vector<int> encoding;
  unordered_map<int, char> mapping;
  list<int> primes = {2, 3};
  int N;
  int num_primes;
  int divisor;
  bool found, is_prime;
  list<int>::iterator it;
  int current, next;
  int aux;
  
  cin >> T;
  
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ": ";
    cin >> N >> num_primes;
    encoding.clear();
    used_primes.clear();
    
    // If current bound is greater than max stored prime
    // compute missing primes and add them to our list
    if (primes.empty() || N > primes.back()) {
      for (int p = primes.back() + 2; p < N; p += 2) {
        is_prime = true;
        it = primes.begin();
        
        while (it != primes.end() && *it < p / 2 && is_prime) {
          is_prime = p % *it != 0;
          ++it;
        }

        if (is_prime)
          primes.push_back(p);
      }
    }
    
    it = primes.begin();
    found = false;

    cin >> current >> next;

    while (*it < current && !found) {
      if (current % (*it) == 0) {
        found = true;
        divisor = *it;
      }
      
      ++it;
    }

    if (next % divisor != 0)
      divisor = current / divisor;

    encoding.push_back(current/divisor);
    encoding.push_back(divisor);
    divisor = next / divisor;
    encoding.push_back(divisor);

    for (int k = 0; k < (num_primes - 2); ++k) {
      cin >> current;

      // We have failed choosing first prime
      if (current % divisor != 0) {
        aux = encoding[k + 1];

        for (int q = 0; q < k + 2; ++q)
          encoding[q] = encoding[q + 1];

        encoding[k + 2] = aux;
        divisor = aux;
      }
      
      divisor = current / divisor;
      
      encoding.push_back(divisor);
    }

    used_primes = encoding;
    sort(used_primes.begin(), used_primes.end());
    auto removed = unique(used_primes.begin(), used_primes.end());
    used_primes.resize(distance(used_primes.begin(), removed));
    
    for (int p = 0; p < used_primes.size(); ++p) {
      mapping[used_primes[p]] = 'A' + p;
    }

    for (int p : encoding) {
      cout << mapping[p];
    }
    
    cout << endl;
  }

}
