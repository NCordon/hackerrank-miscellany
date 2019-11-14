// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
// O(n) solution algorithmically and in space
/**
 * Definition for a binary tree node.
 * class TreeNode(var _value: Int) {
 *   var value: Int = _value
 *   var left: TreeNode = null
 *   var right: TreeNode = null
 * }
 */
object Solution {
  def countNodes(node: TreeNode, k: Int): (Int, Option[Int]) = {
    if (node == null) {
      return (0, None)
    }
    
    if (node.left == null && node.right == null) {
      if (k == 1) 
        (1, Some(node.value)) 
      else 
        (1, None)
    } else {
      val (left, solLeft) = countNodes(node.left, k)
      
      if (!solLeft.isEmpty)
        return (-1, solLeft)
      if (left == k - 1)
        return (-1, Some(node.value))
      
      val (right, solRight) = countNodes(node.right, k - left - 1)
      return (left + right + 1, solRight)
    }
  }
  
  def kthSmallest(root: TreeNode, k: Int): Int = {
    val (_, sol) = countNodes(root, k)
    sol match {
      case Some(node) => node
      case None => -1
    }
  }
}
