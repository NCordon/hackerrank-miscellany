// Solution to: https://leetcode.com/problems/first-missing-positive/
// O(1) in space, O(n) in time

#include <algorithm>

class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    int minimum = nums.size(), maximum = 0;
    bool found = false;
    int result = 1;
    int dist;
        
        
    // Calculate maximum and minimum positive integers of the array
    for (int i : nums){
      if (i < minimum and i>0)
        minimum = i;
      if (i > maximum)
        maximum = i;
    }
        
    /* If minimum positive is 1
       mark positions of array found as negative
       being careful is something is alredy negative 
       (we have made it negative before)
    */
    if(minimum == 1){
      for(int i=0; i < nums.size(); i++)
        nums[i] = max(nums[i], minimum);
            
      for(int i=0; i < nums.size(); i++){
        int indice = nums[i] - 1;
                
        if(indice >= 0 and indice < nums.size() and nums[indice] > 0)
          nums[indice] = -nums[indice];
                    
        indice = -nums[i] - 1;
                
        if(indice >=0 and indice < nums.size() and nums[indice] > 0)
          nums[indice] = -nums[indice];
      }
            
      for(int i=0; i<nums.size() and !found; i++){
        if(nums[i]>0){
          dist = i;
          found = true;
        }
      }
        
      // If we found a position not made negative, that's the distance between
      //      1 and the first non present positive integer
      // If not, the result is maximum positive found in the array plus 1
      if(found)
        result = dist + 1;
      else
        result = maximum + 1;
    }
        
    return result;
  }
};
