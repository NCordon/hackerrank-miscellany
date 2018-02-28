// https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
#include <bits/stdc++.h>
using namespace std;

typedef multiset<long long>::iterator multiset_it;

long long MaximumSubarraySum(const vector<long long>& values, long long m){
  long long max_sum = numeric_limits<long long>::min();
  long long current_sum;
  vector<long long> all_sums(values.size() + 1);
  multiset<long long> right_sums;
  multiset_it erase_pos, complementary_pos;
  
  all_sums[0] = 0;
  right_sums.insert(0);
  
  for (long i = 1; i < all_sums.size(); i++) {
    all_sums[i] = (values[i - 1] + all_sums[i - 1]) % m;
    right_sums.insert(all_sums[i]);
  }
  
  /*
    Idea: brute force (having a running sum vector and comparing
    pairs of positions in which the subvector could start and end,
    would be -> O(n²)
  
    Improvement: introduce running sums in a tree (the multiset),
    and for each position, take its running_sum, namely x, delete 
    it from the multiset, and search in the remaining sums in the tree
    (that is running sums that can be achieved in a position at the
    right of the current one), running sums that are as close as possible
    to either x-1 (in module) or to m-1. -> O(nlog n)  
  */
  for (long i = 0; i < all_sums.size() - 1; i++) {
    erase_pos = right_sums.find(all_sums[i]);
    right_sums.erase(erase_pos);
    
    complementary_pos = right_sums.lower_bound(all_sums[i]);

    if (complementary_pos != right_sums.begin()) {
      complementary_pos--;
      current_sum = (*complementary_pos - all_sums[i] + m) % m;
      max_sum = max(max_sum, current_sum);
    }
    
    complementary_pos = right_sums.end();
    complementary_pos--;
    
    current_sum = (*complementary_pos - all_sums[i]) % m;
    max_sum = max(max_sum, current_sum);
  }

  return max_sum;
}

int main() {
  long q, n, m;
  cin >> q;
  
  for (long i = 0; i < q; i++) {
    cin >> n >> m;
    vector<long long> values(n);
    
    for (long j = 0; j < n; j++) {
      cin >> values[j];
    }
    
    cout << MaximumSubarraySum(values, m) << endl;
  }
}
