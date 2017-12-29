// https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach
#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

class Graph{
private:
  vector<vector<int>> adjacencies;
  int n;
public:
  Graph(int n){
    this->n = n;
    this->adjacencies = vector<vector<int>>(n, vector<int>());
  }

  void add_edge(int u, int v){
    adjacencies[u].push_back(v);
    adjacencies[v].push_back(u);
  }

  vector<int> shortest_reach(int start){
    // Breadth first search guarantees that if we can reach a node 
    // from start it would be using minimum distance
    queue<int> to_explore;
    vector<int> distances(n, 0);
    vector<bool> visited(n, false);
    visited[start] = true;
    int current_node;
    to_explore.push(start);
    
    while(!to_explore.empty()){
      current_node = to_explore.front();
      to_explore.pop();
      
      for(int node:adjacencies[current_node]){
        if(!visited[node]){
          to_explore.push(node);
          visited[node] = true;
          distances[node] = distances[current_node] + 1;
        }
      }
    }
    
    for(int i = 0; i < distances.size(); i++)
      if(distances[i] == 0)
        distances[i] = -1;
      else
        distances[i] *= 6;
    
    return distances;
  }
};

int main() {
  int queries;
  cin >> queries;
        
  for (int t = 0; t < queries; t++){
    int n, m;
    cin >> n;
    // Create a graph of size n where each edge weight is 6: 
    Graph graph(n);
    cin >> m;
    // read and set edges
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      // add each edge to the graph
      graph.add_edge(u, v);
    }
    int startId;
    cin >> startId;
    startId--;
    // Find shortest reach from node s
    vector<int> distances = graph.shortest_reach(startId);

    for (int i = 0; i < distances.size(); i++){
      if (i != startId){
        cout << distances[i] << " ";
      }
    }
    cout << endl;
  }
  
  return 0;
}
