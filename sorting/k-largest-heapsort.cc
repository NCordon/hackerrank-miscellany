// Solution to https://leetcode.com/problems/kth-largest-element-in-an-array/
// Heapsort
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    vector<int> copy(nums);
    make_heap(copy.begin(), copy.end());
    // By default ordered by <
    sort_heap(copy.begin(), copy.end());
        
    return copy[copy.size()-k];
  }
};
