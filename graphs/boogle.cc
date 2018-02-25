#include <bits/stdc++.h>
using namespace std;

struct Node {
  char is_word = false;
  unordered_map<char, Node*> children;
};

class Trie {
  Node* root;

  void Print(Node *root, string& current_word) {
    if(root->is_word)
      cout << current_word << endl;
    
    for (auto child : root->children) {
      current_word.push_back(child.first);
      Print(child.second, current_word);
      current_word.pop_back();
    }
  }

public:
  Trie() {
    root = new Node;
  }
  
  void AddWord(string word) {
    Node* current = root;

    for (char letter : word) {
      if (current->children.count(letter) == 0)
        current->children[letter] = new Node;

      current = current->children[letter];
    }

    current->is_word = true;
  }

  Node* GetRoot(){
    return root;
  }

  void PrintWords() {
    string current_word = "";
    Print(root, current_word);
  }
    
};


void FindWords(vector<vector<char> >& boggle, vector<vector<bool> >& visited, Node* root,
               int i, int j, int N, int M, string& current_word, vector<string>& result) {
  visited[i][j] = true;
  
  for (auto child : root->children) {
    if (boggle[i][j] == child.first) {
      current_word.push_back(child.first);

      if (child.second->is_word)
        result.push_back(current_word);
      
      for (int k = i - 1; k <= i + 1; k++) {
        for (int q = j - 1; q <= j + 1; q++) {
          if (0 <= k && k < N && 0 <= q && 0 < M && !visited[k][q]) {
            FindWords(boggle, visited, child.second, k, q, N, M, current_word, result);
          }
        }
      }
      current_word.pop_back();
    }
  }

  visited[i][j] = false;
}

vector<string> WordsInBoggle(vector<string> words, vector<vector<char> > boggle) {
  Trie dictionary;
  vector<vector<bool> > visited(boggle.size(), vector<bool>(boggle[0].size(), false));
  vector<string> result;
  list<string> unique_result;
  string current_word;

  for (string word : words){
    dictionary.AddWord(word);
  }

  //dictionary.PrintWords();
  
  if (!boggle.empty()) {
    for (int i = 0; i < boggle.size(); i++) {
      for (int j = 0; j < boggle[0].size(); j++) {
        FindWords(boggle, visited, dictionary.GetRoot(), i, j,
                  boggle.size(), boggle[0].size(), current_word, result);
      }
    }
  }    

  // Make each word appear only one time in result
  sort(result.begin(), result.end());
  unique_result = list<string>(result.begin(), result.end());
  unique_result.unique();
  result = vector<string>(unique_result.begin(), unique_result.end());
  
  return result;
}


int main() {
  int T;
  int x;
  int n;
  int m;
  cin >> T;
  
  for (int t; t < T; t++) {
    cin >> x;
    vector<string> dictionary(x);
    
    for (int i = 0; i < x; i++)
      cin >> dictionary[i];
    
    cin >> n >> m;
    vector<vector<char> > boggle(n, vector<char>(m));
    
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> boggle[i][j];   
      }
    }
    
    vector<string> words_boggle = WordsInBoggle(dictionary, boggle);
    copy(words_boggle.begin(), words_boggle.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
  }
}
