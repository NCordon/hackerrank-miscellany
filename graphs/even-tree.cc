// Solution to https://www.hackerrank.com/challenges/even-tree

#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;


struct Node{
  unordered_set<int> neighbours;
    
  bool isLeaf(){
    return neighbours.size()==1;
  }
};

int main() {
  int n, m, u, v;
  int current;
  int prev;
  int removable_edges = 0;
  bool keep_searching = true;
  cin >> n >> m;
    
  vector<Node> graph(n, Node());
  vector<int> descendants(n,1);
  list<int> leaves;
  vector<unordered_set<int>> adjacencies;


  for (int i=0; i<m; i++){
    cin >> u >> v; 
    
    graph[v-1].neighbours.insert(u-1);
    graph[u-1].neighbours.insert(v-1);
  }
    
      
  for (int u=0; u<n; u++){
    // Matrix of adjacencies
      adjacencies.push_back(graph[u].neighbours);
    // Locate the leaves    
    if(graph[u].isLeaf())
      leaves.push_back(u);
  }
    

  /* 
     Move pointers up from leaves towards root
     counting descendants of a node, untill we arrive
     at a fully descendants counted node with pair descendants,
     and that is an even tree
  */
  while(keep_searching){
    list<int>::iterator it = leaves.begin();
    keep_searching = false;
        
    while(it!= leaves.end()){
      if(adjacencies[*it].size() == 1){
        // We have an even tree
        if(descendants[*it]%2 == 0 and descendants[*it]>0){
          removable_edges++;
          descendants[*it] = 0;
        }
                
        prev = *it;
        *it = *adjacencies[*it].begin();
        adjacencies[*it].erase(prev);
        adjacencies[prev].erase(*it);
               
        if(adjacencies[*it].size()>=1)
          keep_searching = true;
        
        descendants[*it]+= descendants[prev];
      }
            
      it++;
    }

    leaves.sort();
    leaves.unique();
  }
    
  cout << removable_edges << endl;
  return 0;
}
