// Problem from https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* prev = head;
        ListNode* result = NULL;
        ListNode** current = &result;
        bool skip = false;
        
        if (head!=NULL)
            head = head->next;
            

        /* 
        increase two consecutive pointers
            if repetition happens
                skip all repetitions
                until new value found
        */
                
        while(head!=NULL){
            if(head->val == prev->val){
                skip = true;
            }
            else if (skip){
                skip = false;
                prev = head;
            }
            else{
                *current = prev;
                current = &(prev->next);
                prev = prev->next;
            }
            head = head->next;
        }
        
        // Last element of the list was repeated
        if (skip)
            *current = NULL;
        // Last element of the list was not repeated and therefore is valid
        else
            *current = prev;
        
        
        return result;
    }
};
