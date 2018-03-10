// https://leetcode.com/problems/merge-intervals
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
bool IntervalSort(const Interval& a, const Interval& b) {
  return a.start < b.start;
}

class Solution {  
public:
  vector<Interval> merge(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), IntervalSort);
    int i = 0;
    int j;
    vector<Interval> result;
    
    while (i < intervals.size()) {
      j = i;
      Interval temp;
      temp.start = intervals[i].start;
      temp.end = intervals[i].end;
      
      while (j < intervals.size() &&
             intervals[j].start <= temp.end) {
        temp.end = max(intervals[j].end, temp.end);
        ++j;
      }
      
      result.push_back(temp);
      i = j;
    }
    
    return result;      
  }
};
