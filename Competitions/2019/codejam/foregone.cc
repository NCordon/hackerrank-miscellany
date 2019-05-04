#include <iostream>
using namespace std;

int main() {
  int N;
  int current_number;
  int A, B;
  int current_digit;
  int power;
    
  cin >> N;
    
  for (int i = 1; i <= N; ++i) {
    power = 1;
    A = 0;
    B = 0;
    cin >> current_number;
    
    while (current_number != 0) {
      current_digit = current_number % 10;
            
      if (current_digit == 4) {
        A += 2 * power;
        B += 2 * power;
      } else {
        A += current_digit * power;
      }
            
      power *= 10;
      current_number /= 10;
    }
        
    cout << "Case #" << i << ": " << A << " " << B << endl;
  }
}
