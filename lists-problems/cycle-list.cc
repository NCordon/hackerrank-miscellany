/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/

bool has_cycle(Node* head) {
    if(head == false)
        return false;
    if(head == head->next)
        return true;
    else{
        Node* p_next = head->next;   
        // Points to itself
        head->next = head;
        
        return(has_cycle(p_next));
    }
}
