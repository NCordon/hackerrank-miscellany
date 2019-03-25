// https://leetcode.com/problems/intersection-of-two-arrays/
// O(n) solution where n is the length of the shorter vector
// from the two inputs
class Solution {
public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size())
      return intersection(nums2, nums1);
    
    unordered_set<int> nums (nums1.begin(), nums1.end());
    vector<int> result;
    result.reserve(nums1.size());
    
    for (int n : nums2) {
      auto it = nums.find(n);
      
      if (it != nums.end()) {
        result.push_back(n);
        nums.erase(it);
      }
    }
    
    return result;
  }
};
