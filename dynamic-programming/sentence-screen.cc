// https://leetcode.com/problems/sentence-screen-fitting
/* Considering number of words <= 100 constant, O(rows) solution algorithmically

 Idea: for each row, if we ended previous one without completing a whole sentence,
       we look for the last word we could fill in the gap
       If we have been able to fill the rest of the sentence, we look for how many
       complete sentences we would be able to fit into the remaining row, and try to
       start a new one
*/

class Solution {
public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    vector<int> required(sentence.size() + 1);
    required[0] = 0;
    int n = sentence.size();
    int j = 0;
    int result = 0;
    int last;
    int slides;
    int old_required;
      
    for (int i = 1; i <= n; ++i)
      required[i] = sentence[i - 1].size() + required[i - 1] + 1;
      
    for (int i = 0; i < rows; ++i) {
      old_required = required[j];
      j = upper_bound(required.begin() + j, required.end(), 
                      cols + 1 + old_required) - required.begin();
      --j;
        
      if (j == n) {
        ++result;
        last = required[j] - 1 - old_required;
        slides = (cols - last) / required[n];
        last += slides * required[n];
        result += slides;
        j = upper_bound(required.begin(), required.end(), 
                        cols - last) - required.begin();
        --j;
      }
    }
      
    return result;      
  }
};
