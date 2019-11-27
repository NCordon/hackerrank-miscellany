// https://leetcode.com/problems/n-queens
// Branch and bound to solve the N-queens problem
object Solution {
  // A -1 represents a non-valid square, 1 a queen, 0 non-occupied
  type Board = Array[Array[Int]]
  type Solution = List[String]
  
  def toSolution(board: Board): Solution = {
    board.map { row =>
      String.join(
        "",
        row.map { e =>
          if (e == 1) 'Q' else '.'
        }
      )
    }.toList
  }
  
  def placeQueen(board: Board, i: Int, j: Int): Board = {
    board.toIterator.zipWithIndex.map { case (row, ii) =>
      row.toIterator.zipWithIndex.map { case (elem, jj) =>
        if (i == ii && j == jj)
          1
        else if (i == ii || j == jj || Math.abs(i - ii) == Math.abs(j - jj))
          -1
        else
          elem
      }.toArray
    }.toArray
  }
  
  def solveNQueens(n: Int): List[Solution] = {
    val init = Array.fill(n)(Array.fill(n)(0))
    
    def solve(i: Int, board: Board, result: List[Solution]): List[Solution] = {
      if (i == n) {
        return toSolution(board)::result
      } else {
        @annotation.tailrec
        def exploreRow(j: Int, sols: List[Solution]): List[Solution] = {
          if (j == n) {
            sols
          } else if (board(i)(j) == 0) {
            val nextBoard = placeQueen(board, i, j)
            val nextSols = solve(i + 1, nextBoard, sols)
            exploreRow(j + 1, nextSols)
          } else {
            exploreRow(j + 1, sols)
          }
        }
        
        exploreRow(0, result)
      }
    }
    
    solve(0, init, List.empty)
  }
}
