// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
/* 
   Algorithm:
     Given an input c_1...c_n where each c_i is a digit,
     if we had the solution for c_1...c_{n-1}, let's say [R_1, ..., R_m],
     then we could build the solution as [R_1c_{n-1}, ..., R_mc_{n-1}
*/
class Solution {
public:
  vector<string> letterCombinations(string digits) {
    unordered_map<char, vector<char>> decodings = {
      {'2', {'a', 'b', 'c'}},
      {'3', {'d', 'e', 'f'}},
      {'4', {'g', 'h', 'i'}},
      {'5', {'j', 'k', 'l'}},
      {'6', {'m', 'n', 'o'}},
      {'7', {'p', 'q', 'r', 's'}},
      {'8', {'t', 'u', 'v'}},
      {'9', {'w', 'x', 'y', 'z'}}
    };
    
    vector<string> result;
    int num_combinations;
    int last_ending_index;
    
    if (!digits.empty()) {
      result.push_back("");
      
      for (char digit : digits) {
        num_combinations = result.size();
        vector<char>& endings = decodings[digit];
        last_ending_index = endings.size() - 1;
        
        for (int i = 0; i < num_combinations; ++i) {
          for (int j = 0; j < last_ending_index; ++j)
            result.push_back(result[i] + endings[j]);
            
          result[i] += endings[last_ending_index];
        }
      }
    }

    return result;
  }
};
