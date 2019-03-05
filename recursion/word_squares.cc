// https://leetcode.com/problems/word-squares/
// I ended up writing a solution pretty similar to
// https://leetcode.com/problems/word-squares/discuss/91344/Short-PythonC%2B%2B-solution
// unintendedly of course, I did not look at the solutions before actually solving it
// O(n^L) solution where n is the number of words and L is the length of all words
class Solution {
public:
  void fill_with_prefix(int i, 
                        vector<string>& current, 
                        vector<vector<string>>& solution,
                        unordered_map<string, vector<string>>& prefixed_word) {
    string prefix;

    if (i < current.size()) {
      for (int j = 0; j < i; ++j) {
        prefix += current[j][i];
      }

      for (string& word : prefixed_word[prefix]) {
        current[i] = word;
        fill_with_prefix(i + 1, current, solution, prefixed_word);
      }
    } else {
      solution.push_back(current);
    }
  }

  vector<vector<string>> wordSquares(vector<string>& words) {
    unordered_map<string, vector<string>> prefixed_word;
    vector<vector<string>> solution;
    vector<string> current;
    string prefix;
    int length;

    for (string& word : words) {
      prefix = word;
      length = word.size();
      
      for (int i = 0; i < length; ++i) {
        prefix.pop_back();
        prefixed_word[prefix].push_back(word);
      }
    }
    
    current.resize(length);
    
    fill_with_prefix(0, current, solution, prefixed_word);
    return solution;
  }
};
