// https://leetcode.com/problems/word-search-ii/
// Solution using a trie
typedef vector<vector<char>> Board;
typedef vector<vector<bool>> Visited;

struct Node {
  unordered_map<char, Node*> children;
  bool leaf;
  
  Node() {
    leaf = false;
  }
  
  void is_leaf() {
    leaf = true;
  }
};

class Trie {
public:
  Node* root;
  
  Trie() {
    root = new Node;
  }
  
  void add(const string& word) {
    Node* current = root;
    
    for (char c : word) {
      if (current->children.count(c) == 0)
        current->children[c] = new Node;
      
      current = current->children[c];
    }
    
    current->is_leaf();
  }
};

class Solution {
  vector<pair<int,int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
  
public:
  void find_rec(Board& board, int i, int j, 
                int n, int m, Visited& visited,
                pair<char, Node*> child, string word,
                unordered_set<string>& found) {
    if (0 <= i && i < n && 0 <= j && j < m && !visited[i][j]) {
      if (board[i][j] == child.first) {
        word += board[i][j];
        visited[i][j] = true;
        
        if (child.second->leaf)
          found.insert(word);

        auto children = child.second->children;
        
        for (auto child : children)
          for (int k = 0; k < dirs.size(); ++k)
            find_rec(board, i + dirs[k].first, j + dirs[k].second, 
                     n, m, visited, child, word, found);
        
        visited[i][j] = false;
        word.pop_back();
      }
    }
  }
  
  vector<string> find_words(vector<vector<char>>& board, 
                            vector<string>& words) {
    int n = board.size();
    int m;
    Visited visited;
    unordered_set<string> found_words;
    Trie trie;
    
    for (string& word : words)
      trie.add(word);
    
    if (n > 0) {
      m = board[0].size();
      visited = Visited(n, vector<bool> (m, false));
    }
    
    if (trie.root != NULL) {
      auto children = trie.root->children;
      
      for (auto child : children)
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < m; ++j)
            find_rec(board, i, j, n, m, visited, child, "", found_words);
    }
    
    return vector<string>(found_words.begin(), found_words.end());
  }
};
