# -*- coding:utf-8 -*-
# 题目描述
# 在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但
# 不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复
# 的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重
# 复的数字2。


# 利用所有数字都在0到n-1范围内这个条件，如果没有任何元素重复，排序后数值应跟下标对应
# 时间 O(n)，空间 O(1)
class Solution:
    # 这里要特别注意~找到任意重复的一个值并赋值到duplication[0]
    # 函数返回True/False
    def duplicate(self, numbers, duplication):
        # write code here
        n = len(numbers)
        if n <= 1:
            return False
        i = 0
        while i < n:
            if numbers[i] == i:
                i += 1
            elif numbers[i] == numbers[numbers[i]]:
                duplication[0] = numbers[i]
                return True
            else:
                temp = numbers[i]
                numbers[i] = numbers[temp]
                numbers[temp] = temp
        return False
        

# 哈希表
# 时间 O(n)，空间 O(n)
class Solution2:
    # 这里要特别注意~找到任意重复的一个值并赋值到duplication[0]
    # 函数返回True/False
    def duplicate(self, numbers, duplication):
        # write code here
        s = set()
        for n in numbers:
            if n in s:
                duplication[0] = n
                return True
            else:
                s.add(n)
        return False


# 排序后扫描
# 时间 O(nlogn)，空间 O(1)
class Solution1:
    # 这里要特别注意~找到任意重复的一个值并赋值到duplication[0]
    # 函数返回True/False
    def duplicate(self, numbers, duplication):
        # write code here
        n = len(numbers)
        if n <= 1:
            return False
        self.quick_sort(numbers, 0, n-1)
        prev = numbers[0]
        for i in range(1, n):
            if numbers[i] == prev:
                duplication[0] = numbers[i]
                return True
            prev = numbers[i]
        return False

    def quick_sort(self, nums, left, right):
        if left < right:
            pivot_index = self.partition(nums, left, right)
            self.quick_sort(nums, left, pivot_index-1)
            self.quick_sort(nums, pivot_index+1, right)

    def partition(self, nums, left, right):
        # choose right end as the pivot
        pivot_index = right
        pivot = nums[pivot_index]
        store_index = left
        # move all elements smaller than the pivot to the left part
        for i in range(left, right):
            if nums[i] < pivot:
                nums[i], nums[store_index] = nums[store_index], nums[i]
                store_index += 1
        # swap the pivot to middle
        nums[pivot_index], nums[store_index] = nums[store_index], nums[pivot_index]
        return store_index

    
if __name__ == '__main__':
    numbers = [2,3,1,0,2,5,3]
    duplication = [-1]
    res = Solution().duplicate(numbers, duplication)
    print(res, duplication[0])
