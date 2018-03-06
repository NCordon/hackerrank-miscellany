// https://leetcode.com/problems/graph-valid-tree/description/

class Solution {
public:
  bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);
    vector<unordered_set<int> > adjacency(n);
    bool is_tree = true;
        
    for (auto edge : edges) {
      adjacency[edge.first].insert(edge.second);
      adjacency[edge.second].insert(edge.first);            
    }
        
    stack<int> to_explore;
    to_explore.push(0);
        
    // DFS marking the parents of the nodes
    // If at some point a node has got a parent,
    // it means we have found a cycle, and graph
    // cannot be a tree
    while (!to_explore.empty() && is_tree) {
      auto current = to_explore.top();
      to_explore.pop();

      for (int adjacent : adjacency[current]) {
        adjacency[adjacent].erase(current);
        if(parent[adjacent] != adjacent)
          is_tree = false;
        parent[adjacent] = current;
        to_explore.push(adjacent);
      }
    }
    
    // Check if it is connected (if a node different from 
    // the root is its own parent, it is not connected)
    for (int i = 1; i < n && is_tree; ++i)
      if (parent[i] == i)
        is_tree = false;
            
    return is_tree;
  }
};
