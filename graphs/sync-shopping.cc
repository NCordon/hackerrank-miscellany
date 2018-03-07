//https://www.hackerrank.com/challenges/synchronous-shopping/problem

#include <bits/stdc++.h>
using namespace std;

struct Node{
  int id;
  int mask;
  
  Node(int id, int mask) : id(id), mask(mask){}
};

class NodeComparison{
public:
  bool operator()(const pair<Node, long long>& a, 
                  const pair<Node, long long>& b) const{
    return a.second > b.second;
  }
};


int compute_mask(vector<int>& types){
  int mask = 0;
  
  for(int t : types){
    mask |= 1 << (t - 1);
  }
  
  return mask;
}

long long synchronous_shopping(int N, int K,
                               vector<list<int>>& adjacencies,
                               vector<vector<int>>& edges, 
                               vector<vector<int>>& types){
  int mask_all = (1 << K) - 1;
  int mask, current_mask, new_mask;
  int current_dist, current_id, edge_cost;
  long long min_cost = numeric_limits<long long>::max();
  
  // Node, priority=dist, min-heap
  priority_queue<pair<Node, long long>, 
                 vector<pair<Node, long long> >,
                 NodeComparison> to_explore;
  vector<vector<long long>> dist(
    N + 1, vector<long long>(mask_all + 1, numeric_limits<long long>::max())
  );
  
  mask = compute_mask(types[1]);
  dist[1][mask] = 0;
  to_explore.push({Node(1, mask), dist[1][mask]});
  
  // Modification of Dijkstra, where a state is the id of
  // the node and the fish we have bought until that moment
  while(!to_explore.empty()){
    Node current_node = to_explore.top().first;
    current_mask = current_node.mask;
    current_id = current_node.id;
    current_dist = to_explore.top().second;
    to_explore.pop();
    
    if(current_dist <= dist[current_id][current_mask]){
      for(int adjacent : adjacencies[current_id]){
        mask = compute_mask(types[adjacent]);
        edge_cost = edges[current_id][adjacent];
        new_mask = mask | current_mask;
        
        if((dist[current_id][current_mask] + edge_cost) < dist[adjacent][new_mask]){
          dist[adjacent][new_mask] = dist[current_id][current_mask] + edge_cost;
          to_explore.push({Node(adjacent, new_mask), dist[adjacent][new_mask]});
        }
      }
    }
  }

  // Compute minimum of possible costs, where 
  // two masks add to all types of fishes
  for(int mask = 0; mask < dist[N].size(); mask++){
    for(int other_mask = mask; other_mask < dist[N].size(); other_mask++){
      if((mask | other_mask) == mask_all){
        min_cost = min(
          min_cost, max(dist[N][mask], dist[N][other_mask])
        );
      }
    } 
  }
  
  return min_cost;
}

int main(){
  int N, M, K;
  int T;
  int current_type;
    
  cin >> N >> M >> K;
  
  vector<vector<int> > edges(N + 1, vector<int>(N + 1, 0));
  vector<list<int> > adjacencies(N + 1);
  vector<vector<int> > types(N + 1);
  int edge_first, edge_second, cost;
  
  for(int i = 1; i <= N; i++){
    cin >> T;
    
    for(int j = 0; j < T; j++){
      cin >> current_type;
      types[i].push_back(current_type);
    }
  }
  
  for(int i = 0; i < M; i++){
    cin >> edge_first >> edge_second >> cost;
    edges[edge_first][edge_second] = cost;
    edges[edge_second][edge_first] = cost;
    adjacencies[edge_first].push_back(edge_second);
    adjacencies[edge_second].push_back(edge_first);
  }
  
  cout << synchronous_shopping(N, K, adjacencies, edges, types) << endl;
  return 0;
}
