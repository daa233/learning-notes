import pytest

from max_product import Solution1, Solution2, Solution3, Solution


solution_list = [Solution1(), Solution2(), Solution3(), Solution()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        (["abcw", "baz", "foo", "bar", "fxyz", "abcdef"],),
        16,
    ),
    (
        (["a", "ab", "abc", "d", "cd", "bcd", "abcd"],),
        4,
    ),
    (
        (["a", "aa", "aaa", "aaaa"],),
        0,
    ),
    (
        (["eae", "ea", "aaf", "bda", "fcf", "dc", "ac", "ce", "cefde", "dabae"],),
        15,
    ),
    (
        (["a"],),
        0,
    ),
    (
        ([],),
        0,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.maxProduct


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """

    if isinstance(out, set):
        assert sln(*inp) in out
    else:
        assert sln(*inp) == out
