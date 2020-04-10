#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
using namespace std;

typedef vector<vector<int> > matrix;

bool repeatedElements(matrix& m, int j, bool by_row, int n) {
  vector<bool> seen(n + 1);
  bool repeated = false;
  
  for (int i = 0; i < n && !repeated; ++i) {
    int current = by_row ? m[j][i] : m[i][j];
    repeated = seen[current];
    
    if (!repeated)
      seen[current] = true;
  }

  return repeated;
}

int numWithRepeated(matrix& m, int n, bool by_row) {
  int count = 0;

  for (int i = 0; i < n; ++i)
    if (repeatedElements(m, i, by_row, n))
      ++count;

  return count;
}

matrix readMatrix(int n) {
  matrix m = vector<vector<int> >(n, vector<int>(n));
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> m[i][j];

  return m;
} 

int trace(matrix& m, int n) {
  int result = 0;
  
  for (int i = 0; i < n; ++i)
    result += m[i][i];

  return result;
}

int main() {
  int t, n;
  // read number of cases
  cin >> t;
  
  for (int i = 1; i <= t; ++i) {
    cin >> n;
    matrix m = readMatrix(n);

    int k = trace(m, n);
    int r = numWithRepeated(m, n, true);
    int c = numWithRepeated(m, n, false);
    cout << "Case #" << i << ":" << " " << k << " " << r << " " << c << endl;
  }
} 
