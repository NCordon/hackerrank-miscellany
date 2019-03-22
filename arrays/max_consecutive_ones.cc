// https://leetcode.com/problems/max-consecutive-ones/
// O(n) solution where n is the length of nums
class Solution {
public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    int i = -1;
    int j = 0;
    int max_length = 0;
    
    while(j < nums.size()) {
      if (nums[j] == 0) {
        max_length = max(max_length, j - i - 1);  
        i = j;
      }
      
      ++j;
    }
    
    max_length = max(max_length, j - i - 1);
    
    return max_length;
  }
};
