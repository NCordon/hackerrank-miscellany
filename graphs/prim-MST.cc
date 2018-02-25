#include<bits/stdc++.h>
using namespace std;

struct Cut {
  int cost;
  int end_point;
  pair<int,int> edge;

  Cut(int cost, int end_point, pair<int,int> edge){
    this->cost = cost;
    this->end_point = end_point;
    this->edge = edge;    
  }
};

class CutComparison {
public:
  bool operator()(const Cut& a, const Cut& b) {
    return a.cost > b.cost;
  }
};

struct MST {
  int cost;
  vector<pair<int, int> > edges;
};

MST PrimMST(int num_nodes, const vector<list<int> >& adjacency, const vector<vector<int> >& weight) {
  priority_queue<Cut, vector<Cut>, CutComparison> to_use;
  unordered_set<int> in_MST;
  unordered_set<int> out_MST;
  //vector<pair<int,int> > edges;
  MST result;
  result.cost = 0;
  
  // Introduce first node in MST, rest of them in set of not used nodes
  in_MST.insert(0);
  for (int i = 1; i < num_nodes; i++)
    out_MST.insert(i);

  for (auto connected : adjacency[0])
    to_use.push(Cut(weight[0][connected], connected, {0, connected}));

  while (in_MST.size() != num_nodes) {
    auto current = to_use.top();
    to_use.pop();

    while (out_MST.count(current.end_point) == 0) {
      current = to_use.top();
      to_use.pop();
    }

    for (auto connected : adjacency[current.end_point])
      to_use.push(Cut(weight[current.end_point][connected],
                      connected,
                      {current.end_point, connected}));

    result.edges.push_back(current.edge);
    in_MST.insert(current.end_point);
    out_MST.erase(current.end_point);
    result.cost += current.cost;
  }

  return result;
}


int main() {
  int num_nodes = 4;
  const int INF = numeric_limits<int>::max();
  vector<list<int> > adjacency = {{3}, {2, 3}, {1, 3}, {0, 1, 2}};
  vector<vector<int> >  weight = {{INF, INF, INF, 1},
                                  {INF, INF, 6, 5},
                                  {INF, 6, INF, 7},
                                  {1, 5, 7, INF}};

  cout << PrimMST(num_nodes, adjacency, weight).cost << endl;
}
