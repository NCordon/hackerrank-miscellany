// Gives the next element int the inorder to a given one in an arbitrary binary tree

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  bool found;
  bool next;
  TreeNode* result;
  TreeNode* p;
  
  void process(TreeNode* current){
    if (next) {
      result = current;
      found = true;
    }
    if (!found && current == p) {
      next = true;
    }
  }
public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    result = NULL;
    found = false;
    next = false;
    this->p = p;
    
    if (p->right != NULL) {
      result = p->right;
      
      while (result->left != NULL) {
        result = result->left;
      }
    } else if (p != root) {
      TreeNode* current = root;
      TreeNode* prev;

      while (current != NULL && !found) {
        if (current->left != NULL) {
          prev = current->left;

          while (prev->right != NULL && prev->right != current)
            prev = prev->right;

          if (prev->right == NULL) {
            prev->right = current;
            current = current->left;
          } else if (prev->right == current) {
            process(current);
            current = current->right;
            prev->right = NULL;
          } 
        } else {
          process(current);
          current = current->right;
        }
      }
    }
    
    return result;
  }
};

int main() {
  /*
  Construct tree

        5
       / \
      3   6
     / \
    2   4
   /
  1
  */
  TreeNode* root = new TreeNode(5);
  root->left = new TreeNode(3);
  root->right = new TreeNode(6);
  TreeNode* p = root->left->left = new TreeNode(2);
  root->left->right = new TreeNode(4);
  root->left->left->left = new TreeNode(1);
  
  Solution sol;
  TreeNode* next = sol.inorderSuccessor(root, p);
  cout << next->val << endl;
}
