# @problem: 189. Rotate Array
# @file: rotate_array.py
# @url: https://leetcode-cn.com/problems/rotate-array
# @description:
#
# Given an array, rotate the array to the right by k steps, where k is
# non-negative.
# Example 1:
# Input: [1,2,3,4,5,6,7] and k = 3
# Output: [5,6,7,1,2,3,4]
# Explanation:
# rotate 1 steps to the right: [7,1,2,3,4,5,6]
# rotate 2 steps to the right: [6,7,1,2,3,4,5]
# rotate 3 steps to the right: [5,6,7,1,2,3,4]
#
# Example 2:
# Input: [-1,-100,3,99] and k = 2
# Output: [3,99,-1,-100]
# Explanation:
# rotate 1 steps to the right: [99,-1,-100,3]
# rotate 2 steps to the right: [3,99,-1,-100]
#
# Note:
#
# Try to come up as many solutions as you can, there are at least 3
# different ways to solve this problem.
# Could you do it in-place with O(1) extra space?
#
# @author: Du Ang
# @date: Sep 09, 2019

from typing import List


# Reverse
class Solution:
    """Reverse three times."""

    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        # reverse all elements
        self.reverse(nums, 0, len(nums) - 1)
        # reverse the first k elements
        self.reverse(nums, 0, k - 1)
        # reverse the last n-k elements
        self.reverse(nums, k, len(nums) - 1)

    def reverse(self, nums: List[int], left: int, right: int) -> None:
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1


class Solution2:
    """
    Brute force: move the last one to the start for k times.
    For list, we just need pop and insert.
    For array, we need move all elements one by one.
    """

    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        for _ in range(k):
            nums.insert(0, nums.pop())


class Solution3:
    """Using extra array for copy and paste"""

    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        # copy and paste
        nums[:] = nums[n - k :] + nums[: n - k]


class Solution4:
    """Cyclic replacement, controlled with gcd"""

    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        else:
            # if the gcd of (n, k) is not 1, we need change the start to cover all
            for i in range(self.gcd(n, k)):
                self.cyclic_replacement(nums, k, start=i)

    def cyclic_replacement(self, nums: List[int], k: int, start=0) -> None:
        cur = start
        prev = nums[cur]
        n = len(nums)
        while True:
            cur = (cur + k) % n
            if cur == start:
                nums[cur] = prev
                break
            temp = nums[cur]
            nums[cur] = prev
            prev = temp

    def gcd(self, a: int, b: int) -> int:
        if a < b:
            return self.gcd(b, a)
        else:
            if a % b == 0:
                return b
            else:
                return self.gcd(b, a % b)


class Solution5:
    """Cyclic replacement, controlled with count"""

    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        else:
            start, count = 0, 0
            while True:
                # cyclic replacement with the start
                cur = start
                prev = nums[cur]
                while True:
                    cur = (cur + k) % n
                    if cur == start:
                        nums[cur] = prev
                        count += 1
                        break
                    temp = nums[cur]
                    nums[cur] = prev
                    count += 1
                    prev = temp
                # check if all elements have been covered
                if count < n:
                    # no, repeat cyclic replacement with the next start
                    start += 1
                else:
                    # yes, all elements covered
                    break


if __name__ == "__main__":
    k = 4
    array = [1, 2, 3, 4, 5, 6]
    Solution().rotate(array, k)
    print(array)
    array = [1, 2, 3, 4, 5, 6]
    Solution2().rotate(array, k)
    print(array)
