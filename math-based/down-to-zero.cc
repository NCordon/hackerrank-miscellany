// https://www.hackerrank.com/challenges/down-to-zero-ii/problem
#include <bits/stdc++.h>
using namespace std;

void MinOperations(vector<long> &partial_solutions, long N) {
  partial_solutions.resize(N + 1);
  iota(partial_solutions.begin(), partial_solutions.end(), 0);
  
  for (long i = 2; i <= N; i++) {
    partial_solutions[i] = min(partial_solutions[i], 
                               partial_solutions[i - 1] + 1);
    for (long j = 2; j <= min(i, N/i); j++) {
      partial_solutions[i * j] = min(partial_solutions[i * j], 
                                     partial_solutions[i] + 1);
    }
  }       
}


int main() {
  long Q;  
  cin >> Q;
  vector<long> queries(Q);
  vector<long> partial_solutions;
  long max_query;
  
  for (long i = 0; i < Q; i++) {
    cin >> queries[i];
  }
  
  max_query = *max_element(queries.begin(), queries.end());
  MinOperations(partial_solutions, max_query);
  
  for(auto q : queries){
    cout << partial_solutions[q] << endl;
  }
  
}
