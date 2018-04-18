# https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
# O(n) solution, being n number of nodes
#
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def flatten(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """

        if root != None:
            self.flatten(root.left)
            self.flatten(root.right)

          last = root
          current = root.left

          while current != None:
              last = current
              current = current.right

          last.right = root.right

          if last != root:
              root.right = root.left

          root.left  = None
