// https://leetcode.com/problems/merge-k-sorted-lists/

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
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    vector<ListNode*> pointers = lists;
    // first element = value, second one = index of the list of the value
    priority_queue<pair<int, int>, vector<pair<int, int> >, 
                   greater<pair<int, int> >> min_heap;
    ListNode* result = NULL;
    ListNode** current = &result;
    int index_min;
    int value_min;
        
    for (int i = 0; i < pointers.size(); ++i) {
      if(pointers[i] != NULL) {
        min_heap.push({pointers[i]->val, i});
      }
    }
        
    while (!min_heap.empty()) {
      auto minimum = min_heap.top();
      min_heap.pop();
      index_min = minimum.second;
      value_min = minimum.first;

      *current = new ListNode(value_min);
      current = &(*current)->next;
            
      if (pointers[index_min]->next != NULL) {
        pointers[index_min] = pointers[index_min]->next;
        min_heap.push({pointers[index_min]->val, index_min});
      }
    }
        
    return result;
  }
};
