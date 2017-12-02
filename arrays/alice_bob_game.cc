// https://www.hackerrank.com/challenges/alice-and-bobs-silly-game/problem
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main(){
  int g;
  vector<int> myset;
  cin >> g;
  bool alice_turn;
  for(int a0 = 0; a0 < g; a0++){
    int n;
    cin >> n;
    vector<int> myset(n+1);
    alice_turn = true;
      
    // Fill array
    iota(myset.begin(), myset.end(), 0);
        
    for(int i = 2; i <= n; i++){
      if(myset[i] != -1){
        alice_turn = !alice_turn;
            
        for(int j = 1; j <= n/i; j++)
          myset[i * j] = -1;
      }
    }
        
    if(alice_turn)
      cout << "Bob" << endl;
    else
      cout << "Alice" << endl;      
  }
  return 0;
}

