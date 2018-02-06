// https://www.hackerrank.com/challenges/kruskalmstrsub/problem
#include <bits/stdc++.h>
using namespace std;

struct Edge : public pair<int,int>{
  int cost;
};

bool edge_compare(Edge a, Edge b){
  if(a.cost == b.cost)
    return (a.first + a.second < b.first + b.second);
  else
    return a.cost < b.cost;
}

class DisjointSet{
private:
  vector<int> parents;
  vector<int> ranks;
  
public:  
  DisjointSet(int n){
    // Initialize dummy first position
    parents.push_back(-1);
    ranks.push_back(0);
    
    for(int i = 1; i <= n; i++){
      parents.push_back(i);
      ranks.push_back(0);
    }
  }
  
  int find(int node){
    if(node != parents[node]){
      parents[node] = find(parents[node]);
    }
    
    return parents[node];
  }
  
  
  void merge(int first_forest, int second_forest){
    int first_parent = find(first_forest);
    int second_parent = find(second_forest);
    
    if(ranks[first_parent] < ranks[second_parent])
      parents[first_parent] = second_parent;
    else{
      parents[second_parent] = first_parent;
      if(ranks[first_parent] == ranks[second_parent])
        ranks[second_parent]++;
    }
  }
};

int mst(int n, vector<Edge> edges){
  // Order edges with increasing order of cost and sum
  // of cordinates in case of tie
  sort(edges.begin(), edges.end(), edge_compare);
  int result = 0;
  int first_forest, second_forest;
  DisjointSet forests(n);
  
  for(Edge e : edges){
    first_forest = forests.find(e.first);
    second_forest = forests.find(e.second);
    
    if(first_forest != second_forest){
      result += e.cost;
      forests.merge(first_forest, second_forest);
    }
  }
  
  return result;
}

int main() {
  int n;
  int m;
  Edge current;
  cin >> n >> m;
  vector<Edge> edges(m);
  
  for(int edges_i = 0; edges_i < m; edges_i++){
    cin >> current.first >> current.second;
    cin >> current.cost;
    edges[edges_i] = current;
  }
  
  int result = mst(n, edges);
  cout << result << endl;
  return 0;
}
