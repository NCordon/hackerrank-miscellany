// https://www.hackerrank.com/challenges/journey-to-the-moon/problem
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
  vector<list<long>> adjacencies;
  long num_nodes;
  
  long GetComponentSize(long node, vector<bool>& visited) {
    long result = 1;
    visited[node] = true;
    
    for (long child : adjacencies[node]) {
      if (!visited[child])
        result += GetComponentSize(child, visited);
    }
    
    return result;
  }
  
public:
  Graph(long num_nodes) {
    this->num_nodes = num_nodes;
    adjacencies.resize(num_nodes);
  }
  
  void AddEdge(pair<long, long> edge) {
    adjacencies[edge.first].push_back(edge.second);
    adjacencies[edge.second].push_back(edge.first);
  }
  
  vector<long> ConnectedComponentsSize(){
    vector<bool> visited(num_nodes, false);
    vector<long> result;
    
    for (long i = 0; i < num_nodes; i++) {
      if (!visited[i])
        result.push_back(GetComponentSize(i, visited));
    }
    
    return result;
  }
};


long AstronautPairs(long num_astronauts, vector<pair<long, long> > country_pairs) {
  Graph countries(num_astronauts);
  
  for (auto country_pair : country_pairs)
    countries.AddEdge(country_pair);
  
  vector<long> component_sizes = countries.ConnectedComponentsSize();
  long result = num_astronauts * (num_astronauts - 1) / 2;
  
  for(long component_size : component_sizes)
    result -= component_size * (component_size - 1) / 2;
  
  return result;
}

int main() {
  int N, P;
  cin >> N >> P;
  vector<pair<long, long> > country_pairs(P);
  
  for (int i = 0; i < P; i++) {
    cin >> country_pairs[i].first >> country_pairs[i].second;
  }
  
  cout << AstronautPairs(N, country_pairs) << endl;
  
  return 0;
}
