// https://leetcode.com/problems/k-empty-slots/solution/
// O(n log n) algorithmically where n is the number of flowers
// O(n) in memory
class Solution {
public:
  int kEmptySlots(vector<int>& flowers, int k) {
    set<int> bloomed;
    bloomed.insert(0);
    
    int sol = -1;
    set<int>::iterator lower, upper;
    int flower;
    bool found = false;
    
    for (int i = 0; i < flowers.size() && !found; ++i) {
      flower = flowers[i];
      lower = bloomed.lower_bound(flower);
      upper = bloomed.upper_bound(flower);
      --lower;
      
      if (((*lower != 0) && (flower - *lower - 1) == k) || 
          (upper != bloomed.end() && (*upper - flower - 1) == k)) {
        sol = i + 1;
        found = true;
      }
      
      bloomed.insert(flower);
    }
    
    return sol;
  }
};
