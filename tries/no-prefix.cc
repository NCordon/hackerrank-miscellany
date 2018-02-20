// https://www.hackerrank.com/challenges/no-prefix-set/problem
#include <bits/stdc++.h>
using namespace std;

struct Node{
  bool is_end_node = false;
  unordered_map<char, Node*> children;
};

class Trie{
private:
  Node* root;

public:  
  Trie() {
    root = new Node();
  }
  
  ~Trie() {
    stack<Node*> to_erase;
    to_erase.push(root);
    Node* current;
    
    while (!to_erase.empty()){
      current = to_erase.top();
      to_erase.pop();
      delete current;
      
      for (auto child : current->children) {
        to_erase.push(child.second);
      }
    }
  }

  bool IsOrHasPrefix(string word) {
    Node* current = root;
    bool prefix_found = false;
    bool keep_looking = true;
    
    for (int i = 0; i < word.size() && keep_looking && !prefix_found; i++) {
      if (current->children.count(word[i]) == 0) {
        keep_looking = false;
      }
      else {
        current = current->children[word[i]];
        prefix_found = current->is_end_node || i == word.size() - 1;
      }
    }
    
    return prefix_found;
  }
  
  void Add(string word) {
    Node* current = root;
    
    for (char letter : word) {
      if (current->children.count(letter) == 0) {
        current->children[letter] = new Node();
      }
      
      current = current->children[letter];
    }
    
    current->is_end_node = true;
  }
};


int main() {
  int num_words;
  string current_word;
  Trie dictionary;
  bool prefix_found = false;
  cin >> num_words;
  
  for (int i = 0; i < num_words && !prefix_found; i++) {
    cin >> current_word;
    prefix_found = dictionary.IsOrHasPrefix(current_word);
    
    if(!prefix_found)
      dictionary.Add(current_word);
  }
  
  if(prefix_found)
    cout << "BAD SET" << endl << current_word << endl;
  else
    cout << "GOOD SET" << endl;
}
