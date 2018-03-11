// https://leetcode.com/problems/one-edit-distance

class Solution {
  bool EqualWithInsert(string s, string t){
    bool distinct_found = false;
    bool one_edit = true;
    
    for (int i = 0; i < s.size() && one_edit; i++) {
      if (distinct_found) {
        if (s[i] != t[i + 1])
          one_edit = false;
      } else if (s[i] != t[i]) {
        if(!distinct_found) {
          distinct_found = true;
          --i;
        }
      }
    }
    
    return one_edit;
  }
  
  
public:
  bool isOneEditDistance(string s, string t) {
    bool distinct_found = false;
    bool one_edit = false;

    // Look for a replacement
    if (s.size() == t.size()) {
      one_edit = true;

      for (int i = 0; i < s.size() && one_edit; ++i){
        if (s[i] != t[i])
          if (!distinct_found)
            distinct_found = true;
          else
            one_edit = false;
      }

      if(!distinct_found)
        one_edit = false;

    // Look for an insertion
    } else if (s.size() == t.size() - 1) {
      one_edit = EqualWithInsert(s, t);
    } else if (s.size() - 1 == t.size()) {
      one_edit = EqualWithInsert(t, s);
    }

    return one_edit;
  }
};
