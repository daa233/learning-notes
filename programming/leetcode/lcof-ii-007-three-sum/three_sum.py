# @problem: 剑指 Offer II 007. 数组中和为 0 的三个数
# @file: three_sum.py
# @url: https://leetcode-cn.com/problems/1fGaJU
# @description:
#
# 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a ，b ，c ，使得 a + b + c = 0
# ？请找出所有和为 0 且 不重复 的三元组。
# 示例 1：
#
# 输入：nums = [-1,0,1,2,-1,-4]
# 输出：[[-1,-1,2],[-1,0,1]]
#
# 示例 2：
#
# 输入：nums = []
# 输出：[]
#
# 示例 3：
#
# 输入：nums = [0]
# 输出：[]
#
# 提示：
#
# 0 <= nums.length <= 3000
# -10^5 <= nums[i] <= 10^5
#
# 注意：本题与主站 15 题相同：https://leetcode-cn.com/problems/3sum/
#
# @author: Du Ang
# @date: Mar 09, 2022
from typing import List
from collections import defaultdict


class Solution1:
    """
    未通过。
    暴力破解。遍历所有三元组，依次判断所有加和是否为0。注意去除重复的三元组。
    时间复杂度：O(n^3*n) = O(n^4)，三重循环遍历+去重。
    空间复杂度：O(1)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        if len(nums) < 3:
            return []
        elif len(nums) == 3:
            if sum(nums) == 0:
                return [nums]
            else:
                return []
        else:
            result = []
            for i in range(len(nums) - 2):
                for j in range(i + 1, len(nums) - 1):
                    for k in range(j + 1, len(nums)):
                        if nums[i] + nums[j] + nums[k] == 0:
                            triple = sorted([nums[i], nums[j], nums[k]])
                            if triple not in result:
                                result.append(triple)
            return result


class Solution2:
    """
    未通过。
    遍历数组，每次选取一个数字作为 target，然后从剩余的数字中寻找和为 -target 的两个数字，
    即题目退化为 two sum（双指针法）。但是需要注意，数组中有可能包含重复的数字。
    时间复杂度：O(nlogn + n^2 * (3+n)) = O(n^3)，排序+双指针+去重
    空间复杂度：O(n)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        nums = sorted(nums)
        for pt, target in enumerate(nums):
            pi = 0
            pj = len(nums) - 1
            while pi < pj:
                if pi == pt:
                    pi += 1
                    continue
                elif pj == pt:
                    pj -= 1
                    continue
                s = nums[pi] + nums[pj]
                if s > -target:
                    pj -= 1
                elif s < -target:
                    pi += 1
                else:
                    triple = sorted([target, nums[pi], nums[pj]])
                    if triple not in result:
                        result.append(triple)
                    pi += 1
                    pj -= 1

        return result


class Solution3:
    """
    未通过。
    遍历数组，每次选取一个数字作为 target，然后从剩余的数字中寻找和为 -target 的两个数字，
    即题目退化为 two sum（哈希表法）。但是需要注意，数组中有可能包含重复的数字。
    时间复杂度：O(n^2 * (3 + n)) = O(n^3)，哈希表法+去重
    空间复杂度：O(n^2)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        for pt, target in enumerate(nums):
            d = dict()
            for i, num in enumerate(nums):
                if i == pt:
                    continue
                if num in d:
                    triple = sorted([target, num, nums[d[num]]])
                    if triple not in result:
                        result.append(triple)
                else:
                    diff = -target - num
                    d[diff] = i
        return result


class Solution4:
    """
    在方法3的基础上，对去重的逻辑优化，可以通过。可以将结果先存到 set 中，将每个三元组
    转为 tuple 类型再添加到 set。
    时间复杂度：O(n^2 * (3 + n)) = O(n^3)
    空间复杂度：O(n^2)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = set()
        for pt, target in enumerate(nums):
            d = dict()
            for i, num in enumerate(nums):
                if i == pt:
                    continue
                if num in d:
                    triple = tuple(sorted([target, num, nums[d[num]]]))
                    if triple not in result:
                        result.add(triple)
                else:
                    diff = -target - num
                    d[diff] = i
        return [list(item) for item in result]


class Solution5:
    """
    基于方法2中的双指针法，先对数组进行排序，然后利用 two sum 的方法，注意利用排序
    后的结果进行去重。
    时间复杂度：O(nlog(n) + n^2) = O(n^2) 排序 + 双重循环遍历
    空间复杂度：O(n)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        nums = sorted(nums)
        for pt, target in enumerate(nums):
            if pt > 0 and target == nums[pt - 1]:
                continue
            ans = self.twoSum(nums, pt + 1, len(nums) - 1, -target)
            if ans:
                result.extend(ans)
        return result

    def twoSum(self, nums: List[int], start: int, end: int, target: int) -> List[int]:
        ans = []
        while start < end:
            s = nums[start] + nums[end]
            if s == target:
                ans.append([-target, nums[start], nums[end]])
                # 去重
                while start < end and nums[start] == nums[start + 1]:
                    start += 1
                start += 1
                while start < end and nums[end] == nums[end - 1]:
                    end -= 1
                end -= 1
            elif s < target:
                start += 1
            else:
                end -= 1
        return ans


class Solution6:
    """
    基于 Solution5 优化。可以利用更多的先验来节省计算，三元组中，第一个数一定是大于
    等于0的，第三个数一定是小于等于0的。
    时间复杂度：O(nlog(n) + n^2) = O(n^2) 排序 + 双重循环遍历
    空间复杂度：O(n)
    """

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        nums = sorted(nums)
        for pt, target in enumerate(nums):
            if pt > 0 and target == nums[pt - 1] or target > 0:
                # 排除第一个数重复和第一个数大于0的情况
                continue
            ans = self.twoSum(nums, pt + 1, len(nums) - 1, -target)
            if ans:
                result.extend(ans)
        return result

    def twoSum(self, nums: List[int], start: int, end: int, target: int) -> List[int]:
        ans = []
        while start < end:
            if nums[end] < 0:
                # 排除第三个数小于0的情况
                break

            s = nums[start] + nums[end]

            if s == target:
                ans.append([-target, nums[start], nums[end]])
                # 去重
                while start < end and nums[start] == nums[start + 1]:
                    start += 1
                start += 1
                while start < end and nums[end] == nums[end - 1]:
                    end -= 1
                end -= 1
            elif s < target:
                start += 1
            else:
                end -= 1
        return ans


class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        """
        结合三元组特点，对 nums 数字进行分组，分为 zeros、positives、negatives 三组，
        并统计每组中各个数字出现的次数。
        则三元组的组合可能是以下情况：
            1. 三个全部来自 zeros
            2. 一个数字来自 zeros，一个数字来自 positives，一个数字来自 negatives
            3. 一个数字来自 positives，两个数字来自 negatives。注意两个数字的部分去重。
            4. 两个数字来自 positives，一个数字来自 negatives。注意两个数字的部分去重。
        时间复杂度：O(n) 遍历统计个数 + O(1) 情况1 + O(n) 情况2 + O(n^2) 情况3、4 = O(n^2)
        空间复杂度：O(n)
        """
        result = []
        # 将nums分成三组：zeros，positives，negatives
        zeros_count, positives, negatives = 0, defaultdict(int), defaultdict(int)
        for num in nums:
            if num == 0:
                zeros_count += 1
            elif num > 0:
                positives[num] += 1
            else:
                negatives[num] += 1

        if zeros_count >= 3:
            # [0, 0, 0]
            result.append([0, 0, 0])
        for pi, pi_count in positives.items():
            if -pi in negatives and zeros_count >= 1:
                # [pos, 0, neg]
                result.append([pi, 0, -pi])

            for pj, pj_count in positives.items():
                neg = -(pi + pj)
                if neg not in negatives:
                    continue
                else:
                    if (pi == pj and pi_count >= 2) or (pi < pj):
                        # [pi, pj, neg]
                        result.append([pi, pj, neg])

            for ni, ni_count in negatives.items():
                nj = -pi - ni
                if nj not in negatives:
                    continue
                else:
                    if (ni == nj and ni_count >= 2) or (ni < nj):
                        # [pos, ni, nj]
                        result.append([pi, ni, nj])

        return result
