// https://leetcode.com/problems/regular-expression-matching/description/

struct CharRegexp {
    char c;
    bool asterisked;
    
    CharRegexp(char c, bool asterisked) {
        this->c = c;
        this->asterisked = asterisked;
    }
};

struct Regexp : public vector<CharRegexp> {
    
    Regexp(string r) {
        int i = 0;
        while (i < r.size()) {
            if (i + 1 < r.size() && r[i + 1] == '*') {
                push_back(CharRegexp(r[i], true));
                i += 2;
            } else {
                push_back(CharRegexp(r[i], false));
                ++i;
            }
        }
    }
};


class Solution {
public:
    bool isMatch(string s, string p) {
        Regexp regexp(p);
        // match[i][j] indicates whether we can match s[i...] with regexp[j...]
        vector<vector<bool> > match(s.size() + 1, vector<bool>(regexp.size() + 1, false));
        
        // We can match empty string with empty regexp
        match[s.size()][regexp.size()] = true;
        
        bool can_match = true;
        
        // Compute if we can match emtpy string with regexp[j...]
        for (int j = regexp.size() - 1; j >= 0; --j) {
            if (!regexp[j].asterisked)
                can_match = false;
            
            match[s.size()][j] = can_match;
        }
        
        for (int i = s.size() - 1; i >= 0; --i) {
            for (int j = regexp.size() - 1; j >= 0; --j) {
                if (regexp[j].asterisked) { 
                    match[i][j]   = ((s[i] == regexp[j].c || '.' == regexp[j].c) && 
                                    match[i + 1][j]) ||
                                    match[i][j + 1];
                }
                else {
                    match[i][j] = (s[i] == regexp[j].c || '.' == regexp[j].c) && 
                                  match[i + 1][j + 1];
                }
            }
        }
        
        return match[0][0];        
    }
};


