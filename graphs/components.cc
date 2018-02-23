// https://www.hackerrank.com/challenges/components-in-graph/problem
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

Graph MinIsomorphicGraph(vector<pair<long, long> > edges) {
  unordered_map<long, long> edge_map;
  long next_map = 0;
  
  for (auto& e : edges) {
    if (edge_map.count(e.first) == 0) {
      edge_map[e.first] = next_map;
      next_map++;
    }
    
    e.first = edge_map[e.first];
    
    if (edge_map.count(e.second) == 0) {
      edge_map[e.second] = next_map;
      next_map++;
    }
    
    e.second = edge_map[e.second];
  }
  
  Graph result(next_map);

  for (auto e : edges) {
    result.AddEdge(e);
  }
  
  return result;
}

int main() {
  long num_edges;
  cin >> num_edges;
  vector<pair<long, long>> edges(num_edges);
  long min_component = numeric_limits<long>::max();
  long max_component = numeric_limits<long>::min();

  
  for (long i = 0; i < num_edges; i++) {
    cin >> edges[i].first >> edges[i].second;
  }
  
  Graph my_graph = MinIsomorphicGraph(edges);
  vector<long> component_sizes = my_graph.ConnectedComponentsSize();
  
  for (long size : component_sizes) {
    if (size > 1)
      min_component = min(min_component, size);
    
    max_component = max(max_component, size);
  }
  
  cout << min_component << " " << max_component << endl;
}
