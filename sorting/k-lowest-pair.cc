// https://leetcode.com/problems/find-k-th-smallest-pair-distance/
// O(n²) solution

#include <bits/stdc++.h>
using namespace std;

int KthLowest(int i, int j, int k, vector<int>& values) {
  int pivot = values[i];
  int left = i;
  int right = j - 1;
    
  while (left < right) {
    if (values[left] <= pivot)
      ++left;
    else if (values[right] > pivot)
      --right;
    else
      swap(values[left], values[right]);
  }

  if (values[left] > pivot)
    --left;

  swap(values[i], values[left]);
  // Everything from values[i] to values[left] is lower or equal than pivot
  
  if (left == k - 1)
    return values[left];
  else if (left > k - 1)
    return KthLowest(i, left, k, values);
  else
    return KthLowest(left + 1, j, k, values);
}


int SmallestDistancePair(vector<int>& nums, int k) {
  int n = nums.size();
  vector<int> pairs(n * (n - 1) / 2);
  int l = 0;
    
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      pairs[l] = abs(nums[i] - nums[j]);
      ++l;
    }
  }
    
  return KthLowest(0, pairs.size(), k, pairs);
}

int main() {
  vector<int> nums{38, 33, 57, 65, 13, 2, 86, 75, 4, 56};
  int k = 26;

  cout << SmallestDistancePair(nums, k) << endl;
}
