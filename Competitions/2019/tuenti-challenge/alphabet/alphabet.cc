#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool fill_path(list<char>& path,
               unordered_map<char, unordered_set<char>>& ordering,
               char next,
               int target_length) {
  bool result = false;
  
  if (path.size() == target_length)
    result = true;
  else {
    for (char child : ordering[next]) {
      if (!result) {
        path.push_back(child);
        result = fill_path(path, ordering, child, target_length);
        
        if (!result)
          path.pop_back();
      }
    }
  }

  return result;
}

int main() {
  int N;
  int M;
  int num_seen;
  string current;
  string previous;
  bool relation_found;
  char next;
  bool ambiguous;
  cin >> N;

  for (int i = 1; i <= N; ++i) {
    cin >> M;
    vector<string> words(M);
    ambiguous = false;
    
    for (int j = 0; j < M; ++j)
      cin >> words[j];

    unordered_set<char> seen;
    unordered_map<char, unordered_set<char>> ordering;
    list<char> path;
    
    for (int j = 0; j < M; ++j)
      for (char c : words[j])
        seen.insert(c);
      
    for (int j = 1; j < M; ++j) {
      current = words[j];
      previous = words[j - 1];
      relation_found = false;
      
      for (int k = 0; k < min(current.size(), previous.size()) && !relation_found; ++k) {
        if (current[k] != previous[k]) {
          relation_found = true;
          ordering[previous[k]].insert(current[k]);
        }
      }
    }
    
    num_seen = seen.size();
    cout << "Case #" << i << ":";
    
    for (auto children : ordering)
      for (char elem : children.second)
        seen.erase(elem);

    if (seen.size() != 1) {
      ambiguous = true;
    } else {
      for (char elem : seen)
        next = elem;

      path.push_back(next);
      ambiguous = !fill_path(path, ordering, next, num_seen);
    }
    
    if (ambiguous)
      cout << " " << "AMBIGUOUS";
    else
      for (char letter : path)
        cout << " " << letter;
    
    cout << endl;
  }
}
