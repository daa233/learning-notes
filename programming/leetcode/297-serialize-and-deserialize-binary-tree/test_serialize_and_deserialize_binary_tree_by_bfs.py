import pytest

from serialize_and_deserialize_binary_tree import Codec

solution_list = [Codec()]

# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    ("[1,2,3,null,null,4,5,null,null,null,null]",),
    ("[null]",),
    ("[1,null,null]",),
]


@pytest.fixture(params=solution_list)
def ser(request):
    """Solution fixture"""
    return request.param.serialize


@pytest.fixture(params=solution_list)
def deser(request):
    """Solution fixture"""
    return request.param.deserialize


@pytest.mark.parametrize("inp", data)
def test(ser, deser, inp):
    """
    Test the solution with input and output.
    """
    assert (ser(deser(*inp)),) == inp
