#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
typedef unordered_map<string, vector<string>> Edges;

vector<string> split(string& to_split, string to_search) {
  vector<string> result;
  bool end_reached = false;
  int pos;
  int split_pos = -1;
  
  while (!end_reached) {
    pos = split_pos + 1;
    split_pos = to_split.find(to_search, pos);
    
    if (split_pos == -1) {
      split_pos = to_split.size();
      end_reached = true;
    }
    
    result.push_back(to_split.substr(pos, split_pos - pos));
  }

  return result;
}

int num_ways(Edges& edges, string& source) {
  int result = 0;
  
  if (source == "New Earth")
    result = 1;
  else {
    for (auto& target : edges[source])
      result += num_ways(edges, target);
  }

  return result;
}

int main() {
  int C;
  int num_planets;
  char discard;
  string planets;
  string current;
  string forward;
  string source = "Galactica";
  cin >> C;

  for (int i = 1; i <= C; ++i) {
    // When reading win cin, we have to discard the trailing newline character
    cin >> num_planets;
    discard = getchar();
    Edges edges;
    
    for (int p = 1; p <= num_planets; ++p) {
      getline (cin, planets);

      vector<string> split_planets = split(planets, ":");
      current = split_planets[0];
      edges[current] = split(split_planets[1], ",");
    }

    // This recursively backtracks using a depth-first scheme with Galactica as source
    cout << "Case #" << i << ": " << num_ways(edges, source)  << endl;
  }
}
