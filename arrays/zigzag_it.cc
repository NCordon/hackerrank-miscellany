// https://leetcode.com/explore/interview/card/google/65/design-4/479/
class ZigzagIterator {
  bool print_first;
  int first_pos;
  int second_pos;
  vector<int>& first;
  vector<int>& second;
public:
  ZigzagIterator(vector<int>& v1, vector<int>& v2): first(v1), second(v2) {
    print_first = true;
    first_pos = 0;
    second_pos = 0;
  }

  int next() {
    int result;

    if (print_first) {
      print_first = false || !(second_pos < second.size());

      if (first_pos < first.size())
        result = first[first_pos++];
      else
        result = next();
    } else {
      print_first = true && first_pos < first.size();

      if (second_pos < second.size())
        result = second[second_pos++];
      else
        result = next();
    }
    
    return result;
  }

  bool hasNext() {
    return first_pos < first.size() || second_pos < second.size();
  }
};
