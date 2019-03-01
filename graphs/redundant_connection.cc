// https://leetcode.com/problems/redundant-connection-ii/
// O(n) solution where n is the number of edges
class DisjointSet {
private:
  vector<int> parent;
  vector<int> rank;
  int num_components;
  
public:
  DisjointSet(int n) {
    num_components = n;
    parent.resize(n + 1);
    rank.resize(n + 1);
    // Fill the parents from 0 to n
    iota(parent.begin(), parent.end(), 0);
    // Fill the ranks with 0
    fill(rank.begin(), rank.end(), 0);
  }

  // Find the component index which contains elem
  // elem must be in 1...n
  int find(int elem) {
    if (parent[elem] != elem)
      parent[elem] = find(parent[elem]);
    
    return parent[elem];
  }

  // Merge the component that contains i with 
  // the component that contains j
  void merge(int i, int j) {
    int component_i = find(i);
    int component_j = find(j);

    if (component_i != component_j) {
      --num_components;
      
      if (rank[component_i] > rank[component_j]) {
        parent[component_j] = component_i;
      } else {
        parent[component_i] = component_j;

        if (rank[component_i] == rank[component_j])
          ++rank[component_j];
      }
    }
  }
  
  int get_num_components() {
    return num_components;
  }
};


class Solution {
  vector<vector<int>> children;
  vector<vector<int>> parents;
public:
  bool valid_if_removing(vector<vector<int>>& edges, int i) {
    DisjointSet graph(edges.size());
    int x, y;
    
    for (int j = 0; j < edges.size(); ++j) {
      if (j != i) {
        x = edges[j].front();
        y = edges[j].back();
        graph.merge(x, y);
      }
    }
    
    return (graph.get_num_components() == 1);      
  }
  
  vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    children.resize(n + 1);
    parents.resize(n + 1);
    int x, y;
    bool has_root = false;
    bool found = false;
    vector<int> result;
    vector<int> edge;
    
    for (auto edge : edges) {
      x = edge.front();
      y = edge.back();
      children[x].push_back(y);
      parents[y].push_back(x);
    }
    
    // First check whether the graph has a defined root
    for (int i = 1; i <= n && !has_root; ++i)
      if (parents[i].size() == 0)
        has_root = true;
    
    /* If the graph already has a defined root, find a node which
       has 2 parents and try erasing the edges which make it have 2
       parents
           
       If it does not have a defined root, then the edge we have
       to erase is the one which creates a cycle.
    */
    if (has_root) {      
      for (int i = n - 1; i >= 0 && !found; --i) {
        edge = edges[i];
        
        if (parents[edge.back()].size() == 2) {
          if (valid_if_removing(edges, i)) {
            found = true;
            result = edge;
          }
        }
      }
    } else {
      DisjointSet component(edges.size());
      
      for (int i = 0; i < edges.size() && !found; ++i) {
        x = edges[i].front();
        y = edges[i].back();
      
        if (component.find(x) != component.find(y))
          component.merge(x, y);
        else {
          result = edges[i];
          found = true;
        }
      }
    }
    
    return result;
  }
};
