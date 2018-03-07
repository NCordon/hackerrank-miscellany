// https://www.hackerrank.com/challenges/xor-quadruples/
#include <bits/stdc++.h>
using namespace std;
typedef unordered_map<int,int>::iterator hash_it;

/* Idea:
Posibilities with 
  1 <= a <= A
  1 <= b <= B
  1 <= c <= C
  1 <= d <= D
are given by:
\sum_{a = 1}^A \sum_{b = a}^B \sum_{c = b}^C \sum_{d = c}^D 1 =
\sum_{a = 1}^A \sum_{b = a}^B {(C-b+1)*(D+1) - (C+b)*(C-b+1)/2}

Fixed a c, possibilities for c^d are given by d = c...D
So to calculate possibilities for c^d we start by calculating 
possibilities for C^d, and then summing then to (C-1)^d and so on...

For a^b (a <= b) we need c^d which holds b <= c <= d and we have 
previously computed the possibilities for c <= d
*/
int main(){
  int A;
  int B;
  int C;
  int D;
  cin >> A >> B >> C >> D;
  long long valid_xors = 0;
  int current;
  
  // Order bounds from lowest to greatest
  vector<int> bounds{A,B,C,D};
  sort(bounds.begin(), bounds.end());
  
  // A <= B <= C <= D
  A = bounds[0];
  B = bounds[1];
  C = bounds[2];
  D = bounds[3];
  
  unordered_map<int,int> explored_xors;
  
  for(int c = C; c >= 1; c--){
    for(int d = c; d <= D; d++){
      current = c ^ d;
      hash_it value_pos = explored_xors.find(current);

      if(value_pos != explored_xors.end())
          value_pos->second = value_pos->second + 1;
        else
          explored_xors[current] = 1;
    }
    if(c <= B){
      for(int a = 1; a <= min(c, A); a++){
        valid_xors += (C - c + 1)*(D + 1) - ((C + c)*(C - c + 1))/2;
      
        hash_it value_pos = explored_xors.find(a ^ c);
      
        if(value_pos != explored_xors.end())
          valid_xors -= value_pos->second;
      }
    }
  }
  
  cout << valid_xors << endl;
  return 0;
}
