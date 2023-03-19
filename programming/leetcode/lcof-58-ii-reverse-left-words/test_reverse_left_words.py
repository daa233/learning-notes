import pytest

from reverse_left_words import Solution, Solution2, Solution3, Solution4


solution_list = [Solution(), Solution2(), Solution3(), Solution4()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ("abcdefg", 2),
        "cdefgab",
    ),
    (
        ("lrloseumgh", 6),
        "umghlrlose",
    ),
    (
        ("", 0),
        "",
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.reverseLeftWords


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    assert sln(*inp) == out
