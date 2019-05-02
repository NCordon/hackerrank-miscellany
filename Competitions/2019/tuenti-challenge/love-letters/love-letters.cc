#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef vector<vector<char>> Layout;
typedef pair<int, int> Tuple;

Tuple compute_offset(Layout& layout, char current, char target) {
  Tuple target_index;
  Tuple current_index;
  
  for (int i = 0; i < layout.size(); ++i) {
    for (int j = 0; j < layout[i].size(); ++j) {
      if (layout[i][j] == target)
        target_index = {i, j};
      if (layout[i][j] == current)
        current_index = {i, j};
    }
  }

  return {
    target_index.first - current_index.first,
    target_index.second - current_index.second
  };
}

string decrypt(string message, Layout& layout, Tuple offset) {
  int row_length = layout[0].size();
  int current_row;
  int current_col;
  int dec_row;
  int dec_col;
  int num_rows = layout.size();
  
  for (char& current : message) {
    if (current != ' ') {
      current_row = -1;
      current_col = -1;
      
      for (int i = 0; i < layout.size() && current_row == -1; ++i) {
        for (int j = 0; j < layout[i].size() && current_col == -1; ++j) {
          if (layout[i][j] == current) {
            current_row = i;
            current_col = j;
          }
        }
      }

      dec_row = (current_row + offset.first + num_rows) % num_rows;
      dec_col = (current_col + offset.second + row_length) % row_length;
      current = layout[dec_row][dec_col];
    }
  }

  return message;
}

int main() {
  int C;
  Tuple offset;
  char sender;
  string message;
  Layout layout = {
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
    {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';'},
    {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '-'}
  };
  cin >> C;
  
  for (int i = 1; i <= C; ++i) {    
    cin >> sender;
    getchar();
    getline(cin, message);

    offset = compute_offset(layout, message.back(), sender);

    cout << "Case #" << i  << ": " << decrypt(message, layout, offset) << endl;
  }
}
