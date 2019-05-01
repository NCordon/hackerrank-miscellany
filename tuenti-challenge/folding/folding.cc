#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> intPair;
enum Reflection {L, R, T, B};

intPair reflect_point(intPair& current, Reflection reflection, int width, int height) {
  int x = current.first;
  int y = current.second;
  
  switch (reflection) {
    case R:
    case L:
      x = width - 1 - x;
      break;
    case T:
    case B:
      y = height - 1 - y;
      break;
  }

  return {x, y};
}

bool is_vertical(Reflection reflection) {
  return reflection == T || reflection == B;
}

bool is_horizontal(Reflection reflection) {
  return reflection == L || reflection == R;
}

int main() {
  int C, W, H, F, P;
  char reflection;
  int x_reflections;
  int y_reflections;
  int width;
  int height;
  int x, y;
  int start, end;
  cin >> C;

  for (int i = 1; i <= C; ++i) {
    cin >> W >> H >> F >> P;
    
    vector<Reflection> folds(F);
    vector<intPair> result;
    x_reflections = 0;
    y_reflections = 0;
    
    // Read the folds
    for (int f = 0; f < F; ++f) {
      cin >> reflection;

      switch(reflection) {
        case 'L':
          folds[f] = L;
          ++x_reflections;
          break;
        case 'R':
          folds[f] = R;
          ++x_reflections;
          break;
        case 'T':
          folds[f] = T;
          ++y_reflections;
          break;
        case 'B':
          folds[f] = B;
          ++y_reflections;
          break;
      }
    }
    
    // Read the points
    for (int p = 0; p < P; ++p) {
      cin >> x >> y;
      start = result.size();
      result.push_back({x, y});
      width = W;
      height = H;

      // Iteratively apply the folds
      for (auto& fold : folds) {
        end = result.size();
        
        if (fold == L) {
          for (int i = start; i < end; ++i)
            result[i].first += width;
        } else if (fold == T) {
          for (int i = start; i < end; ++i)
            result[i].second += height;
        }

        if (is_vertical(fold))
          height *= 2;
        else
          width *= 2;
        
        for (int i = start; i < end; ++i)
          result.push_back(reflect_point(result[i], fold, width, height));
      }
    }
    sort(result.begin(), result.end());
    cout << "Case #" << i << ":" << endl;

    for (auto& tuple : result)
      cout << tuple.first << " " << tuple.second << endl;
  }
}
