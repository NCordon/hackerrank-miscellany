// https://leetcode.com/problems/kth-largest-element-in-an-array/
// O(n) solution (in amortized time) using a pivot similar
// to the one used in quicksort
class Solution {
public:
  int rec_search(int k, vector<int>& nums, 
                 int left, int right) {
    int pivot = nums[left];
    int i = left;
    int j = right;
    
    while (i <= j) {
      if (nums[i] <= pivot)
        ++i;
      else if (nums[j] > pivot)
        --j;
      else
        swap(nums[i], nums[j]);
    }
    
    if (i == k) {
      return pivot;
    } else if (i < k) {
      return rec_search(k, nums, i, right);
    } else {
      swap (nums[left], nums[i - 1]);
      return rec_search(k, nums, left, i - 2);
    }
  }
  
  int find_kth_largest(vector<int>& nums, int k) {
    return rec_search(nums.size() - k + 1, nums, 0, nums.size() - 1);
  }
};
