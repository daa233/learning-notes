import pytest

from three_sum import Solution2, Solution3, Solution4, Solution5, Solution6, Solution


solution_list = [Solution2(), Solution3(), Solution4(), Solution5(), Solution6(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ([-1, 0, 1, 2, -1, -4],),
        [[-1, -1, 2], [-1, 0, 1]],
    ),
    (
        ([],),
        [],
    ),
    (
        ([0],),
        [],
    ),
    (
        ([1, -1],),
        [],
    ),
    (
        ([0] * 3000,),
        [[0, 0, 0]],
    ),
    (
        ([-2, 1, 1],),
        [[-2, 1, 1]],
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.threeSum


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    res = sln(*inp)

    res_set = set([tuple(sorted(item)) for item in res])
    out_set = set([tuple(sorted(item)) for item in out])

    assert res_set == out_set
