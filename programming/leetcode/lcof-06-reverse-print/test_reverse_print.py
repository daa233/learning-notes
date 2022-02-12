import pytest

from reverse_print import Solution1, Solution, Solution2
from reverse_print import create_linked_list


solution_list = [Solution1(), Solution(), Solution2()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        [],
        [],
    ),
    (
        [1],
        [1],
    ),
    (
        [1, 3, 2],
        [2, 3, 1],
    ),
    (
        [3, 5, 6, 7, 9],
        [9, 7, 6, 5, 3],
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.reversePrint


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    linked_list = create_linked_list(inp)

    if isinstance(out, set):
        assert sln(linked_list) in out
    else:
        assert sln(linked_list) == out
