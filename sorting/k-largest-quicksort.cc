// Solution to https://leetcode.com/problems/kth-largest-element-in-an-array

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    int aux, left, right, pivote, old_left, old_right;
    stack<int> left_pointer;
    stack<int> right_pointer;
    left_pointer.push(0);
    right_pointer.push(nums.size()-1);
            
    while(!left_pointer.empty()){
      old_left = left = left_pointer.top();
      old_right = right = right_pointer.top();
      pivote = nums[left];
                
      left_pointer.pop();
      right_pointer.pop();
                
      if (right > left){
        while(left != right){  
          if(nums[right] < pivote)
            right--;
          else if(nums[left] >= pivote)
            left++;
          else{
            aux = nums[left];
            nums[left] = nums[right];
            nums[right] = aux;
            right--;
          }
        }
    
        nums[old_left] = nums[left];
        nums[left] = pivote;
              
                        
        left_pointer.push(old_left);
        left_pointer.push(left+1);
        right_pointer.push(left-1);
        right_pointer.push(old_right);
      }
    }
      
    return nums[k-1];
  }
};
