// https://leetcode.com/problems/insert-into-a-cyclic-sorted-list/
// O(n) solution where n is the length of the list, algorithmically
// O(1) in space
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
  Node* lower_bound(Node* head, int val) {
    Node* result = NULL;
    Node* current = head;
    Node* maximum = current;
    
    if (current != NULL) {
      result = (current != NULL && current->val < val ? current : NULL);
      current = current->next;
      
      while (current != head) {
        if (current->val < val && 
           (result == NULL || current->val >= result->val))
          result = current;
        
        if (current->val >= maximum->val)
          maximum = current;
        
        current = current->next;
      }
    }
    
    if (result == NULL)
      result = maximum;
    
    return result;
  }
  
  
  Node* insert(Node* head, int insertVal) {
    Node* before = lower_bound(head, insertVal);
    
    if (before != NULL)
      before->next = new Node(insertVal, before->next);
    else {
      head = new Node(insertVal, NULL);
      head->next = head;
    }
    
    return head;    
  }
};
