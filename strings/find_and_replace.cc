// https://leetcode.com/problems/find-and-replace-in-string/
// O(n) solution where n is the length of S, given the constraints
// in the problem (sources do not overlap and indexes has length
// lower than the length of S)
class Solution {
 public:
  string findReplaceString(string S, 
                           vector<int>& indexes, 
                           vector<string>& sources, 
                           vector<string>& targets) {
    vector<bool> keep(S.size(), true);
    unordered_map<int, string> replace;
    int index;
    bool can_replace;
    string source;
    string result;
      
    for (int i = 0; i < indexes.size(); ++i) {
      index = indexes[i];
      source = sources[i];
      can_replace = true;
      can_replace = (S.size() - index) >= source.size();
          
      for (int j = 0; j < source.size() && can_replace; ++j)
        can_replace = S[j + index] == source[j];
          
      if (can_replace) {
        replace[index] = targets[i];
            
        for (int j = 0; j < source.size(); ++j)
          keep[j + index] = false;
      }
    }
      
    for (int i = 0; i < S.size(); ++i) {
      if (keep[i])
        result += S[i];
      else if (replace.count(i))
        result += replace[i];
    }
      
    return result;
  }
};
