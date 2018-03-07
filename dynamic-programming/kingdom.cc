// https://www.hackerrank.com/challenges/kingdom-division/
#include <bits/stdc++.h>
using namespace std;

long long maximum = 1E9 + 7;

/*
Idea to solve the problem:

Carry a data structure which indicates well colored subtrees and 
quasi-well colored subtrees (those in which root can have a certain
color, providing that its parent has same color)
*/
enum Color{
    red_color,
    black_color
};

Color red = red_color;
Color black = black_color;

struct Coloring{
  // Subtrees which are valid solutions on their own
  // with its root coloured in red (0), or black(1)
  long long valid[2];
  // Subtrees which are valid solutions providing than 
  // parent has same colour than their root (red (0), 
  // black (1))
  long long invalid[2];
};

bool is_leaf(int node, vector<bool>& visited, vector< list<int> >& adjacencies){
  bool leaf = true;
  
  for(auto child : adjacencies[node]){
    if(!visited[child])
      leaf = false;
  }
  
  return leaf;
}

Coloring solve_divisions(int node, vector<bool>& visited, 
                         vector< list<int> >& adjacencies){
    
  long long count_red = 1;
  long long count_black = 1;
  long long product_black = 1;
  long long product_red = 1;
  long long valid_subcolorings;
  Coloring child_coloring;
  Coloring solution;
  visited[node] = true;

  if(!is_leaf(node, visited, adjacencies)){
    for(auto child : adjacencies[node]){
      if(!visited[child]){
        child_coloring = solve_divisions(child, visited, adjacencies);
        valid_subcolorings = (child_coloring.valid[red] + 
                             child_coloring.valid[black]) % maximum;
        count_red = (count_red * (valid_subcolorings + 
                     child_coloring.invalid[red])) % maximum;
        count_black = (count_black * (valid_subcolorings + 
                       child_coloring.invalid[black])) % maximum;
        product_red = (product_red * child_coloring.valid[red]) % maximum;
        product_black = (product_black * child_coloring.valid[black]) % maximum;
      }
    }
    
    // Sum maximum to get a positive modulo
    solution.valid[red] = (count_red - product_black + maximum) % maximum;
    solution.valid[black] = (count_black - product_red + maximum) % maximum;
    solution.invalid[red] = product_black % maximum;
    solution.invalid[black] = product_red % maximum;
  }
  else{
    solution.valid[red] = solution.valid[black] = 0;
    solution.invalid[red] = solution.invalid[black] = 1;
  }
  
  return solution;
}

long long kingdom_divisions(int n, vector < vector<int> > edges){
  Coloring solution;
  vector<bool> visited(n + 1, false);
  vector< list<int> > adjacencies(n+1);
  
  for(auto edge : edges){
    adjacencies[edge[0]].push_back(edge[1]);
    adjacencies[edge[1]].push_back(edge[0]);
  }
  
  solution = solve_divisions(n, visited, adjacencies);
    
  return (solution.valid[red] + solution.valid[black]) % maximum;
}


int main() {
  int n;
  cin >> n;
  vector< vector<int> > roads(n-1,vector<int>(2));
  for(int roads_i = 0;roads_i < n-1;roads_i++){
    for(int roads_j = 0;roads_j < 2;roads_j++){
      cin >> roads[roads_i][roads_j];
    }
  }
  long long result = kingdom_divisions(n, roads);
  cout << result << endl;
  return 0;
}
