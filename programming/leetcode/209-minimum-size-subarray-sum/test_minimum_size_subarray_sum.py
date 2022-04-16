import pytest

from minimum_size_subarray_sum import Solution2, Solution


solution_list = [Solution(), Solution2()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        (7, [2, 3, 1, 2, 4, 3]),
        2,
    ),
    (
        (1, []),
        0,
    ),
    (
        (4, [1, 4, 4]),
        1,
    ),
    (
        (11, [1, 1, 1, 1, 1, 1, 1, 1]),
        0,
    ),
    (
        (11, [1, 2, 3, 4, 5]),
        3,
    ),
    (
        (1, [0]),
        0,
    ),
    (
        (3, [1, 1, 1]),
        3,
    ),
    (
        (7, [1, 1, 1, 1, 7]),
        1,
    ),
    (
        (6, [10, 2, 3]),
        1,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.minSubArrayLen


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    assert sln(*inp) == out
