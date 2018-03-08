// https://leetcode.com/problems/remove-duplicates-from-sorted-array
// O(1) in space solution

class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    // next position to write
    int i = 0;
    bool unique;
      
    for (int j = 0; j < nums.size(); ++j) {
      unique = true;
        
      for (int k = 0; k < i && unique; ++k) {
        if (nums[k] == nums[j])
          unique = false;
      }
        
      if(unique) {
        nums[i] = nums[j];
        ++i;
      }
    }
      
    return i;
  }
};
