//https://www.hackerrank.com/contests/womens-codesprint-2/challenges/stone-division-2/
#include <bits/stdc++.h>

using namespace std;
typedef unordered_map<long, long>::iterator hash_it;
 

long compute_divisions(long n, vector<long>& s, 
                       unordered_map<long, long>& stored_divisions) {
  long maximum = 0;
  // current splits
  long current;
  long sub_divisions;
  
  // For each possible value of s
  for(long s_i : s){
    // If divisor of n
    if(n != s_i){
      if(n%s_i == 0){
        hash_it it = stored_divisions.find(s_i);
        
        // If we have previously calculated the number of necessary splits, use them
        // else, compute them
        if(it != stored_divisions.end())
          sub_divisions = stored_divisions[s_i];
        else
          sub_divisions = compute_divisions(s_i, s, stored_divisions);
        
        /*
        If we called M(n) the maximum number of splits for n,
        with vector s = {s_1,..., s_n}, we have:

        M(n) = 1 + max(n/s_1 * M(s_1),..., n/s_n * M(s_n))
        */
        current = 1 + n/s_i * sub_divisions;
        
        if(current > maximum)
          maximum = current;
      }
    }
  }
  
  stored_divisions[n] = maximum;
  return maximum;
}

// Wrapper for the solver
long stone_division(long n, vector<long>& s){
  // We need to keep track of the already computed cases
  unordered_map<long, long> stored_divisions;
  
  return compute_divisions(n, s, stored_divisions);
}

int main(){
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        long n;
        int m;
        cin >> n >> m;
        vector<long> s(m);
      
        for(int s_i = 0; s_i < m; s_i++){
           cin >> s[s_i];
        }
        // Sort in decreasing order
        sort(s.begin(), s.end(), greater<int>());
      
        long result = stone_division(n, s);
        cout << result << endl;
    }
    return 0;
}
