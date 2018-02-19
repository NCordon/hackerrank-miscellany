// https://www.hackerrank.com/challenges/largest-rectangle/problem
#include <bits/stdc++.h>
using namespace std;

long long MaxAreaRectangle(long n, vector<long> heights) {
  long long max_area = numeric_limits<long long>::min();
  // first = position from where we can slide
  // second = height to slide
  stack<pair<long, long> > lower_heights;
  long pos_slide;
  long height_slide;
  heights.push_back(0);
  
  for (int i = 0; i <= n; i++) {
    pos_slide = i;
    
    while (!lower_heights.empty() &&
           lower_heights.top().second >= heights[i]) {
      pos_slide = lower_heights.top().first;
      height_slide = lower_heights.top().second;
      max_area = max(max_area, (i - pos_slide) * height_slide * 1LL);
      lower_heights.pop();
    }
    
    lower_heights.push({pos_slide, heights[i]});
  }
  
  return max_area;
}


int main() {
  long n;
  cin >> n;
  vector<long> heights(n);
  
  for (int i = 0; i < n; i++)
    cin >> heights[i];
  
  cout << MaxAreaRectangle(n, heights) << endl;
  
}
