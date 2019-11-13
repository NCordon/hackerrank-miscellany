// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
// Solution based on binary search
// We know that either the array is sorted, which happens
// if the first element, a, is lower than the last one,
// b, or the array is splitted into two halves wich are sorted
// (respectively). There is an exception, when a == b we cannot
// ensure we are not in this case 11111011111 and we have to do
// linear search.
// O(n) in the worst case, O(log n) in the average
object Solution {
  def findMin(nums: Array[Int]): Int = {
    val last = nums.length - 1
    if (nums(0) < nums(last)) {
      nums(0)
    } else if (nums(0) == nums(last)) {
      nums.min
    } else {

      @annotation.tailrec
      def findFirstLower(target: Int, lower: Int, upper: Int): Int = {
        if (lower == upper) {
          nums(lower)
        } else {
          val middle = (lower + upper) / 2

          if (target <= nums(middle)) {
            findFirstLower(target, middle + 1, upper)
          } else {
            findFirstLower(nums(middle), lower, middle)
          }
        }
      }

      findFirstLower(nums(0), 0, last)
    }
  }
}
