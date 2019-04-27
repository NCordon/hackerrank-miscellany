// https://leetcode.com/problems/range-module/solution/
// O(n) solution
struct Range {
  int left;
  int right;
  bool is_empty;
  
  Range() {
    is_empty = true;struct Range {
  int left;
  int right;
  bool is_empty;
  
  Range() {
    is_empty = true;
  }
  
  Range(int left, int right) {
    this->left = left;
    this->right = right;
    is_empty = false;
  }
};

struct interval_comp {
  bool operator() (const Range& a, const Range& b) const{
    return a.left < b.left || a.left == b.left && a.right > b.right;
  }
};

typedef set<Range, interval_comp> Ranges;

// [a_1, a_2[ - [b_1, b_2]
vector<Range> diff(const Range& a, const Range& b) {
  vector<Range> result;
  
  if (b.left <= a.left) {
    if (b.right < a.left)
      result.push_back(a);
    else if (b.right >= a.left && b.right < a.right)
      result.push_back(Range(b.right, a.right));
  } else if (b.left > a.left && b.left < a.right) {
    if (b.right >= a.right)
      result.push_back(Range(a.left, b.left));
    else {
      result.push_back(Range(a.left, b.left));
      result.push_back(Range(b.right, a.right));
    }
  } else {
    result.push_back(a);
  }
  
  return result;
}

Ranges merge(Ranges intervals) {
  Ranges merged;
  auto it = intervals.begin();
  auto insert_it = merged.begin();
  int start, end;
  bool overlap;
  
  while (it != intervals.end()) {
    start = it->left;
    end = it->right;
    overlap = true;
    
    while (overlap) {
      ++it;
      if (it != intervals.end() && end >= it->left)
        end = max(end, it->right);
      else
        overlap = false;
    }
    
    merged.insert(merged.end(), Range(start, end));
  }
  
  return merged;
}

class RangeModule {
private:
  Ranges intervals;
public:

  RangeModule() {}

  void addRange(int left, int right) {
    intervals.insert({left, right});
    intervals = merge(intervals);
  }

  bool queryRange(int left, int right) {
    auto it = intervals.upper_bound(Range(left, right));
    bool result = false;
    
    if (it != intervals.begin()) {
      --it;
      result = it->right >= right;
    }
    
    return result;
  }

  void removeRange(int left, int right) {
    Ranges result;
    Range to_remove(left, right);
    vector<Range> difference;
    
    for (auto& interval : intervals) {
      difference = diff(interval, to_remove);
      
      for (auto& new_interval : difference)
        result.insert(result.end(), new_interval);
    }
    
    intervals = result;
  }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

  }
  
  Range(int left, int right) {
    this->left = left;
    this->right = right;
    is_empty = false;
  }
};

struct interval_comp {
  bool operator() (const Range& a, const Range& b) const{
    return a.left < b.left;
  }
};

typedef set<Range, interval_comp> Ranges;

// [a_1, a_2[ - [b_1, b_2]
vector<Range> diff(const Range& a, const Range& b) {
  vector<Range> result;
  
  if (b.left <= a.left) {
    if (b.right < a.left)
      result.push_back(a);
    else if (b.right >= a.left && b.right < a.right)
      result.push_back(Range(b.right, a.right));
  } else if (b.left > a.left && b.left < a.right) {
    if (b.right >= a.right)
      result.push_back(Range(a.left, b.left));
    else {
      result.push_back(Range(a.left, b.left));
      result.push_back(Range(b.right, a.right));
    }
  } else {
    result.push_back(a);
  }
  
  return result;
}

Ranges merge(Ranges intervals) {
  Ranges merged;
  auto it = intervals.begin();
  auto insert_it = merged.begin();
  int start, end;
  bool overlap;
  
  while (it != intervals.end()) {
    start = it->left;
    end = it->right;
    overlap = true;
    
    while (overlap) {
      ++it;
      if (it != intervals.end() && end >= it->left)
        end = max(end, it->right);
      else
        overlap = false;
    }
    
    merged.insert(merged.end(), Range(start, end));
  }
  
  return merged;
}

class RangeModule {
private:
  Ranges intervals;
public:

  RangeModule() {}

  void addRange(int left, int right) {
    intervals.insert({left, right});
    intervals = merge(intervals);
  }

  bool queryRange(int left, int right) {
    auto it = intervals.upper_bound(Range(left, right));
    bool result = false;
    
    if (it != intervals.begin()) {
      --it;
      result = it->right >= right;
    }
    
    return result;
  }

  void removeRange(int left, int right) {
    Ranges result;
    Range to_remove(left, right);
    vector<Range> difference;
    
    for (auto& interval : intervals) {
      difference = diff(interval, to_remove);
      
      for (auto& new_interval : difference)
        result.insert(result.end(), new_interval);
    }
    
    intervals = result;
  }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
