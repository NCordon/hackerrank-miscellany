// https://leetcode.com/problems/sort-transformed-array/
class Solution {
  int a;
  int b;
  int c;
  
  int f(int x) {
    return a*x*x + b*x + c;
  }
  
public:
  vector<int> sortTransformedArray(vector<int>& v, int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
    vector<int> result;
    int i = 0;
    int j = v.size() - 1;
    double axis;

    if (a == 0) {
      if (b > 0) {
        for (int i = 0; i < v.size(); ++i)
          result.push_back(f(v[i]));
      } else {
        for (int i = v.size() - 1; i >= 0; --i)
          result.push_back(f(v[i]));
      }
    } else {
      axis = -b / (2.0 * a);
      
      while(i <= j) {
        if (fabs(axis - v[i]) > fabs(axis - v[j])) {
          result.push_back(f(v[i]));
          ++i;
        } else{
          result.push_back(f(v[j]));
          --j;
        }
      }

      if (a > 0)
        reverse(result.begin(), result.end());
    }

    return result;
  }
};
