// https://leetcode.com/problems/combination-sum/
object Solution {
  def combinationSum(candidates: Array[Int], target: Int): List[List[Int]] = {
    val result = Array.fill(target + 1)(List.empty[List[Int]])
    result(0) = List(List.empty[Int])
    
    candidates.foreach { x =>
      (0 to target - x).foreach { i =>
        if (!result(i).isEmpty) {
          result(i + x) = result(i + x) ++ result(i).map { prev => x::prev }
        }
      }
    }
    
    result(target)
  }
}
