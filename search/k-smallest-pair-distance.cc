// https://leetcode.com/problems/find-k-th-smallest-pair-distance/solution/
// O(N log M) solution where N is the size of nums and M is
// the maximum distance among its elements
// Idea: do a binary search among the possible solutions, which lie in [0, W]
class Solution {
public:
  int smallestDistancePair(vector<int>& nums, int k) {
    int num_lower = 0;
    int num_lower_equal = 0;
    sort(nums.begin(), nums.end());
    int right = nums.back() - nums.front();
    int left = 0;
    int current;
    int length = nums.size();
    bool materialized = false;
    
    while (num_lower_equal < k || num_lower >= k || !materialized) {      
      current = (left + right) / 2;
      num_lower = 0;
      num_lower_equal = 0;
      materialized = false;
      int j = length - 1;
      int l = length - 1;
      
      for (int i = length - 1; i > 0; --i) {
        while (j >= 0 && (nums[i] - nums[j]) <= current) {
          if (nums[i] - nums[j] == current)
            materialized = true;
          
          --j;
        }
        
        l = min(i, l);
        
        while (l >= 0 && (nums[i] - nums[l]) < current)
          --l;
        
        num_lower_equal += i - j - 1;
        num_lower += max(i - l - 1, 0);
      }
      
      if (num_lower_equal < k)
        left = current + 1;
      else
        right = current - 1;
    }
    
    return current;
  }
};
