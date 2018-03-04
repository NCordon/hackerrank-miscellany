// https://www.geeksforgeeks.org/painters-partition-problem/
#include <bits/stdc++.h>
using namespace std;

// O(log(sum(boards)) * sum(boards)) solution

bool IsSolution(int value, const vector<int>& boards, int num_painters) {
  int necessary_painters = 0;
  int current = 0;

  if (!boards.empty()) {
    necessary_painters = 1;
  }
  
  for (int i = 0; i < boards.size() && necessary_painters <= num_painters; ++i) {
    if (current + boards[i] <= value) {
      current += boards[i];
    } else {
      current = boards[i];
      ++necessary_painters;
    }
  }

  return necessary_painters <= num_painters;
}


int MaxPartition(const vector<int>& boards, int num_painters) {
  int upper = accumulate(boards.begin(), boards.end(), 0);
  int lower = upper / num_painters;
  int middle;
  int min_max;
  
  while (lower < upper) {
    middle = (lower + upper) / 2;

    if (IsSolution(middle, boards, num_painters)) {
      min_max = middle;
      upper = middle;
    } else {
      lower = middle + 1;
    }
  }


  return min_max;
}


int main() {
  int num_painters;
  int num_boards;

  cin >> num_painters >> num_boards;

  vector<int> boards(num_boards);
  
  for (int i = 0; i < num_boards; i++) {
    cin >> boards[i];
  }


  cout << MaxPartition(boards, num_painters) << endl;
}
