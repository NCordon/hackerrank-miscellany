#include <iostream>
using namespace std;

int main() {
  int C;
  int N, M;
  int result;

  cin >> C;
  
  for (int i = 1; i <= C; ++i) {
    cin >> N >> M;
    
    result = (N / 2 + N % 2);
    result += (M / 2 + M % 2);

    cout << "Case #" << i  << ": " << result << endl;
  }
}
