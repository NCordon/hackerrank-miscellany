//https://www.hackerrank.com/challenges/self-balancing-tree/problem
/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */

int height(node* n){
  if(n == NULL)
    return -1;
  else
    return n->ht;
}

void update_height(node* n){
  if(n != NULL)
    n->ht = max(height(n->left), height(n->right)) + 1;
}

node* rotate_left(node* left_subtree, node* right_subtree){
  left_subtree->right = right_subtree->left;
  right_subtree->left = left_subtree;
  update_height(left_subtree);
  update_height(right_subtree);
  
  return right_subtree;
}

node* rotate_right(node* left_subtree, node* right_subtree){
  right_subtree->left = left_subtree->right;
  left_subtree->right = right_subtree;
  update_height(right_subtree);
  update_height(left_subtree);
  
  return left_subtree;
}

node* insert(node *root,int val){
  node* current_node = root;
  node* previous_node;
  vector<node*> path_to_leaf;
  vector<bool> go_left;

  int i;
   
  while(current_node != NULL){
    path_to_leaf.push_back(current_node);
    
    if(val <= current_node->val){
      current_node = current_node->left;
      go_left.push_back(true);
    }
    else{
      current_node = current_node->right;
      go_left.push_back(false);
    }
  }
  
  current_node = new node;
  current_node->val = val;
  current_node->left = NULL;
  current_node->right = NULL;
  current_node->ht = 0;
  i = path_to_leaf.size() - 1;
  previous_node = current_node;
  
  // Go backwards 
  while(i >= 0){
    current_node = path_to_leaf[i];
    if(go_left[i])
      current_node->left = previous_node;
    else
      current_node->right = previous_node;
    
    // Imbalanced to left
    if(height(current_node->left) - height(current_node->right) > 1){      
      // Left right case, rotate to left
      if(height(current_node->left->right) - height(current_node->left->left) > 0)
        current_node->left = rotate_left(current_node->left, current_node->left->right);
      // Left left case
      if(height(current_node->left->left) - height(current_node->left->right) > 0)
        current_node = rotate_right(current_node->left, current_node);
    }
    // Imbalanced to right
    else if(height(current_node->right) - height(current_node->left) > 1){
      // Right left case, rotate to right
      if(height(current_node->right->left) - height(current_node->right->right) > 0)
        current_node->right = rotate_right(current_node->right->left, current_node->right);
      // Right right case
      if(height(current_node->right->right) - height(current_node->right->left) > 0)
        current_node = rotate_left(current_node, current_node->right);
    }
    
    update_height(current_node);
    previous_node = current_node;
    i--;
  }

  update_height(previous_node);
  return previous_node;
}
