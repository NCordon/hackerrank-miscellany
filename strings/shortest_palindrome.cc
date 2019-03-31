// https://leetcode.com/problems/shortest-palindrome
// O(n) solution where n is the length of the string
// Solution based on Rabin-Karp

class Solution {
public:
  bool check_palindrome(string& s, int k) {
    int i = 0;
    int j = k;
    bool palindrome = true;
    
    while (i < j && palindrome) {
      palindrome = s[i] == s[j];
      ++i;
      --j;
    }
    
    return palindrome;
  }
  
  string shortestPalindrome(string s) {
    int p = 18181;
    int m = 26;
    int m_inv = 1;
    int hash_inv = 0;
    int hash = 0;
    int pow = 1;
    int last_index = s.size() - 1;
    int k = 0;
    int current;
    bool palindrome;
    string to_append;
    
    for (int i = 0; i < p - 2; ++i)
      m_inv = (m_inv * m) % p;
    
    for (int i = 0; i < s.size(); ++i) {
      current = s[i] - 'a' + 1;
      hash = (hash + ((pow * current) % p)) % p;
      current = s[last_index - i] - 'a' + 1;
      hash_inv = (hash_inv + ((pow * current) % p)) % p;
      pow = (pow * m) % p;
    }
    
    k = last_index;
    palindrome = (hash == hash_inv && check_palindrome(s, k));
      
    for(int i = last_index; i > 0 && !palindrome; --i) {
      palindrome = true; 
      pow = (pow * m_inv) % p;
      current = s[i] - 'a' + 1;
      hash = ((hash - ((pow * current) % p)) + p) % p;
      hash_inv = (hash_inv - current + p) % p;
      hash_inv = (hash_inv * m_inv) % p;
      k = i - 1;
      palindrome = (hash == hash_inv && check_palindrome(s, k));
    }
    
    to_append = s.substr(k + 1, string::npos);
    reverse(to_append.begin(), to_append.end());
    
    return to_append + s;
  }
};
