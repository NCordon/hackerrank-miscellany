#include <iostream>
#include <string>
using namespace std;

int main() {
  int T, N;
  string path;
  cin >> T;
    
  for (int i = 1; i <= T; ++i) {
    cin >> N >> path;
    
    for (int j = 0; j < path.size(); ++j) {
      if (path[j] == 'S')
        path[j] = 'E';
      else
        path[j] = 'S';
    }
    cout << "Case #" << i << ": " << path << endl;
  }
}
