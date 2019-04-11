// https://leetcode.com/problems/house-robber-ii/
// O(N) solution algorithmically and O(1) in space
// Calling S(i, j) = maximum bounty we can get robbing
// houses from i to j (both included), solution would be
// max { S(0, N - 2), S(1, N - 1) } where N is the length of
// nums. And S(i, j) = max { A[i] + S(i + 2, j), S(i + 1, j) }
class Solution {
public:
  int rob(vector<int>& nums) {
    int n = nums.size();
    int solution;
    
    if (n == 1)
      solution = nums[0];
    else {
      int a = 0;
      int b = 0;
      int c = 0;
      int d = 0;
      int aux;
      
      for (int i = n - 1; i >= 1; --i) {
        aux = max(nums[i] + b, a);
        b = a;
        a = aux;
      }
        

      for (int i = n - 2; i >= 0; --i) {
        aux = max(nums[i] + d, c);
        d = c;
        c = aux;
      }
      
      solution = max(a, c);
    }
    
    return solution;
  }
};
