// https://leetcode.com/problems/trapping-rain-water/
// O(n) algorithmically and in space, where n is the
// length of heights
// The idea is:
//   When we hit a height, if the previous height (current in the code)
//   was lower, slide the maximum height rectangle contained within two
//   columns and placed on top of previous.
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>
#include <iostream>
using namespace std;


int trap(vector<int>& heights) {
  stack<pair<int, int>> previous;
  pair<int, int> prev;
  int width;
  int height;
  int result = 0;
  int current = numeric_limits<int>::max();
  bool keep_sliding;

  for (int i = 0; i < heights.size(); ++i) {
    keep_sliding = true;

    if (heights[i] > current) {
      while (!previous.empty() && previous.top().first >= current && keep_sliding) {
        prev = previous.top();

        if (prev.first <= heights[i])
          previous.pop();
        else
          keep_sliding = false;

        if (prev.first > current) {
          width = i - prev.second - 1;
          height = min(heights[i], prev.first) - current;
          result += width * height;
          current = prev.first;
        }
      }
    }

    previous.push({heights[i], i});
    current = heights[i];
  }

  return result;
}

int main() {
  vector<int> heights = {0,4,0,3,1,1,0,1,1,3,4,0,2};

  /*  _               _
     | |  _         _| |
     | | | |       |   |  _
     | | | |__   __|   | |
    _| |_|    |_|      |_|
    
   */
  
  cout << "Solution: " << trap(heights) << endl;
}
