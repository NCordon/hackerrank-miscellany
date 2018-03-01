// https://www.hackerrank.com/challenges/angry-children-2/problem
#include <bits/stdc++.h>
using namespace std;

/* Idea:
We have to find the minimum unfairness between K candies out of the N possible
ones. We first sort the array of candies, since a solution is going to be composed
of K contiguous positions. Given a set x_1,.., x_k of K contiguous candies, 
if we can compute unfairness of x_2, ... x_{k+1} in O(1) using the unfairness of
x_1, ...,x_k, then we have an O(N log N) algorithm (cost of sorting)
*/

long MinUnfairness(vector<long> candies, long N, long K) {
  long sum;
  long slide = 0;
  long min_cost = 0;
  long current_cost = 0;
  
  sort(candies.begin(), candies.end());
  
  if(!candies.empty())
    sum = candies[0];
  
  for (long i = 1; i < K; i++) {
    slide++;
    min_cost += slide * candies[i] - sum;
    sum += candies[i];
  }
  
  current_cost = min_cost;
  
  for (long i = K; i < N; i++) {
    sum -= candies[i - K];
    current_cost += - (sum - candies[i - K] * slide)
                    + (slide * candies[i] - sum);
    min_cost = min(current_cost, min_cost);
    sum += candies[i];    
  }
  
  return min_cost;  
}

int main() {
  long N, K;
  cin >> N >> K;
  vector<long> candies(N);
  
  for (long i = 0; i < N; i++) {
    cin >> candies[i];
  }
  
  cout << MinUnfairness(candies, N, K) << endl;
}
