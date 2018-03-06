// https://leetcode.com/problems/evaluate-division/description/

class Solution {
private:
  vector<vector<double> > distances;
  vector<list<int> > adjacency;
  int num_vertex;
    
  void ComputeDistances(int index) {
    vector<bool> visited(num_vertex, false);
    stack<pair<int,double> > to_explore;
    to_explore.push({index, 1.0});

    while (!to_explore.empty()) {
      auto current = to_explore.top();
      to_explore.pop();
      visited[current.first] = true;
      distances[index][current.first] = current.second;

      for (int adjacent : adjacency[current.first]) {
        if(!visited[adjacent]) {
          to_explore.push({adjacent, current.second * distances[current.first][adjacent]});
        }
      }
    }   
  }
    
    
    
public:   
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values,  
                              vector<pair<string, string>> queries) {
    unordered_map<string, int> vertex;
    vector<double> result;
    int index = 0;
    int u,v;
    double current_distance;
        
    // Read different vertexes
    for (auto eq : equations) {
      if (vertex.count(eq.first) == 0) {
        vertex[eq.first] = index;
        ++index;
      }
      if (vertex.count(eq.second) == 0) {
        vertex[eq.second] = index;
        ++index;
      }
    }
        
    num_vertex = vertex.size();
    distances = vector<vector<double> >(num_vertex, vector<double>(num_vertex, -1.0));
    vector<vector<bool> > computed(num_vertex, vector<bool>(num_vertex, false));
    adjacency = vector<list<int> >(num_vertex);
        
    // Create the matrix of distances
    for (int i = 0; i < values.size(); ++i) {
      auto eq = equations[i];
      u = vertex[eq.first];
      v = vertex[eq.second];
      adjacency[u].push_back(v);
      adjacency[v].push_back(u);
      distances[u][v] = values[i];
      distances[v][u] = 1.0 / values[i];
      distances[u][u] = distances[v][v] = 1.0;
      computed[u][v] = computed[u][v] = computed[v][u] = computed[v][v] = true;
    }
        
    // Compute the solution to the queries
    for (auto q : queries) {
      if (vertex.count(q.first) > 0 && vertex.count(q.second) > 0) {
        u = vertex[q.first];
        v = vertex[q.second];
                
        if (!computed[u][v]) {
          ComputeDistances(u);
          computed[u][v] = true;
        }
        current_distance = distances[u][v];
        result.push_back(current_distance);
      } else {
        result.push_back(-1.0);
      }
    }
        
    return result;       
  }
};
