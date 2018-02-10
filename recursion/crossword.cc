// https://www.hackerrank.com/challenges/crossword-puzzle/problem
#include <bits/stdc++.h>
using namespace std;

struct CrosswordGap : public pair<int, int>{
  int length;
  bool horizontal;
};

class Crossword{
private:
  vector<string> board;
  list<CrosswordGap> gaps;
  
  void computeGaps(bool horizontal){
    int length;
    int limit_i;
    int limit_j;
    int l,k;
    CrosswordGap current_gap;
    current_gap.horizontal = horizontal;
    
    if(horizontal){
      limit_i = board.size();
      limit_j = board[0].size();
    }
    else{
      limit_i = board[0].size();
      limit_j = board.size();
    }
      
      
    for(int i = 0; i < limit_i; i++){
      length = 0;
      
      for(int j = 0; j < limit_j; j++){
        if(horizontal){
          l = i;
          k = j;
        }
        else{
          l = j;
          k = i;
        }
          
        if(board[l][k] == '-'){
          if(length == 0){
            current_gap.first = l;
            current_gap.second = k;
          }
          length++;
        }
        else{
          if(length > 1){
            current_gap.length = length;
            gaps.push_back(current_gap);
          }
          
          length = 0;
        }
      }
      
      if(length > 1){
        current_gap.length = length;
        gaps.push_back(current_gap);
      }
    }
  }
  
public:
  Crossword(vector<string> board){
    this->board = board;
    // compute both horizontal and vertical gaps
    computeGaps(true);
    computeGaps(false);
  }

  bool fillFirstGap(string word){
    bool able_to_fill = true;
    CrosswordGap gap;
    char current_pos;
    
    if(!gaps.empty()){
      gap = gaps.front();
      
      if(gap.length == word.size()){
        for(int j = 0; j < gap.length && able_to_fill; j++){
          current_pos = board[gap.first + (gap.horizontal ? 0 : j)]
            [gap.second + (gap.horizontal ? j : 0)];
          if(current_pos != word[j] && current_pos != '-')
            able_to_fill = false;
        }
      }
      else{
        able_to_fill = false;
      }
    
      if(able_to_fill){
        for(int j = 0; j < gap.length && able_to_fill; j++)
          board[gap.first + (gap.horizontal ? 0 : j)]
               [gap.second + (gap.horizontal ? j : 0)] = word[j];

        gaps.erase(gaps.begin());
      }
    } 
    
    return able_to_fill;
  }
  
  bool isSolved(){
    return gaps.empty();
  }
  
  void printBoard(){
    for(string row : board){
      cout << row << endl;
    }
  }
  
};

void solve_crossword(vector<string>& board, list<string>& words){
  stack<pair<Crossword, list<string> > > to_explore;
  to_explore.push({Crossword(board), words});
  bool solved = false;
  
  while(!to_explore.empty() && !solved){
    Crossword current = to_explore.top().first;
    words = to_explore.top().second;
    to_explore.pop();
    
    if(current.isSolved()){
      solved = true;
      current.printBoard();
    }


    if(!solved){
      list<string>::iterator it = words.begin();
      
      while(it != words.end()){
        string current_word = *it;
        it = words.erase(it);
        Crossword old_current = current;
  
        if(old_current.fillFirstGap(current_word))
          to_explore.push({old_current, words});
        
        it = words.insert(it, current_word);
        it++;
      }
    }
  }
}

int main(){
  string row;
  vector<string> board;
  string words;
  list<string> word_collection;
  
  for(int i = 0; i < 10; i++){
    cin >> row;
    board.push_back(row);
  }
  
  cin >> words;
  words += ";";
  string current;
  
  for(int i = 0; i < words.size(); i++){
    if(words[i] != ';')
      current += words[i];
    else{
      word_collection.push_back(current);
      current = "";
    }
  }
  
  solve_crossword(board, word_collection);
  
  return 0;
}
