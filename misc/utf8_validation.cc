// https://leetcode.com/problems/utf-8-validation/
class Solution {
public:
  bool validUtf8(vector<int>& data) {
    int continuation = 0;
    int byte;
    bool valid = true;
    
    for (int i = 0; i < data.size() && valid; ++i) {
      byte = data[i];

      if (continuation > 0) {
        --continuation;
        valid = (byte >> 6) == 2;
      } else {        
        if ((byte >> 7) == 0)
          valid = true;
        else if ((byte >> 5) == 6)
          continuation = 1;
        else if ((byte >> 4) == 14)
          continuation = 2;
        else if ((byte >> 3) == 30)
          continuation = 3;
        else
          valid = false;
      }
    }
    
    return valid && continuation == 0;
  }
};
