// https://www.hackerrank.com/challenges/absolute-permutation/problem
#include <bits/stdc++.h>
using namespace std;

vector<int> AbsolutePermutation(int N, int K){
  vector<int> result;
  
  if (K == 0) {
    result.resize(N);
    iota(result.begin(), result.end(), 1);
  }
  else if ((N/K) % 2 == 0 && (N/K) * K == N) {
    for (int q = 0; q < N/K; q++){
      for (int j = 1; j <= K; j++){
        if(q % 2 == 0)
          result.push_back((q + 1)*K + j);
        else
          result.push_back((q - 1)*K + j);
      }
    }
  }
  
  return result;
}

int main() {
  int T, N, K;
  cin >> T;
  
  for (int i = 0; i < T; i++) {
    cin >> N >> K;
    vector<int> permutation = AbsolutePermutation(N, K);
    if(!permutation.empty())
      copy(permutation.begin(), permutation.end(), 
           ostream_iterator<int>(cout, " "));
    else
      cout << -1;
    
    cout << endl;
  }
  
  return 0;
}
