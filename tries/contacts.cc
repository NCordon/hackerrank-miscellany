//https://www.hackerrank.com/challenges/ctci-contacts/problem
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node{
  bool is_end_node;
  unordered_map<char, Node*> children;
  int count;

  Node(){
    is_end_node = false;
    count = 0;
  }
};

class Trie{
private:
  Node* root;
public:
  Trie(){
    root = new Node();
  }

  void add(string word){
    Node* current = root;
    
    for(int i = 0; i < word.size(); i++){
      unordered_map<char, Node*>::iterator it = current->children.find(word[i]);
      current->count++;  
      
      if(it != current->children.end())
        current = it->second;
      else{
        current->children[word[i]] = new Node();
        current = current->children[word[i]];
      }

      if(i == word.size() - 1){
        current-> is_end_node = true;
        current->count++;
      }
    }
  }

  int count(string partial){
    int result = 0;
    Node* current = root;
    bool found = true;
    stack<Node*> to_explore;

    for(int i = 0; i < partial.size() && found; i++){
      unordered_map<char, Node*>::iterator it = current->children.find(partial[i]);

      if(it != current->children.end())
        current = it->second;
      else
        found = false;
    }

    if(found){
      result = current->count;
    }
    return result;
  }
};

int main(){
  int n;
  cin >> n;
  Trie contacts;
  for(int a0 = 0; a0 < n; a0++){
    string op;
    string contact;
    cin >> op >> contact;
    if(op == "add"){
      contacts.add(contact);
    }
    else{
      cout << contacts.count(contact) << endl;
    }
  }
  return 0;
}
