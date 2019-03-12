// https://leetcode.com/contest/weekly-contest-127/problems/construct-binary-search-tree-from-preorder-traversal/
// O(N²) where N is the number of nodes in the worst case
// TODO Improve this solution
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
  TreeNode* bstFromPreorder(vector<int>& preorder) {
    TreeNode* root = new TreeNode(preorder[0]);
    TreeNode* current;
    int elem;
    bool assigned;
    
    for (int i = 1; i < preorder.size(); ++i) {
      elem = preorder[i];
      current = root;
      assigned = false;

      while (!assigned) {
        if (current->val > elem) {
          if (current->left != NULL)
            current = current->left;
          else {
            assigned = true;
            current->left = new TreeNode(elem);
          }
        } else {
          if (current->right != NULL)
            current = current->right;
          else {
            assigned = true;
            current->right = new TreeNode(elem);
          }
        }
      }
    }
    
    return root;
  }
};
