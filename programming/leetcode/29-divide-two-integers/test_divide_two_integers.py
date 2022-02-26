import pytest

from divide_two_integers import Solution


solution_list = [Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        (15, 2),
        7,
    ),
    (
        (7, -3),
        -2,
    ),
    (
        (0, 1),
        0,
    ),
    (
        (1, 1),
        1,
    ),
    (
        (-1, -1),
        1,
    ),
    (
        (-2147483648, -1),
        2147483647,
    ),
    (
        (-2147483648, 1),
        -2147483648,
    ),
    (
        (-2147483648, 2),
        -1073741824,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.divide


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    if isinstance(out, set):
        assert sln(*inp) in out
    else:
        assert sln(*inp) == out
