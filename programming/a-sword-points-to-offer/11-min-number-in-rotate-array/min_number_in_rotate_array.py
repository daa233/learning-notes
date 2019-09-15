# -*- coding:utf-8 -*-
# 题目描述
# 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
# 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
# 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
# NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

# 先考虑没有重复元素的情况：
# （1）l-->--m---->r，最小值m左侧（包含m），right = m
# （2）l----m-->-->r，最小值在m右侧（不包含m），left = m + 1
# 如果包含重复元素，当 mid 和 right 大小相等时无法区间，则顺序查找或缩小区间范围
class Solution:
    def minNumberInRotateArray(self, rotateArray):
        # write code here
        left = 0
        right = len(rotateArray) - 1

        # 没有旋转
        if rotateArray[left] < rotateArray[right]:
            return rotateArray[left]

        while left < right:
            mid = (left + right) // 2
            if rotateArray[mid] < rotateArray[right]:
                # l-->--m---->r
                right = mid
            elif rotateArray[mid] > rotateArray[right]:
                # l----m-->-->r
                left = mid + 1  # +1 是因为 mid 肯定不是最小值
            else:
                # mid 和 right 相等，无法判断哪个区间，缩小区间范围
                right = right - 1
        return rotateArray[left]


if __name__ == "__main__":
    array = [3, 4, 5, 1, 2]
    print(Solution().minNumberInRotateArray(array))
    array = [1, 1, 1, 0, 1]
    print(Solution().minNumberInRotateArray(array))
    array = [1, 2, 3, 4, 5]
    print(Solution().minNumberInRotateArray(array))
