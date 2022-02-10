import pytest

from find_number_in_2d_array import Solution1, Solution2, Solution


solution_list = [Solution1(), Solution2(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        [],
        5,
        False,
    ),
    (
        [
            [1, 4, 7, 11, 15],
            [2, 5, 8, 12, 19],
            [3, 6, 9, 16, 22],
            [10, 13, 14, 17, 24],
            [18, 21, 23, 26, 30],
        ],
        5,
        True,
    ),
    (
        [
            [1, 4, 7, 11, 15],
            [2, 5, 8, 12, 19],
            [3, 6, 9, 16, 22],
            [10, 13, 14, 17, 24],
            [18, 21, 23, 26, 30],
        ],
        20,
        False,
    ),
    (
        [[-5]],
        -5,
        True,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.findNumberIn2DArray


@pytest.mark.parametrize("matrix, target, out", data)
def test(sln, matrix, target, out):
    """
    Test the solution with input and output.
    """
    if isinstance(out, set):
        assert sln(matrix, target) in out
    else:
        assert sln(matrix, target) == out
