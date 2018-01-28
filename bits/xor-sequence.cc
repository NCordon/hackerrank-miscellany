// https://www.hackerrank.com/challenges/xor-se/problem
#include <bits/stdc++.h>
using namespace std;

/*
Solution for this problem is based on the fact
that if we have an array with running xor for A,
namely XOR, answer will be XOR[R] ^ XOR[L-1]. 
e.g. 3^0^4 = (0^1)^(0^1^3^0^4)

Due to space constraints we cannot store whole XOR,
but we can come up with a formula that gives us 
XOR[until] with arbitrary 'until' position.

XOR = [0,1,2,2,6,7,0,0,8,9,2,2,14,15,0,0,16,17,2,2,22,23,0,0,...]
*/
long long running_xor(long long until){
  int mod;
  long long result;
  
  if(until < 0)
    result = 0;
  else{
    mod = until % 8;
    switch(mod){
      case 0:
      case 1:
        result = until;
        break;
      case 2:
      case 3:
        result = 2;
        break;
      case 4:
      case 5:
        result = until + 2;
        break;
      default:
        result = 0;
    }
  }
  
  return result;
}

int main(){
  long long Q;
  cin >> Q;
  
  // Test cases:
  //  2 4
  for(long long a0 = 0; a0 < Q; a0++){
    long long L;
    long long R;
    cin >> L >> R;
    cout << (running_xor(R) ^ running_xor(L - 1)) << endl;
  }
  
  return 0;
}
