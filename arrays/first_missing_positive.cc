// https://leetcode.com/problems/first-missing-positive/
// O(n) solution and O(1) in extra space
// The idea is to mark the indexes for an element in
// a vector as negative if we arrive at such an element
class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    int current;
    int solution = n + 1;
    
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= 0)
        nums[i] = solution;
    }
    
    for (int i = 0; i < n; ++i) {
      current = abs(nums[i]) - 1;
      
      if (current >= 0 && current < n)
        nums[current] = -(abs(nums[current]));
    }
    
    for (int i = 0; i < n && solution > n; ++i) {
      if (nums[i] > 0)
        solution = i + 1;
    }
    
    return solution;
  }
};
