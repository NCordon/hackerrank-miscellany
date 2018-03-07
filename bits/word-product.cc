// https://leetcode.com/problems/maximum-product-of-word-lengths/description/

class Solution {
public:
  int maxProduct(vector<string>& words) {
    vector<int> word_mask (words.size(), 0);
    bool repeated_letter;
    int max_length = 0;
    int current_length;
        
    // Preprocess each word
    for (int i = 0; i < words.size(); ++i)
      for (char letter : words[i])
        word_mask[i] |= 1 << (letter - 'a');
        
        
    for (int i = 0; i < words.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        repeated_letter = ((word_mask[i] & word_mask[j]) != 0);
                
        if (!repeated_letter && (words[i].size() * words[j].size()) > max_length) {
          max_length = words[i].size() * words[j].size();
        }
      }
    }
        
    return max_length;
  }
};
