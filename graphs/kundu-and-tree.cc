// https://www.hackerrank.com/challenges/kundu-and-tree/problem
#include <bits/stdc++.h>
using namespace std;

typedef pair<long, long> edge;
long long MOD = 1E9 + 7;

class DisjointSet {
private:
  vector<long> parent;
  vector<long> rank;
  long num_nodes;
  
public:
  DisjointSet(long num_nodes) {
    this->num_nodes = num_nodes;
    parent = vector<long>(num_nodes + 1);
    rank = vector<long>(num_nodes + 1, 0);
    iota(parent.begin(), parent.end(), 0);
  }
  
  long FindSet(long node) {
    if (parent[node] != node) {
      // Path Compression
      parent[node] = FindSet(parent[node]);
    }

    return parent[node];
  }
  
  void MergeComponents(long first_parent, long second_parent) {
    if(first_parent != second_parent) {
      if (rank[first_parent] > rank[second_parent]) {
        parent[second_parent] = first_parent;
      }
      else if (rank[first_parent] < rank[second_parent]) {
        parent[first_parent] = second_parent;
      }
      else {
        parent[first_parent] = second_parent;
        rank[second_parent]++;
      }
    }
  }
  
  vector<long> PartitionsSize(long N) {
    unordered_map<long, long> component_counts;
    vector<long> result;
    long node_parent;

    for (long node = 1; node <= N; node++) {
      node_parent = FindSet(node);
      
      if (component_counts.count(node_parent) == 0)
        component_counts[node_parent] = 1;
      else
        component_counts[node_parent]++;      
    }

    for (auto count : component_counts) {
      result.push_back(count.second);
    }

    return result;  
  }
};

long long TripletsRedPath(long N, vector<edge> edges) {
  long long result = N * (N - 1) * (N - 2);
  long first_parent;
  long second_parent;
  long invalid;
  DisjointSet forest(N);
  vector<long> component_sizes;
  
  
  for (auto e : edges) {
    first_parent = forest.FindSet(e.first);
    second_parent = forest.FindSet(e.second);
    forest.MergeComponents(first_parent, second_parent);
  }
  
  component_sizes = forest.PartitionsSize(N);
  
  // if we have an isolated node, size = 1, we rest 0
  for (long size : component_sizes) {
    invalid =  size * (size - 1) * (N - size) * 3;
    invalid += size * (size - 1) * (size - 2);
    result =  result - invalid;
  }
  
  // Divide result by 3!
  return (result / 6) % MOD;
}

int main() {
  long N;
  cin >> N;
  vector<edge> edges;
  edge current_edge;
  char color;
  
  for (long i = 1; i < N; i++) {
    cin >> current_edge.first >> current_edge.second >> color;
    
    if (color == 'b')
      edges.push_back(current_edge);
  }
  
  cout << TripletsRedPath(N, edges) << endl;
}
