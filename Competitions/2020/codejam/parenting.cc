#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct interval {
  int start;
  int end;
  int pos;
};

bool intervalOrder(interval a, interval b) {
  return a.start < b.start;
}

int main() {
  int t;
  // read number of cases
  cin >> t;
  
  for (int i = 1; i <= t; ++i) {
    int n;
    cin >> n;
    int jamie = 0, cameron = 0;
    bool impossible = false;
    string result(n, 'C');
    vector<interval> intervals(n);
    
    for (int j = 0; j < n; ++j) {
      cin >> intervals[j].start;
      cin >> intervals[j].end;
      intervals[j].pos = j;
    }

    sort(intervals.begin(), intervals.end(), intervalOrder);
    
    for (int j = 0; j < n && !impossible; ++j) {
      int start = intervals[j].start;
      int end = intervals[j].end;
      int pos = intervals[j].pos;

      if (start >= jamie) {
        result[pos] = 'J';
        jamie = end;
      } else if (start >= cameron) {
        result[pos] = 'C';
        cameron = end;
      } else {
        result = "IMPOSSIBLE";
        impossible = true;
      }
    }

    cout << "Case #" << i << ": " << result << endl;
  }

}
