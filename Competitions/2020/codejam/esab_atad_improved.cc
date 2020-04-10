#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct Positions {
  int changing = 1;
  int non_changing = 1;
};

void complement(string& s) {
  for (int i = 0; i < s.size(); ++i)
      s[i] = (s[i] == '0') ? '1' : '0';
}

void reverse(string& s) {
  reverse(s.begin(), s.end());
}

void computeCurrentState(string& s, Positions p) {
  int pos = p.changing;
  int pos_non = p.non_changing;
  char c, c_non;
  
  cout << pos_non << endl;
  cin >> c_non;
  cout << pos << endl;
  cin >> c;

  if (s[pos - 1] != c && s[pos_non - 1] == c_non) {
    reverse(s);
  } else if (s[pos - 1] == c && s[pos_non - 1] != c_non) {
    reverse(s); 
    complement(s);
  } else if (s[pos - 1] != c && s[pos_non - 1] != c_non) {
    complement(s);
  }
}

int main() {
  int t, b;
  // read number of cases and number of bits in each test case
  cin >> t >> b;

  for (int i = 1; i <= t; ++i) {
    char c;
    // initialize the result
    string result(b, '0');
    string response;
    Positions pos;
    int p = 1;
    int limit = p + 5;

    while (p <= b / 2) {
      while (p < limit && p <= b / 2) {
        cout << p << endl;
        cin >> c;
        result[p - 1] = c;
        cout << b - p + 1 << endl;
        cin >> c;
        result[b - p] = c;

        if (result[p - 1] != result[b - p])
          pos.changing = p;
        else
          pos.non_changing = p;

        ++p;
      }
      limit = p + 4;

      if (p <= b / 2)
        computeCurrentState(result, pos);
    }
    cout << result << endl;
    cin >> response;

    if (response == "N")
      return -1;
  }
}
