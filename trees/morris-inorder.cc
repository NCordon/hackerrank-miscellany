#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;

  Node(int val) {
    this->val = val;
    left = nullptr;
    right = nullptr;
  }
};

void MorrisInorder(Node* root, auto& ProcessNode) {
  Node* current = root;
  Node* previous;

  while(current != nullptr) {
    if (current->left == nullptr){
      ProcessNode(current);
      current = current->right;
    } else {
      previous = current;
      current = current->left;

      while (current->right != nullptr && current->right != previous) {
        current = current->right;
      }

      if (current->right == nullptr) {
        current->right = previous;
        current = previous->left;
      } else if (current->right == previous) {
        current->right = nullptr;
        ProcessNode(previous);
        current = previous->right;
      }
    }
  }
}

void PrintNodes(Node* node) {
  cout << node->val << " ";
}


int main() {
  Node* root = new Node(4);
  root->left = new Node(2);
  root->right = new Node(6);
  root->left->left = new Node(1);
  root->left->right = new Node(3);
  root->right->left = new Node(5);
  root->right->right = new Node(7);

  MorrisInorder(root, PrintNodes);
  cout << endl;
}


