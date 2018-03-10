// https://leetcode.com/problems/closest-binary-search-tree-value
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
public:
  int closestValue(TreeNode* root, double target) {
    int closest;
    double dist;
    double min_dist = numeric_limits<double>::max();
    TreeNode* current = root;
    
    while (current != NULL) {
      dist = fabs(target - current->val);
      
      if (dist < min_dist) {
        min_dist = dist;
        closest = current->val;
      }
      
      if (current->val > target) 
        current = current->left;
      else
        current = current->right;
    }
    
    return closest;
  }
};
