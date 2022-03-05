import pytest

from count_bits import Solution1, Solution2, Solution3, Solution4, Solution


solution_list = [Solution1(), Solution2(), Solution3(), Solution4(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        (2,),
        [0, 1, 1],
    ),
    (
        (5,),
        [0, 1, 1, 2, 1, 2],
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.countBits


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    if isinstance(out, set):
        assert sln(*inp) in out
    else:
        assert sln(*inp) == out
