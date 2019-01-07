#include <algorithm>

// https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/
// O(n) solution where n is the number of nodes of the tree

/* Idea:
   Firstly, we compute the number of nodes in the tree, which should match the
   length of the voyage. Otherwise there is no solution
   Secondly, we recursively pile the changes needed to achieve the given voyage 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
private:
  void computeFlipsToDo(
    TreeNode* root,
    int& index,
    vector<int>& voyage,
    vector<int>& flips
  ) {
    if (root != NULL) {
      if (root->val == voyage[index]) {
        ++index;

        // If left->val does not match next element in the voyage, we
        // should swap left and right trees
        if (root->left != NULL && root->left->val != voyage[index]) {
          swap(root->left, root->right);
          flips.push_back(root->val);
        }
        
        computeFlipsToDo(root->left, index, voyage, flips);
        computeFlipsToDo(root->right, index, voyage, flips);
      } else {
        flips = {-1};
      }
    }
  }
  
  int sizeOfTree(TreeNode* node) {
    if (node == NULL)
      return 0;
    else
      return 1 + sizeOfTree(node->left) + sizeOfTree(node->right);
  }
  
public:
  vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
    int index = 0;
    int numNodes = sizeOfTree(root);
    vector<int> flips;
    
    if (numNodes == voyage.size())
      computeFlipsToDo(root, index, voyage, flips);
    else
      flips = {-1};
    
    return flips;
  }
};
