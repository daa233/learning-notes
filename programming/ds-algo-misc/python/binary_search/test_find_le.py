from find_le import find_le


def test_find_le():
    nums = [5, 7, 7, 8, 8, 10]

    target = 7
    assert find_le(nums, target) == 2

    target = 9
    assert find_le(nums, target) == 4

    target = 10
    assert find_le(nums, target) == 5

    try:
        target = 6
        i = find_le(nums, target)
    except Exception as e:
        assert isinstance(e, ValueError)


def test_find_le_only_one_item():
    nums = [5]

    target = 7
    assert find_le(nums, target) == 0
