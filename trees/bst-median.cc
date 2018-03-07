// Based on morris-inorder.cc

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

void CountNodes(Node* node, int* count) {
  ++(*count);
}

void FindPosition(Node* node, int target, int* current, int* result) {
  if (*current == target)
    *result = node->val;
  ++(*current);
}

double BstMedian(Node* root) {
  int num_nodes = 0;
  int current_count;
  int left_median, right_median;
  auto CurryCount = bind(CountNodes, placeholders::_1, &num_nodes);

  // Count nodes in the tree
  MorrisInorder(root, CurryCount);

  // Median is the average of the position (num_nodes - 1) / 2 and num_nodes / 2 in the tree
  auto CurryLeftMedian = bind(FindPosition, placeholders::_1, (num_nodes - 1) / 2,
                              &current_count, &left_median);
  

  auto CurryRightMedian = bind(FindPosition, placeholders::_1, num_nodes / 2,
                               &current_count, &right_median);
  
  current_count = 0;
  MorrisInorder(root, CurryLeftMedian);
  current_count = 0;
  MorrisInorder(root, CurryRightMedian);
  
  return (left_median + right_median) / 2.0;
}


int main() {
  Node* root = new Node(4);
  root->left = new Node(2);
  root->right = new Node(6);
  root->left->left = new Node(1);
  root->left->right = new Node(3);
  root->right->left = new Node(5);
  root->right->right = new Node(7);

  cout << "Median is: " << BstMedian(root) << endl;

  root->right->right = nullptr;

  cout << "Median is: " << BstMedian(root) << endl;
}


