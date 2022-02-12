import pytest

from replace_space import Solution1, Solution


solution_list = [Solution1(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        "We are happy.",
        "We%20are%20happy.",
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.replaceSpace


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    if isinstance(out, set):
        assert sln(inp) in out
    else:
        assert sln(inp) == out
