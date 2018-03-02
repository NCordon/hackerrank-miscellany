// https://careercup.com/question?id=5682612859305984
#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  vector<Node*> children;

  Node(int val) {
    this->val = val;
  }
};

void PostOrder(Node* root) {
  unordered_set<int> visited;
  stack<Node*> to_explore;
  to_explore.push(root);

  while (!to_explore.empty()) {
    Node* current = to_explore.top();

    if (visited.count(current->val) > 0) {
      to_explore.pop();
      cout << current->val << " ";
    } else {
      for (auto child : current->children) {
        to_explore.push(child);
      }

      visited.insert(current->val);
    }
  }
}

int main() {
  /*         1 
           / \ \ 
          2   5 7
         / \   \
        3   4   6
  */
  Node* root = new Node(1);
  root->children.push_back(new Node(2));
  root->children.push_back(new Node(5));
  root->children.push_back(new Node(7));
  root->children[0]->children.push_back(new Node(3));
  root->children[0]->children.push_back(new Node(4));
  root->children[1]->children.push_back(new Node(6));

  PostOrder(root);
}

