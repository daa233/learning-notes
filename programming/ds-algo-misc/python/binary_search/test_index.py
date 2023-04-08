from index import index


def test_index():
    nums = [5, 7, 7, 8, 8, 10]

    target = 7
    assert index(nums, target) == 1

    target = 10
    assert index(nums, target) == 5

    try:
        target = 6
        i = index(nums, target)
    except Exception as e:
        assert isinstance(e, ValueError)
