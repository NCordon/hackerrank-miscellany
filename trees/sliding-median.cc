// https://leetcode.com/problems/sliding-window-median/
// O(n log k) algorithmically where n is size of nums
typedef multiset<double>::iterator set_it;

class Solution {
public:
  vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    vector<double> result(n - k + 1);
    multiset<double, greater<double>> max_heap;
    multiset<double, less<double>> min_heap;
    vector<double> window(nums.begin(), nums.begin() + k);
    int max_size = k/2;
    int min_size = (k + 1)/2;
    int old, next;
    bool even = max_size == min_size;
    set_it pos;
    
    sort(window.begin(), window.end());
    
    for (int i = 0; i < k; ++i) {
      if (i < max_size)
        max_heap.insert(window[i]);
      else
        min_heap.insert(window[i]);
    }
    
    int q = 0;
    
    if (even)
      result[q] = (*max_heap.begin() + *min_heap.begin()) / 2;
    else
      result[q] = *min_heap.begin();
    
    ++q;
    
    for (int i = k; i < n; ++i) {
      old = nums[i - k];
      next = nums[i];
      
      if (old >= *min_heap.begin()) {
        pos = min_heap.find(old);
        min_heap.erase(pos);
        
        if ((!min_heap.empty() && next >= *min_heap.begin()) || 
            next >= *max_heap.begin()) {
          min_heap.insert(next);
        } else {
          max_heap.insert(next);
          min_heap.insert(*max_heap.begin());
          max_heap.erase(max_heap.begin());
        }
      } else {
        pos = max_heap.find(old);
        max_heap.erase(pos);
        
        if ((!max_heap.empty() && next <= *max_heap.begin()) ||
            next <= *min_heap.begin()) {
          max_heap.insert(next);
        } else {
          min_heap.insert(next);
          max_heap.insert(*min_heap.begin());
          min_heap.erase(min_heap.begin());
        }
      }
      
      if (even)
        result[q] = (*max_heap.begin() + *min_heap.begin()) / 2;
      else
        result[q] = *min_heap.begin();
      
      
      ++q;      
    }
    
    return result;
  }
};
