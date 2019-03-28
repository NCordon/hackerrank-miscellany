// https://leetcode.com/problems/insert-interval/
// O(n) solution where n is the length of the intervals array
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    int s, e;
    vector<Interval> sorted;
    vector<Interval> result;
    bool used = false;
    
    for (auto& interval : intervals) {
      s = interval.start;
      e = interval.end;
      
      if (s >= newInterval.start && !used) {
        used = true;
        sorted.push_back(newInterval);
      }
      
      sorted.push_back(interval);
    }
    
    if (!used)
      sorted.push_back(newInterval);
    
    int i = 0;
    
    while (i < sorted.size()) {
      s = sorted[i].start;
      e = sorted[i].end;
      
      ++i;
      
      while (i < sorted.size() && e >= sorted[i].start) {
        e = max(e, sorted[i].end);
        ++i;
      }
      
      result.push_back(Interval(s, e));
    }
    
    return result;
  }
};
