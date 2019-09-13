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
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        # reverse all elements
        for i in range(n//2):
            nums[i], nums[n-1-i] = nums[n-1-i], nums[i]
        # reverse the first k elements
        for i in range(k//2):
            nums[i], nums[k-1-i] = nums[k-1-i], nums[i]
        # reverse the last n-k elements
        for i in range((n-k)//2):
            nums[k+i], nums[k+(n-k-1-i)] = nums[k+(n-k-1-i)], nums[k+i]


# Cyclic replacement, controlled with count
class Solution4:
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


# Cyclic replacement, controlled with gcd
class Solution3:
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


# Using extra array for copy and paste
class Solution2:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        if k == 0:
            return
        # copy and paste
        nums[:] = nums[n-k:] + nums[:n-k]
        

# Brute force: move the last one to the start for k times
# for list, we just need pop and insert
# for array, we need move all elements one by one
class Solution1:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        for _ in range(k):
            nums.insert(0, nums.pop())


if __name__ == '__main__':
    k = 4
    array = [1, 2, 3, 4, 5, 6]
    Solution().rotate(array, k)
    print(array)
    array = [1, 2, 3, 4, 5, 6]
    Solution2().rotate(array, k)
    print(array)

