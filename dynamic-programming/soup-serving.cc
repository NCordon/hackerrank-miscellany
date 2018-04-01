// https://leetcode.com/problems/soup-servings/description/
// O(N²) algorithmically, O(N) in memory
#include<bits/stdc++.h>
using namespace std;

double soupServings(int N) {
  N = (N % 25 == 0 ? N / 25 : N / 25 + 1);
  vector<vector<double>> dist(5, vector<double>(N + 1, 0));
  dist[min(4, N)][N] = 1.0;
  
  for (int i = N; i > 4; --i) {
    for (int j = N; j > 0; --j) {
      dist[0][j] += 0.25 * dist[4][j];
      dist[1][max(j-1, 0)] += 0.25 * dist[4][j];
      dist[2][max(j-2, 0)] += 0.25 * dist[4][j];
      dist[3][max(j-3, 0)] += 0.25 * dist[4][j];
    }

    if (i > 4) {
      for (int k = 4; k > 0; --k)
        dist[k] = dist[k - 1];

      fill(dist[0].begin(), dist[0].end(), 0.0);
    }
  }

  for (int i = min(N, 4); i > 0; --i) {
    for (int j = N; j > 0; --j) {
      dist[max(i-4, 0)][j] += 0.25 * dist[i][j];
      dist[max(i-3, 0)][max(j-1, 0)] += 0.25 * dist[i][j];
      dist[max(i-2, 0)][max(j-2, 0)] += 0.25 * dist[i][j];
      dist[max(i-1, 0)][max(j-3, 0)] += 0.25 * dist[i][j];
    }
  }

  return accumulate(dist[0].begin() + 1, dist[0].end(), 0.0) +
         0.5 * dist[0][0];
}

int main() {
  cout << soupServings(176);
};
