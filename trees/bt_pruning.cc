// https://leetcode.com/problems/binary-tree-pruning/
// O(n) solution, with n the number of nodes
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
  bool containsOne(TreeNode*& root) {
    bool result = false;
    
    if(root != NULL) {
      bool left_one  = containsOne(root->left);
      bool right_one = containsOne(root->right);
      
      if(!left_one)
        root->left = NULL;
      if(!right_one)
        root->right = NULL;
      
      result = root->val == 1 || left_one || right_one;
    }
    
    return result;
  }
  
public:
  TreeNode* pruneTree(TreeNode* root) {
    if(!containsOne(root))
      root = NULL;
    
    return root;
  }
};
