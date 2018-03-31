// https://leetcode.com/problems/remove-duplicate-letters
// O(n² log n) solution
class Solution {
public:
  string removeDuplicateLetters(string s) {
    int last_used = -1;
    vector<int> counts(26, 0);
    vector<bool> used(26, false);
    string result;
    
    // Fill counts vector
    for (int i = 0; i < s.size(); ++i)
      ++counts[s[i] - 'a'];

    
    for (int i = 0; i < s.size(); ++i) {
      --counts[s[i] - 'a'];
      
      if (counts[s[i] - 'a'] == 0 && !used[s[i] - 'a']) {
        priority_queue<pair<char, int>, 
                       vector<pair<char, int>>,
                       greater<pair<char, int>> > min_heap;
        
        for (int j = last_used + 1; j <= i; ++j)
          min_heap.push({s[j], j});

        while (!min_heap.empty()) {
          auto current = min_heap.top();

          if (current.second > last_used && 
              current.first <= s[i] &&
              !used[current.first - 'a']) {
            result += current.first;
            last_used = current.second;
            used[current.first - 'a'] = true;
          }
          min_heap.pop();
        }
      }
    }
    
    return result;
  }
};
