// https://leetcode.com/problems/binary-search-tree-iterator/
// O(1) solution (amortized) for each call to next and hastNext
// O(h) where h is the height of the tree in space for those calls
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
  stack<TreeNode*> to_explore;
public:
  BSTIterator(TreeNode* root) {
    TreeNode* current = root;
    
    while (current != NULL) {
      to_explore.push(current);
      current = current->left;
    }
  }

  /** @return the next smallest number */
  int next() {
    TreeNode* current = to_explore.top();
    to_explore.pop();
    int result = current->val;
    
    current = current->right;
    
    while (current != NULL) {
      to_explore.push(current);
      current = current->left;
    }
    
    return result;
  }

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return !to_explore.empty();
  }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
