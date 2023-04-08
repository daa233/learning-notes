from typing import List


def binary_search(a: List, target, left: int = 0, right: int = None) -> int:
    """
    The return value i is such that all e in a[:i] have e < x, and all e in
    a[i:] have e >= x.
    """

    def condition(value, target) -> bool:
        return value >= target

    if left < 0:
        raise ValueError("left must be non-negative instead of {}".format(left))
    if right is None:
        right = len(a)

    while left < right:
        mid = left + (right - left) // 2
        if condition(a[mid], target):
            right = mid
        else:
            left = mid + 1
    return left


def index(nums, target):
    """Locate the leftmost value exactly equal to x"""
    i = binary_search(nums, target)
    if i != len(nums) and nums[i] == target:
        return i
    else:
        raise ValueError
