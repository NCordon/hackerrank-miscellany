// https://leetcode.com/problems/validate-binary-search-tree/
// Iterative solution
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
  struct Bound {
    bool set;
    int bound;
  };
  
  struct NodeConstraint {
    TreeNode* node;
    Bound lower_bound;
    Bound upper_bound;
  };
  
public:
  bool isValidBST(TreeNode* root) {
    stack<NodeConstraint> nodes;
    bool is_bst = true;
    NodeConstraint current;
    TreeNode* node;
    Bound lower;
    Bound upper;
    Bound this_bound;
    nodes.push(NodeConstraint {root, Bound {false, 0}, Bound {false, 0}});
    
    while (!nodes.empty() && is_bst) {
      current = nodes.top();
      nodes.pop();
      node = current.node;
      lower = current.lower_bound;
      upper = current.upper_bound;
      
      if (node != NULL) {
        if (lower.set && node->val <= lower.bound)
            is_bst = false;
        
        if (upper.set && node->val >= upper.bound)
            is_bst = false;
        
        this_bound = Bound {true, node->val};
        nodes.push(NodeConstraint {node->right, this_bound, upper});
        nodes.push(NodeConstraint {node->left, lower, this_bound});
      }
    }
    
    return is_bst;
  }
};
