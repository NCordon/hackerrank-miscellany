#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <limits>

#define inf numeric_limits<int>::max()

using namespace std;


vector< int > solve_dijkstra(int start, vector< vector<int> > &weight, int &num_nodes){  
  vector<int> distance(num_nodes, inf);
  vector<bool> visited(num_nodes, false);
  priority_queue< pair<int,int> > to_visit;
  int u, dist;
  
  distance[start] = 0;
  to_visit.push(make_pair(start, 0));
  
  while(!to_visit.empty()){
    u = to_visit.top().first;
    dist = to_visit.top().second;
    to_visit.pop();
    visited[u] = true;

    for(int v=0; v < num_nodes; v++){

      if(!visited[v] and (distance[v] > (distance[u] + weight[v][u]) )){
        distance[v] = (distance[u] + weight[v][u]);
        to_visit.push( make_pair(v, distance[v]) );
      }
    }
  }

  return distance;
}


int main(){
  int num_cases,
    num_nodes,
    num_edges,
    u, v, dist,
    start;
  cin >> num_cases;

  // Read a graph and calculate minimum distances to each node
  for (int i=0; i<num_cases; i++){
    cin >> num_nodes;
    cin >> num_edges;

    vector< vector<int> > weight(num_nodes, vector<int>(num_nodes, inf));
    vector<int> distance;
    
    for(int j=0; j<num_edges; j++){
      // Read pair of nodes and distance between them
      cin >> u; u--;
      cin >> v; v--;
      cin >> dist;

      if (weight[u][v] > dist)
        weight[u][v] = weight[v][u] = dist;      
    }
    
    cin >> start; start--;
    distance = solve_dijkstra(start, weight, num_nodes);

    for (int d : distance)
      if(d!=0)
        cout << (d==inf ? -1 : d) << " ";
  }
}
