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
  int changing = 0;
  int non_changing = 0;
};

Positions identifyingPos(string& chunk) {
  Positions pos;

  for (int i = 0; i < chunk.size() / 2; ++i)
    if (chunk[i] != chunk[chunk.size() - 1 - i])
      pos.changing = i;
    else
      pos.non_changing = i;

  return pos;
}


class Operation {
public:
  virtual void apply(string& s) {}
};

class Complement : public Operation {
public:
  void apply(string& s) override {
    for (int i = 0; i < s.size(); ++i)
      s[i] = (s[i] == '0') ? '1' : '0';
  }
};

class Reverse : public Operation {
public:
  void apply(string& s) override {
    reverse(s.begin(), s.end());
  }
};

class ReverseComplement : public Operation {
public:
  void apply(string & s) override {
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++i)
      s[i] = (s[i] == '0') ? '1' : '0';
  }
};

class Identity : public Operation {
public:
  void apply(string& s) override {
    return;
  }
};

Operation* computeOperation(string& s, Positions& p, int pos_offset) {
  int pos = p.changing;
  int pos_non = p.non_changing;
  char c, c_non;
 
  cout << pos_non + pos_offset + 1 << endl;
  cin >> c_non;
  cout << pos + pos_offset + 1 << endl;
  cin >> c;

  if (s[pos] != c && s[pos_non] == c_non)
    return new Reverse();
  else if (s[pos] == c && s[pos_non] != c_non)
    return new ReverseComplement();
  else if (s[pos] != c && s[pos_non] != c_non)
    return new Complement();
  else
    return new Identity();
}

void computeCurrentState(string& s, Positions p, int pos_offset) {
  Operation* op = computeOperation(s, p, pos_offset);
  op->apply(s);
}

int main() {
  int t, b;
  // read number of cases and number of bits in each test case
  cin >> t >> b;

  for (int i = 1; i <= t; ++i) {
    char c;
    string result, response;

    if (b == 10) {
      for (int p = 1; p <= b; ++p) {

        cout << p << endl;
        cin >> c;
        result += c;
      }

      cout << result << endl;
      cin >> response;

      if (response == "N")
        return -1;
    } else if (b == 20) {
      string first;

      for (int p : vector<int>({1, 2, 3, 4, 5, 16, 17, 18, 19, 20})) {
        cout << p << endl;
        cin >> c;
        first += c;
      }

      Positions pos_first = identifyingPos(first);

      string middle;

      for (int p : vector<int>({6, 7, 8, 9, 10, 11, 12, 13, 14, 15})) {
        cout << p << endl;
        cin >> c;
        middle += c;
      }

      Positions pos_middle = identifyingPos(middle);

      computeCurrentState(first, pos_first, 0);
      computeCurrentState(middle, pos_middle, 5);

      cout << first.insert(5, middle) << endl;
      cin >> response;
      if (response == "N")
        return -1;
    } else if (b == 100) {
      int num_chunks = b / 10;
      vector<string> chunks(num_chunks);
      vector<Positions> positions(num_chunks);

      for (int j = 0; j < chunks.size(); ++j) {
        vector<int> bits;

        for (int p = j * 5 + 1; p <= (j + 1) * 5; ++p)
          bits.push_back(p);

        for (int p = b - j * 5 - 4; p <= (b - j * 5); ++p)
          bits.push_back(p);

        for (int p : bits) {
          cout << p << endl;
          cin >> c;
          chunks[j] += c;
        }
        positions[j] = identifyingPos(chunks[j]);
      }

      for (int j = 0; j < 10; ++j)
        computeCurrentState(chunks[j], positions[j], 5 * j);
      

      for (int j = 1; j < 5; ++j)
       chunks[10 - j - 1].insert(5, chunks[10 - j]);

      for (int j = 6; j < 10; ++j)
       chunks[10 - j - 1].insert(5, chunks[10 - j]);

      string first = chunks[0];
      string middle = chunks[5];
      computeCurrentState(first, identifyingPos(first), 0);
      computeCurrentState(middle, identifyingPos(middle), 25);

      cout << first.insert(25, middle) << endl;
      cin >> response;
      if (response == "N")
        return -1;
    }
  }
}
