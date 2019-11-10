// https://leetcode.com/problems/largest-rectangle-in-histogram/
// O(n) solution algorithmically and in space
object Solution {
  import Math._
  type Stack = List[(Int, Int)]

  def largestRectangleArea(heights: Array[Int]): Int = {
    // Process the stack so that it is always sorted increasingly
    @annotation.tailrec
    def processStack(
      stack: Stack,
      height: Int,
      from: Int,
      last: Int,
      maximum: Int
    ): (Stack, Int) = {
      if (!stack.isEmpty && stack.head._1 >= height) {
        val (h, i) = stack.head
        val result = max(maximum, h * (from - i))
        processStack(stack.tail, height, from, i, result)
      } else {
        ((height, last)::stack, maximum)
      }
    }

    // While we can introduce things in the stack, do it, getting the
    // current state of the stack and the maximum to the moment
    // Else, process the remainings of the stack
    @annotation.tailrec
    def computeAreaRec(i: Int, maximum: Int, stack: Stack): Int = {
      if (i < heights.length) {
        val h = heights(i)
        val (next, result) = processStack(stack, h, i, i, maximum)
        computeAreaRec(i + 1, result, next)
      } else {
        val (_, result) = processStack(stack, 0, i, i, maximum)
        result
      }
    }

    computeAreaRec(0, 0, List.empty)
  }
}
