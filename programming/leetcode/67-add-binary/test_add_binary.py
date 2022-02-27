import pytest

from add_binary import Solution1, Solution, Solution2


solution_list = [Solution1(), Solution(), Solution2()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ("11", "10"),
        "101",
    ),
    (
        ("1010", "1011"),
        "10101",
    ),
    (
        ("0", "0"),
        "0",
    ),
    (
        ("0", "1"),
        "1",
    ),
    (
        ("1", "111"),
        "1000",
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.addBinary


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    if isinstance(out, set):
        assert sln(*inp) in out
    else:
        assert sln(*inp) == out
