// https://leetcode.com/problems/validate-binary-search-tree/
// O(n) solution algorithmically, where n is the number of nodes of the tree
// O(n) solution in space
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
  
  struct TreeInfo {
    int min;
    int max;
    bool valid_bst;
    bool empty;
  };
  
  TreeInfo invalid_bst {
    numeric_limits<int>::min(),
    numeric_limits<int>::max(),
    false,
    false
  };
  
  TreeInfo tree_info(TreeNode* root) {
    
    if (root == NULL) {
      return TreeInfo {
        numeric_limits<int>::max(),
        numeric_limits<int>::min(),
        true,
        true
      };
    } else {
      auto left = tree_info(root->left);
      auto right = tree_info(root->right);
      int current = root-> val;
      
      if (left.valid_bst && right.valid_bst) {
        if ((left.empty ? true : (current > left.max)) && 
            (right.empty ? true : (current < right.min))) {
          
          return TreeInfo {
            (left.empty ? current : left.min),
            (right.empty ? current : right.max),
            true,
            false
          };
        }
        else
          return invalid_bst;
      } else {
        return invalid_bst;
      }
    }
  }
  
public:
  bool isValidBST(TreeNode* root) {
    return tree_info(root).valid_bst;
  }
};
