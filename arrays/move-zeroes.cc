// https://leetcode.com/problems/move-zeroes/

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    int i = -1;
    
    for (int j = 0; j < nums.size(); ++j) {
      if (nums[j] == 0 && i == -1)
        i = j;
      
      if (nums[j] != 0 && i != -1) {
        swap(nums[i], nums[j]);
        ++i;
      }
    }
  }
};
