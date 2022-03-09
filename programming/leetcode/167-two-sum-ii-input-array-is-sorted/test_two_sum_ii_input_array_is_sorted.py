import pytest

from two_sum_ii_input_array_is_sorted import Solution, Solution2


solution_list = [Solution(), Solution2()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ([2, 7, 11, 15], 9),
        [1, 2],
    ),
    (
        ([2, 3, 4], 6),
        [1, 3],
    ),
    (
        ([-1, 0], -1),
        [1, 2],
    ),
    (
        ([0] * 13010 + [2, 3] + [9] * 13010, 5),
        [13011, 13012],
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
