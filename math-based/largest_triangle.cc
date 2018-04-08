// https://leetcode.com/problems/largest-triangle-area/
// O(n³) where n is number of points
class Solution {
  template<typename T, typename U>
  double dist(vector<T>& x, vector<U>& y) {
    return sqrt( (x[0]-y[0]) * (x[0]-y[0]) +
                 (x[1]-y[1]) * (x[1]-y[1]) );
  }
public:
  double largestTriangleArea(vector<vector<int>>& points) {
    vector<int> x, y, z;
    vector<double> w(2);
    double result = 0;
    double base, height, area, r;

    for (int i = 0; i < points.size(); ++i) {
      for (int j = i + 1; j < points.size(); ++j) {
        for (int k = j + 1; k < points.size(); ++k) {
          x = points[i];
          y = points[j];
          z = points[k];

          // |x - y| is the base of rectangle
          base = dist<int, int>(x, y);

          // Compute height with intersection of line 
          // joining x and y and perpendicular line to 
          // x-y segment that passes through z
          
          r = ( (y[0]-x[0]) * (z[1]-x[1]) -
                (y[1]-x[1]) * (z[0]-x[0]) ) / (base * base);

          w[0] = z[0] + r * (y[0]-x[0]);
          w[1] = z[1] + r * (x[1]-y[1]);

          height = dist<int, double>(z, w);
          area = 0.5 * height * base;

          if (area > result)
            result = area;
        }
      }
    }

    return result;
  }
};
