// https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct GeneCount{
  long A; 
  long C;
  long G;
  long T;
  
  long& operator[](char g){
    if (g == 'A')
      return A;
    else if (g == 'C')
      return C;
    else if (g == 'G')
      return G;
    else
      return T;
  }
};

bool operator<(const GeneCount& count_one, const GeneCount& count_two) {
  if (count_one.A < count_two.A ||
      count_one.C < count_two.C ||
      count_one.G < count_two.G ||
      count_one.T < count_two.T)
    return true;
  else
    return false;
}

GeneCount operator-(const GeneCount& count_one, const GeneCount& count_two) {
  GeneCount result;
  result.A = count_one.A - count_two.A;
  result.C = count_one.C - count_two.C;
  result.G = count_one.G - count_two.G;
  result.T = count_one.T - count_two.T;
  
  return result;
}

long ShortestModification(string genes, int n) {
  long result = n;
  vector<GeneCount> counts(n + 1);
  long right = 1;
  counts[0].A = counts[0].C = counts[0].G = counts[0].T = 0;
  
  // Compute cumulative counts of each gene
  for (long i = 1; i <= n; i++) {
    counts[i] = counts[i - 1];
    counts[i][genes[i - 1]]++;
  }
  
  GeneCount target;
  target.A = max(counts[n].A - n / 4, 0L);
  target.C = max(counts[n].C - n / 4, 0L);  
  target.G = max(counts[n].G - n / 4, 0L);
  target.T = max(counts[n].T - n / 4, 0L);
  
  // If no change necessary, return 0
  if (target.A == n / 4 &&
      target.C == n / 4 &&
      target.G == n / 4 &&
      target.T == n / 4)
    result = 0;
  // Else, compute minimum substring that contains
  // values to be changed (target count)
  else {
    for (long left = 1; left <= n; left++) {
      while ((counts[right] - counts[left - 1]) < target && 
             right < n)
        right++;
      
      if (! ((counts[right] - counts[left - 1]) < target) )
        result = min(right - left + 1, result);
    }
  }
  
  return result;
}

int main() {
  long n;
  string gene;
  
  cin >> n >> gene;
  cout << ShortestModification(gene, n);
}
