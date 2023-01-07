import sys

import pytest

from build_tree import Solution, Solution2, Solution3

sys.path.insert(0, "../297-serialize-and-deserialize-binary-tree")
from serialize_and_deserialize_binary_tree import CodecLikeLeetCode as Codec


solution_list = [Solution(), Solution2(), Solution3()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        [[3, 9, 20, 15, 7], [9, 3, 15, 20, 7]],
        "[3,9,20,null,null,15,7]",
    ),
    (
        [[], []],
        "[]",
    ),
    (
        [[1, 2, 3, 4, 5], [5, 4, 3, 2, 1]],
        "[1,2,null,3,null,4,null,5]",
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.buildTree


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    ser = Codec(none_str="[]")
    assert ser.serialize(sln(*inp)) == out
