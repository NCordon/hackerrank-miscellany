#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;


int main() {
  int C;
  int N;
  long long multiple;
  long long divisor;
  long long candies;
  long long people;
  int current;
  cin >> C;

  for (int i = 1; i <= C; ++i) {
    cin >> N;
    candies = 0;
    people = 0;
    vector<long long> numbers(N);

    for (int j = 0; j < N; ++j)
      cin >> numbers[j];

    multiple = numbers[0];
    
    for (int j = 1; j < N; ++j)
      multiple = lcm(multiple, numbers[j]);
    
    for (long long number : numbers) {
      candies += multiple;
      people += multiple / number;
    }

    divisor = gcd(candies, people);
      
    cout << "Case #" << i << ": " << candies / divisor << "/" << people / divisor << endl;
  }
}
