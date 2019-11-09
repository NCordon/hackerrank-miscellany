// https://leetcode.com/problems/couples-holding-hands/submissions/
// We iterate the array A advancing in the even positions, keeping another
// array P which says that the i-th element is in the position P(i)
// For each position j, we try to complete the pair, either looking for
// the couple of A(j) or A(j + 1), depending on whether any of them is
// an even number (the lower bound of a couple)
// O(n) solution algorithmically and in space
object Solution {
  def minSwapsCouples(row: Array[Int]): Int = {
    val positions = Array.ofDim[Int](row.length)

    row.zipWithIndex.foreach { case (elem, i) =>
      positions(elem) = i
    }

    return minSwaps(row, positions, 0, 0)
  }

  def findAndSwap(positions: Array[Int], row: Array[Int], i: Int, j: Int): Unit = {
    val a = positions(i)
    val b = positions(j)
    val elem = row(a)
    row(a) = row(b)
    row(b) = elem
    positions(i) = positions(j)
    positions(j) = a
  }

  @annotation.tailrec
  def minSwaps(row: Array[Int], positions: Array[Int], i: Int, result: Int): Int = {
    if (i < row.length) {
      val a = row(i)
      val b = row(i + 1)

      // If the first two positions are a couple, just go to the
      // next possible place for a couple, no need to change nothing here
      if ((a == b + 1 || b == a + 1) && Math.min(a, b) % 2 == 0) {
        return minSwaps(row, positions, i + 2, result)
      } else {
        // Look for the couple for a and swap it with the next element
        val toSwap = if (a % 2 == 0) a + 1 else a - 1
        findAndSwap(positions, row, toSwap, b)
        return minSwaps(row, positions, i + 2, result + 1)
      }
    } else {
      return result
    }
  }
}
