// https://leetcode.com/problems/n-queens-ii
// Branch and bound to solve the N-queens problem
object Solution {
  // If a square is marked in the board, it cannot be occupied
  type Board = Set[(Int, Int)]
  
  def placeQueen(board: Board, i: Int, j: Int, n: Int): Board = {
    val withCol = ((i + 1) to (n - 1)).foldRight(board) { case(r, current) =>
      current + ((r, j))
    }
    val withRDiagonal = ((j + 1) to (n - 1)).foldRight(withCol) { case(c, current) =>
      current + ((i + c - j, c))
    }
    val withLDiagonal = (0 to (j - 1)).foldRight(withRDiagonal) { case(c, current) =>
      current + ((i + j - c, c))
    }
    withLDiagonal
  }
  
  def totalNQueens(n: Int): Int = {
    
    def solve(i: Int, board: Board, result: Int): Int = {
      if (i == n) {
        return result + 1
      } else {
        @annotation.tailrec
        def exploreRow(j: Int, sols: Int): Int = {
          if (j == n) {
            sols
          } else if (!board.contains(i, j)) {
            val nextBoard = placeQueen(board, i, j, n)
            val nextSols = solve(i + 1, nextBoard, sols)
            exploreRow(j + 1, nextSols)
          } else {
            exploreRow(j + 1, sols)
          }
        }
        
        exploreRow(0, result)
      }
    }
    
    solve(0, Set.empty, 0)
  }
}
