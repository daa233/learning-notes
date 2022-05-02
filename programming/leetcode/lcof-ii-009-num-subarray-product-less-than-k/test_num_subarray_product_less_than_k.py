import pytest

from num_subarray_product_less_than_k import Solution1, Solution2, Solution


solution_list = [Solution1(), Solution2(), Solution()]


data = [
    (
        ([10, 5, 2, 6], 100),
        8,
    ),
    (
        ([1, 2, 3], 0),
        0,
    ),
    (
        ([1, 1, 1], 2),
        6,
    ),
    (
        ([2, 1, 3, 2], 10),
        9,
    ),
    (
        ([], 1),
        0,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.numSubarrayProductLessThanK


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    assert sln(*inp) == out
