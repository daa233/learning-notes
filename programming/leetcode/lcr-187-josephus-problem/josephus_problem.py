# @problem: LCR 187. 破冰游戏
# @file: josephus_problem.py
# @url: https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof
# @description:
#
# 社团共有 num 为成员参与破冰游戏，编号为 0 ~ num-1。成员们按照编号顺序围绕圆桌而坐。社长抽取一个数字 target，从 0
# 号成员起开始计数，排在第 target 位的成员离开圆桌，且成员离开后从下一个成员开始计数。请返回游戏结束时最后一位成员的编号。
# 示例 1：
#
# 输入：num = 7, target = 4
# 输出：1
#
# 示例 2：
#
# 输入：num = 12, target = 5
# 输出：0
#
# 提示：
#
# 1 <= num <= 10^5
# 1 <= target <= 10^6
#
# @author: Du Ang
# @date: Jan 09, 2024


class Solution:
    """暴力模拟法（超出时间限制）"""

    def iceBreakingGame(self, num: int, target: int) -> int:
        nums = [i for i in range(num)]
        index = 0
        ti = (target - 1) % len(nums)
        while len(nums) > 1:
            if index == ti:
                nums.pop(index)
                ti = (index + target - 1) % len(nums)
            else:
                index += 1
            index %= len(nums)

        return nums[0]


if __name__ == "__main__":
    sln = Solution()
    for data in [(7, 4), (12, 5), (5, 1), (9, 13), (70866, 116922)]:
        print(f"inp: {data}, out: {sln.iceBreakingGame(*data)}")
