// https://www.hackerrank.com/challenges/magic-square-forming/problem
#include <bits/stdc++.h>
using namespace std;

/* Idea:
Only magic squares in R³ x R³ are:

[4 9 2]
[3 5 7]
[8 1 6]

[2 9 4]
[7 5 3]
[6 1 8]

and its possible rotations, where a right rotation
keeps fixed the center of the matrix
*/
void rotRight(vector<vector<int> >& magic_sq){
  int old_rcorner = magic_sq[2][2];
  int old_midbottom = magic_sq[2][1];
  magic_sq[2][2] = magic_sq[0][2];
  magic_sq[0][2] = magic_sq[0][0];
  magic_sq[0][0] = magic_sq[2][0];
  magic_sq[2][1] = magic_sq[1][2];
  magic_sq[1][2] = magic_sq[0][1];
  magic_sq[0][1] = magic_sq[1][0];
  magic_sq[1][0] = old_midbottom;
  magic_sq[2][0] = old_rcorner;
}

int main() {
  vector<vector<int> > magic{{4, 9, 2}, {3, 5, 7}, {8, 1, 6}};
  vector<vector<int> > t_magic{{2, 9, 4}, {7, 5, 3}, {6, 1, 8}};
  vector<int> normal_diff(4, 0);
  vector<int> t_diff(4, 0);
  int current;
  
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      cin >> current;
      
      for(int rot = 0; rot < 4; rot++){
        normal_diff[rot] += abs(current - magic[i][j]);
        t_diff[rot] += abs(current - t_magic[i][j]);
        
        rotRight(magic);
        rotRight(t_magic);
      }
    }
  }
  
  cout << min(*min_element(normal_diff.begin(), normal_diff.end()), 
              *min_element(t_diff.begin(), t_diff.end()));
}
