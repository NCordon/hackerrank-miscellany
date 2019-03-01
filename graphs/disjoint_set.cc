#include <vector>
#include <numeric>
using namespace std;

class DisjointSet {
  vector<int> parent;
  vector<int> rank;
 public:
  DisjointSet(int n) {
    parent = vector<int>(n);
    // Fill the parents from 0 to n-1
    iota(parent.begin(), parent.end(), 0);

    for (int j = 0; j < n; ++j)
      rank[j] = 0;
  }

  int find(int elem) {
    if (parent[elem] == elem) {
      return elem;
    } else {
      int component = find(parent[elem]);
      parent[elem] = component;
      return component;
    }
  }

  // Merge the component that contains i with the component that contains j
  void merge(int i, int j) {
    int component_i = find(i);
    int component_j = find(j);

    if (component_i != component_j) {
      if (rank[component_i] > rank[component_j]) {
        parent[component_j] = component_i;
      } else {
        parent[component_i] = component_j;

        if (rank[component_i] == rank[component_j])
          ++rank[component_j];
      }
    }
  }

};

  
int main() {
  auto set = DisjointSet(40);

}
