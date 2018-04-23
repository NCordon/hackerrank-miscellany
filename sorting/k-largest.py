#!/usr/bin/python3
# https://leetcode.com/problems/kth-largest-element-in-an-array/
# O(n)

def findKthLargest(nums, k, left, right):
    pivot = nums[left]
    i = left
    j = right
    middle = left - 1

    while i <= j:
        if nums[i] <= nums[left]:
            i += 1
            middle += 1
        elif nums[j] > nums[left]:
            j -= 1
        else:
            # Swap both elements
            nums[i], nums[j] = nums[j], nums[i]


    # Place pivot in the middle of the array
    nums[middle], nums[left] = nums[left], nums[middle]

    if middle == k - 1:
        return nums[middle]
    elif middle >= k:
        return findKthLargest(nums, k, left, middle - 1)
    else:
        return findKthLargest(nums, k, middle + 1, right)





nums = [1, -9, 7, 3, 20]
print("Result: ", findKthLargest(nums, 3, 0, len(nums) - 1))
