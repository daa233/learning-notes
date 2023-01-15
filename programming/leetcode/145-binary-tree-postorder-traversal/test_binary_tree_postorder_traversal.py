import sys
import pytest

from binary_tree_postorder_traversal import Solution, Solution2, Solution3

sys.path.insert(0, "../297-serialize-and-deserialize-binary-tree")
from serialize_and_deserialize_binary_tree import CodecLikeLeetCode as Codec


solution_list = [Solution(), Solution2(), Solution3()]


# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        "[1,null,2,3]",
        [3, 2, 1],
    ),
    (
        "[]",
        [],
    ),
    (
        "[1]",
        [1],
    ),
    (
        "[1,2]",
        [2, 1],
    ),
    (
        "[1,null,2]",
        [2, 1],
    ),
    ("[1,4,3,2]", [2, 4, 3, 1]),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.postorderTraversal


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    deser = Codec(none_str="[]")
    root = deser.deserialize(inp)
    actual = sln(root)
    assert all([a == b for a, b in zip(actual, out)])
