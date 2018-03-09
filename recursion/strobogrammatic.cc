// https://leetcode.com/problems/strobogrammatic-number-ii/

class Solution {
public:
  vector<string> findStrobogrammatic(int n) {
    vector<string> case_one{"0", "1", "8"};
    vector<string> case_two{"00", "11", "69", "88", "96"};
    string number = string(n, ' ');
    vector<string> sides, inners, result;
    int prev_n;
      
    if (n == 1)
      return case_one;
    if (n == 2)
      return vector<string>(case_two.begin() + 1, 
                            case_two.end());
      
    if (n % 2 == 0) {
      prev_n = n - 2;
      inners = case_two;
    } else {
      prev_n = n - 1;
      inners = case_one;
    }
      
    sides = findStrobogrammatic(prev_n);
      
    for (string& side : sides) {
      for (int i = 0; i < prev_n / 2; ++i) {
        number[i] = side[i];
        number[n - 1 - i] = side[prev_n - 1 - i];
      }
        
      for (string& inner : inners) {
        number[prev_n / 2] = inner[0];
          
        if (n % 2 == 0)
          number[prev_n / 2 + 1] = inner[1];
          
        result.push_back(number);
      }
    }
      
    return result;     
  }
};
