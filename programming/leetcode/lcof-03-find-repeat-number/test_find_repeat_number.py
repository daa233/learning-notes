import pytest

from find_repeat_number import Solution1, Solution2, Solution


solution_list = [Solution1(), Solution2(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    ([2, 3, 1, 0, 2, 5, 3], set([2, 3])),
    ([1, 3, 4, 0, 2, 5, 5, 5], 5),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.findRepeatNumber


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    if isinstance(out, set):
        assert sln(inp) in out
    else:
        assert sln(inp) == out
