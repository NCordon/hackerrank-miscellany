class Solution {
  struct Node {
    bool is_word = false;
    unordered_map<char, Node*> children;
  };
  
  bool CanBeSplitted(string& s, Node* root) {
    bool can_split = false;
    bool still_words;
    Node* current;
    stack <int> to_explore;
    vector<bool> visited(s.size(), false);
    
    to_explore.push(0);
    
    while (!to_explore.empty() && !can_split) {
      int i = to_explore.top();
      to_explore.pop();
      
      if(!visited[i]){
        still_words = true;
        current = root;

        for (int k = i; k < s.size() && !can_split && still_words; ++k) {
          if (current->children.count(s[k]) > 0) {
            current = current->children[s[k]];

            if (current->is_word) {
              if (k == s.size() - 1)
                can_split = true;
              else
                to_explore.push(k + 1);
            } 
          } else {
            still_words = false;
          }
        }
        
        visited[i] = true;
      }
    }
    
    return can_split;
  }
  
public:
  bool wordBreak(string s, vector<string>& word_dict) {
    Node* root = new Node;
    Node* current;
      
    for (string word : word_dict) {
      current = root;
      for (char c : word) {
        if (current->children.count(c) == 0)
          current->children[c] = new Node;
          
        current = current->children[c];
      }
      current->is_word = true;
    }
      
    return CanBeSplitted(s, root);
  }
};
