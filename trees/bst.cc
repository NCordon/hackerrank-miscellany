// https://www.hackerrank.com/challenges/ctci-is-binary-search-tree/problem
#include <climits>
/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/

struct TreeInfo{
  bool BST;
  int max;
  int min;
};

TreeInfo is_BST(Node* root){
  TreeInfo my_tree;
  my_tree.BST = true;
  my_tree.min = INT_MAX;
  my_tree.max = INT_MIN;
  
  if(root != NULL){
    my_tree.max = root->data;
    my_tree.min = root->data;

    if(root->left != NULL){
      TreeInfo left_subtree = is_BST(root->left);
      
      if(!left_subtree.BST || root->data <= left_subtree.max)
        my_tree.BST = false;
    
      my_tree.min = min(my_tree.min, left_subtree.min);
      my_tree.max = max(my_tree.max, left_subtree.max);
    }

    if(root->right != NULL){
      TreeInfo right_subtree = is_BST(root->right);

      if(!right_subtree.BST || root->data >= right_subtree.min)
        my_tree.BST = false;
    
      my_tree.min = min(my_tree.min, right_subtree.min);
      my_tree.max = max(my_tree.max, right_subtree.max);
    }
  }

  return my_tree;
}

bool checkBST(Node* root){
  return is_BST(root).BST;
}
