import pytest

import sys

sys.path.insert(0, "../297-serialize-and-deserialize-binary-tree")

from is_sub_structure import Solution
from serialize_and_deserialize_binary_tree import CodecLikeLeetCode


solution_list = [Solution()]

deser = CodecLikeLeetCode().deserialize


# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (("[1,2,3,4]", "[3]"), True),
    (("[1,2,3]", "[3,1]"), False),
    (("[3,4,5,1,2]", "[4,1]"), True),
    (("[4,2,3,4,5,6,7,8,9]", "[4,8,9]"), True),
    (("[1,2,3]", "[]"), False),
    (("[]", "[]"), False),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.isSubStructure


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    assert sln(*[deser(i) for i in inp]) == out
