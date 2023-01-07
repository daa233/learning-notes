import pytest
from typing import List

from build_tree import TreeNode, Solution, Solution2, Solution3


solution_list = [Solution(), Solution2(), Solution3()]


class Codec:
    """The binary tree codec by BFS."""

    def serialize(self, root: TreeNode) -> str:
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        val_list = []
        q = [root]
        while q:
            node = q.pop(0)
            if node:
                val_list.append(node.val)
                q.append(node.left)
                q.append(node.right)
            else:
                val_list.append("null")

        while val_list:
            if val_list[-1] == "null":
                val_list.pop(-1)
            else:
                break

        result = "[{}]".format(",".join([str(i) for i in val_list]))
        return result

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data:
            return None

        data = data[1:-1]  # stripe the '[' and ']'
        val_list = data.split(",")

        if not val_list or (len(val_list) == 1 and val_list[0] == "null"):
            return None

        node_list = []
        for val in val_list:
            if val == "null":
                node_list.append(None)
            else:
                node_list.append(TreeNode(val))

        root = node_list.pop(0)
        q = [root]
        while q:
            node = q.pop(0)
            node.left = node_list.pop(0)
            node.right = node_list.pop(0)
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)

        return root


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
    ser = Codec()
    assert ser.serialize(sln(*inp)) == out
