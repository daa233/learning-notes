"""
Exponentiation by squaring
"""

from typing import List, Union


def exp_by_squaring_multiply(a: int, n: int) -> Union[int, float]:
    ret = 1
    neg_flag = n < 0
    if neg_flag:
        n = -n

    while n > 0:
        if n & 1:
            # n is odd
            ret = ret * a
        n >>= 1  # n *= 2, n is even now
        a = a * a

    if neg_flag:
        ret = 1.0 / ret

    return ret


def matmul(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
    ret = [[0] * len(b[0]) for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(a[0])):
                ret[i][j] += a[i][k] * b[k][j]
    return ret


def exp_by_squaring_matmul(a: List[List[int]], n: int) -> List[List[int]]:
    assert n > 0

    ret = [[1, 0], [0, 1]]
    while n > 0:
        if n & 1:
            # n is odd
            ret = matmul(ret, a)
        n >>= 1  # n *= 2, n is even now
        a = matmul(a, a)
    return ret


if __name__ == "__main__":
    out = exp_by_squaring_multiply(2, 3)
    assert out == 8
    out = exp_by_squaring_multiply(2, 0)
    assert out == 1
    out = exp_by_squaring_multiply(2, -3)
    assert out == 0.125

    out = exp_by_squaring_matmul([[1, 1], [1, 0]], 3)
    assert out == [[3, 2], [2, 1]]
    out = exp_by_squaring_matmul([[1, 0], [0, 1]], 100)
    assert out == [[1, 0], [0, 1]]
    out = exp_by_squaring_matmul([[1, 1], [0, 1]], 5)
    assert out == [[1, 5], [0, 1]]
