import pytest

from two_sum import Solution1, Solution2, Solution


solution_list = [Solution1(), Solution2(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ([1, 2, 4, 6, 10], 8),
        [1, 3],
    ),
    (
        ([2, 3, 4], 6),
        [0, 2],
    ),
    (
        ([-1, 0], -1),
        [0, 1],
    ),
    (
        ([0] * 13010 + [2, 3] + [9] * 13010, 5),
        [13010, 13011],
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.twoSum


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    if isinstance(out, set):
        assert sln(*inp) in out
    else:
        assert sln(*inp) == out
