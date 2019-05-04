#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef char Byte;
typedef unordered_map<Byte, unordered_map<int, string>> Combinations;
typedef vector<Byte> Hash;

struct AlteredHash {
  Hash first;
  Hash second;
  int first_length;
};

// Hash function
Hash weak_hash(string text) {
  vector<Byte> result(16, (Byte) 0);

  for (int i = 0; i < text.size(); ++i)
    result[i % 16] += text[i];

  return result;
}

// Method to read the unaltered text
Hash original_hash() {
  string text;
  string line;
  int N;
  cin >> N;
  getchar();
    
  for (int l = 0; l < N; ++l) {
    getline(cin, line);
    text += line;
  }

  return weak_hash(text);
}

// Method to read the altered text
// Returns the hash of the first part, finishing in --- and
// the hash of the second, starting in ..., as well as the length
// of the first part of the text
AlteredHash altered_hash() {
  AlteredHash result;
  string text;
  string line;
  string sep = "------";
  int N;
  cin >> N;
  getchar();

  for (int l = 0; l < N; ++l) {
    getline(cin, line);

    int pos = line.find(sep);
    
    if (pos != string::npos) {
      text += line.substr(0, pos) + "---";
      result.first = weak_hash(text);
      result.first_length = text.size();
      text.clear();
      text += "---" + line.substr(pos + sep.size());
    } else {
      text += line;
    }
  }

  result.second = weak_hash(text);

  return result;
}

void generate_combinations(Combinations& combinations, Byte x, string& current, int length) {
  if (length < 4) {
    for (Byte a = '0'; a <= 'z'; ++a) {
      x += a;
      current.push_back(a);

      if (combinations[x].count(length + 1) == 0)
        combinations[x][length + 1] = current;

      generate_combinations(combinations, x, current, length + 1);
      
      current.pop_back();
      x -= a;
    }
  }
}

string print_info(Hash& original, AlteredHash& altered, Combinations& combinations) {
  Hash& first = altered.first;
  Hash& second = altered.second;
  int first_length = altered.first_length;
  int shift;
  int offset = (16 - first_length % 16) % 16;
  Hash current;
  string combination;
  string result;
  bool solution = false;
  int comb_length;
  Byte target;
  
  for (int length = 0; length <= 64 && !solution; ++length) {
    shift = first_length + length;
    result = string(length, 0);
    current = first;

    for (int i = 0; i < 16; ++i)
      current[(i + shift) % 16] += second[i];

    solution = true;
    
    for (int i = 0; i < 16 && solution; ++i) {
      target = original[i] - current[i];

      // Compute the length of the combination needed
      comb_length = shift / 16 - first_length / 16;
      
      if (i < shift % 16)
        ++comb_length;
      if (i < first_length % 16)
        --comb_length;

      // If that combination exists for the target value,
      // write its letters to the result
      if (combinations[target].count(comb_length) > 0) {
        combination = combinations[target][comb_length];
        target = 0;

        for (int j = 0; j < comb_length; ++j)
          result[(i + offset) % 16 + j * 16] = combination[j];
      }
      
      solution = (target == 0);
    }

    // Check that all the characters in the solution are valid
    // characters (we could still be using (char) 0, for example)
    if (solution)
      for (int i = 0; i < result.size() && solution; ++i)
        solution = result[i] >= '0' && result[i] <= 'z';
  }

  return result;
}

/*
  Idea: 
  It is easy to show that there is a solution with length 64, since
  summing 4 letters in ['0', 'z'] we can get all the numbers in [0, 255]

  Therefore the solution must be shorter than 64 characters.
  For each length between 0 and 64, compute the number of characters
  we should use, the sum we have between the first hash part for the altered
  text and the second hash part for the altered text, and if there is a way
  of getting the difference between the sum we currently have for that position
  i in [0,16[ and the length of the combination we must use, write those characters
  in the resulting string.

  The problem is not hard. What is hard is to correctly track all the shifts ;___
  and all the boilerplate needed to code it
 */
int main() {
  int C;
  string combination;
  Combinations combinations;
  cin >> C;
  
  generate_combinations(combinations, 0, combination, 0);

  for (int i = 1; i <= C; ++i) {    
    Hash original = original_hash();
    AlteredHash altered = altered_hash();
    
    cout << "Case #" << i << ": " << print_info(original, altered, combinations) << endl;
  }
}
