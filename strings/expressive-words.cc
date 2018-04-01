// https://leetcode.com/contest/weekly-contest-78/problems/expressive-words/
class Solution {
  struct ExtendedChar {
    char current;
    int count;
    
    ExtendedChar(char current, int count) {
      this->current = current;
      this->count = count;
    }
  };
  
public:
  int expressiveWords(string S, vector<string>& words) {
    int i, j, k;
    vector<ExtendedChar> parsed;
    int result = 0;
    bool stretchy;
    int count;
    i = 0;
    
    while (i < S.size()) {
      j = i + 1;
      
      while (S[j] == S[i])
        ++j;
      
      parsed.push_back(ExtendedChar(S[i], j - i));
      
      i = j;
    }

    for (string& word : words) {
      stretchy = true;
      i = 0;
      count = 0;
      k = 0;
      
      while(k < parsed.size() && stretchy && i < word.size()) {
        if(parsed[k].current == word[i]) {
          j = i + 1;
          
          while (word[j] == word[i])
            ++j;
          
          if (!(parsed[k].count == (j - i) || 
               (parsed[k].count >= 3 && 
                parsed[k].count >= (j-i))))
            stretchy = false;

          i = j;
        } else {
          stretchy = false;
        }
       
       ++k;
      }
      
      stretchy = stretchy && (k == parsed.size());
      
      if (stretchy)
        ++result;
    }
    
    return result;
  }
};
