// https://www.hackerrank.com/challenges/swap-nodes-algo/problem
#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node* left = NULL;
  Node* right = NULL;
};

class Tree {
private:
  Node* root = NULL;
  
  void BuildTree(Node*& current, vector<int>& tree, int i) {
    if (tree[i] != -1 && i < tree.size()) {
      current = new Node;
      current->value = tree[i];
      BuildTree(current->left, tree, 2*i + 1);
      BuildTree(current->right, tree, 2*i + 2);
    }
  }
  
  void PrintUtil(Node* current) {
    if (current != NULL) {
      PrintUtil(current->left);
      cout << current->value << " ";
      PrintUtil(current->right);
    }
  }
  
  void SwapUtil(Node* current, int depth, int current_depth) {
    if (current) {
      if (current_depth % depth == 0) {
        Node *aux = current->left;
        current->left = current->right;
        current->right = aux;
      }
      
      SwapUtil(current->left, depth, current_depth + 1);
      SwapUtil(current->right, depth, current_depth + 1);
    }
  }
  
public:
  Tree(vector<int>& tree) {
    BuildTree(root, tree, 0);
  }
  
  void PrintInorder() {
    PrintUtil(root);
    cout << endl;
  }
  
  void Swap(int depth) {
    SwapUtil(root, depth, 1);
  }
};

int main(){
  vector<int> tree{1, 2, 3, 4, -1, 5, -1, 6, -1, -1, -1, 7, 8, -1, -1, -1, 9,
      -1, -1, -1, -1, -1, -1, -1, -1, 10, 11};
  Tree my_tree(tree);
  my_tree.Swap(2);
  my_tree.PrintInorder();
}
