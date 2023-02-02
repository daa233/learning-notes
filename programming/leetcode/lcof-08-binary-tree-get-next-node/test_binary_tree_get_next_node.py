import sys
import pytest
from typing import List

from binary_tree_get_next_node import Solution, TreeNode

sys.path.insert(0, "../297-serialize-and-deserialize-binary-tree")
from serialize_and_deserialize_binary_tree import CodecLikeLeetCode


class Codec(CodecLikeLeetCode):
    """
    支持 next 支持的反序列化
    """

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data:
            return None

        data = data[1:-1]  # stripe the '[' and ']'
        if len(data) == 0:
            val_list = []
        else:
            val_list = data.split(",")

        if not val_list or (len(val_list) == 1 and val_list[0] == "null"):
            return None

        node_list = []
        for val in val_list:
            if val == "null":
                node_list.append(None)
            else:
                node_list.append(TreeNode(int(val)))

        root = node_list.pop(0)
        q = [root]
        while q:
            node = q.pop(0)
            if node_list:
                node.left = node_list.pop(0)
                if node.left:
                    node.left.next = node
            if node_list:
                node.right = node_list.pop(0)
                if node.right:
                    node.right.next = node
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)

        return root


solution_list = [Solution()]


# testcases: List[Tuple[inp, out]]
# use `set` to indicate the expected output may be multiple
data = [
    (
        ("[8,6,10,5,7,9,11]", 8),
        9,
    ),
    (
        ("[8,6,10,5,7,9,11]", 6),
        7,
    ),
    (
        ("[1,2,null,null,3,null,4]", 4),
        1,
    ),
    (
        ("[5]", 5),
        "null",
    ),
    (
        ("[5,4,null,3,null,2]", 4),
        5,
    ),
]


@pytest.fixture(params=solution_list)
def sln(request):
    """Solution fixture"""
    return request.param.GetNext


def search_node(root: TreeNode, val: int) -> TreeNode:
    if root is None:
        return

    if root.val == val:
        return root
    node = search_node(root.left, val)
    if node and node.val == val:
        return node
    node = search_node(root.right, val)
    if node and node.val == val:
        return node


@pytest.mark.parametrize("inp, out", data)
def test(sln, inp, out):
    """
    Test the solution with input and output.
    """
    deser = Codec(none_str="[]")
    tree_str, node_val = inp
    root = deser.deserialize(tree_str)
    node = search_node(root, node_val)
    actual = sln(node)

    if actual is None:
        assert "null" == out
    else:
        assert actual.val == out
