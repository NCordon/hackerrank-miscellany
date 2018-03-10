// https://leetcode.com/problems/inorder-successor-in-bst
// Gives the next element int the inorder to a given one in an BST in O(log n) if tree is balanced

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* result = NULL;
    bool found = false;
    
    if (p->right != NULL) {
      result = p->right;
      
      while (result->left != NULL) {
        result = result->left;
      }
    } else if (p != root) {
      TreeNode* current = root;

      while (!found) {
        if (current == p) {
          found = true;
        } else if (current->val > p->val) {
          result = current;
          current = current->left;
        } else {
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
  root->left->left = new TreeNode(2);
  TreeNode* p = root->left->right = new TreeNode(4);
  root->left->left->left = new TreeNode(1);
  
  Solution sol;
  TreeNode* next = sol.inorderSuccessor(root, p);
  cout << next->val << endl;
}
