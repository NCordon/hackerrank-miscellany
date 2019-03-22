// https://leetcode.com/problems/max-consecutive-ones-ii/
// O(n) solution where n is the length of nums
class Solution {
public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    int i = -1;
    int k = -1;
    int j = 0;
    int max_length = 0;
    
    while (j < nums.size()) {
      if (nums[j] == 0) {
        if (k >= 0) {
          max_length = max(max_length, j - i - 1);
          i = k;
        } 
        k = j;
      } 
      ++j;
    }
    
    max_length = max(max_length, j - i - 1);
    
    return max_length;
  }
};
