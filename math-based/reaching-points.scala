// https://leetcode.com/problems/reaching-points/submissions/
// O(n) solution algorithmically (where n is the largest from tx and ty) and O(1) in space
object Solution {
  def reachingPoints(sx: Int, sy: Int, tx: Int, ty: Int): Boolean = {
    // Solution consists in retracing the only possible path back from the
    // target point (tx, ty), since we can only subtract the lowest one to
    // the largest one, since sx, sy, tx, ty are numbers greater than 1
    //
    // Note that if we did a backtracking from (sx, sy) to try and reach (tx, ty)
    // we would have a huge tree:
    //
    //                         (sx + 2sy, sy)       ...
    //                        /
    //            (sx + sy, sy)
    //           /            \
    //   (sx, sy)              (sx + sy, sx + 2sy)  ...
    //           \
    //            (sx, sy + sx)
    //
    @annotation.tailrec
    def toStart(x: Int, y: Int): Boolean = {
      if (x == sx && y == sy)
        return true
      if (x < sx || y < sy)
        return false
      if (x < y)
        toStart(x, y - x)
      else
        toStart(x - y, y)
    }
    
    toStart(tx, ty)
  }
}
