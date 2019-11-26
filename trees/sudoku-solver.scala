// https://leetcode.com/problems/sudoku-solver/submissions/
// DFS with pruning
object Solution {
  val dim = 9
  
  @inline def squareFor(i: Int, j: Int): Int = {
    i / 3 * 3 + j / 3 
  }
  
  def solveSudoku(board: Array[Array[Char]]): Unit = {
    val lines = Array.fill(dim)((1 to dim).toSet)
    val cols = Array.fill(dim)((1 to dim).toSet)
    val squares = Array.fill(dim)((1 to dim).toSet)
    
    (0 to (dim - 1)).foreach { i =>
      (0 to (dim - 1)).foreach { j =>
        if (board(i)(j) != '.') {
          val current : Int = board(i)(j) - '0'
          val k = squareFor(i, j)
          lines(i) -= current
          cols(j) -= current
          squares(k) -= current
        }
      }
    }
    
    def solve(i: Int, j: Int): Boolean = {
      if (i == dim)
        return true
      else {
        val (ii, jj) = if (j + 1 < dim) (i, j + 1) else (i + 1, 0)
        
        if (board(i)(j) != '.') {
          return solve(ii, jj)
        } else {
          val k = squareFor(i, j)
          val toUse = (lines(i) & cols(j) & squares(k)).toArray
          if (toUse.isEmpty) {
            return false
          } else {

            @annotation.tailrec
            def exploreSquare(l: Int): Boolean = {
              if (l == toUse.length) {
                false
              } else {
                val current = toUse(l)
                board(i)(j) = (current + '0').toChar;
                lines(i) -= current
                cols(j) -= current
                squares(k) -= current

                if (solve(ii, jj))
                  return true
                else {
                  board(i)(j) = '.'
                  lines(i) += current
                  cols(j) += current
                  squares(k) += current
                  exploreSquare(l + 1)
                }
              }
            }

            exploreSquare(0)
          }
        }
      }
    }
    
    solve(0, 0)
  }
}
