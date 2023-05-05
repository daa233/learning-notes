# @problem: 剑指 Offer 63. 股票的最大利润
# @file: max_profit.py
# @url: https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof
# @description:
#
# 假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？
# 示例 1:
# 输入: [7,1,5,3,6,4]
# 输出: 5
# 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
#      注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
#
# 示例 2:
# 输入: [7,6,4,3,1]
# 输出: 0
# 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
# 限制：
# 0 <= 数组长度 <= 10^5
# 注意：本题与主站 121 题相同：https://leetcode-cn.com/problems/best-time-to-buy-
# and-sell-stock/
#
# @author: Du Ang
# @date: May 01, 2023

import sys
from typing import List


class Solution1:
    def getLaterHighestPrices(self, prices: List[int]) -> List[int]:
        later_highest_prices = []
        max_price = prices[-1]
        for price in prices[::-1]:
            if price > max_price:
                max_price = price
            later_highest_prices.append(max_price)
        return later_highest_prices[::-1]

    def maxProfit(self, prices: List[int]) -> int:
        if not prices:
            return 0

        max_profit = 0
        later_highest_prices = self.getLaterHighestPrices(prices)
        print(later_highest_prices)
        for i, price in enumerate(prices):
            profit = later_highest_prices[i] - price
            if profit > max_profit:
                max_profit = profit

        return max_profit


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if not prices:
            return 0

        min_price = prices[0]
        max_profit = 0
        for price in prices:
            if price < min_price:
                min_price = price
            profit = price - min_price
            if profit > max_profit:
                max_profit = profit

        return max_profit
