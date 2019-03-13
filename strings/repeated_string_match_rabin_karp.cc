// https://leetcode.com/problems/repeated-string-match/solution/
// O(n + m) solution where n is the length of A and m is the
// length of B using Rabin Karp
class Solution {
public:
  bool check(int i, string& A, string& B) {
    bool substring = true;
    int n = A.size();
    
    for (int j = 0; j < B.size() && substring; ++ j) {
      substring = A[(i + j) % n] == B[j];
    }
  
    return substring;
  }
  
  int repeatedStringMatch(string A, string B) {
    int p = 13;
    int pinv = 1;
    int h = 1;
    const int M = 18181;
    // p and M are co-primes
    int ahash = 0;
    int bhash = 0;
    int n = A.size();
    int last_a = (B.size() - 1) % n;
    int repetitions = 0;
    bool found = false;
    int j;
    
    for (int i = 0; i < M - 2; ++i)
      pinv = (pinv * p) % M;
    
    for (int i = 0; i < B.size(); ++i) {
      j = i % n;
      
      if (j == 0)
        ++repetitions;
      
      bhash = bhash + ((h * (int) B[i]) % M);
      bhash %= M;      
      ahash = ahash + ((h * (int) A[j]) % M);
      ahash %= M;
      
      if (i < (B.size() - 1))
        h = (h * p) % M;
    }
    
    found = ahash == bhash && check(0, A, B);
    
    for (int i = 0; i < n - 1 && !found; ++i) {
      j = (last_a + i + 1) % n;
      
      if (j == 0)
        ++repetitions;

      ahash = (ahash - A[i]) * pinv;
      ahash %= M;
      ahash = ahash + ((A[j] * h) % M);
      ahash %= M;
      
      found = ahash == bhash && check(i + 1, A, B);
    }
    
    if (!found)
      repetitions = -1;
    
    return repetitions;
  } 
};
