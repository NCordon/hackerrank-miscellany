// https://leetcode.com/problems/moving-average-from-data-stream
class MovingAverage {
private:
  queue<int> values;
  double average;
  int window_size;
  
public:
  /** Initialize your data structure here. */
  MovingAverage(int size) {
    window_size = size;
    average = 0;
  }
    
  double next(int val) {
    values.push(val);
    int old_size = values.size() - 1;
    int new_size = values.size();
      
    if (values.size() <= window_size) {
      average *= old_size;
      average += val;
      average /= new_size;
    } else {
      average -= values.front() / (1.0 * window_size);
      average += val / (1.0 * window_size);
      values.pop();
    }      
      
    return average;
  }
};
