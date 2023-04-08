from find_lt import find_lt


def test_find_lt():
    nums = [5, 7, 7, 8, 8, 10]

    target = 7
    assert find_lt(nums, target) == 0

    target = 9
    assert find_lt(nums, target) == 4

    target = 10
    assert find_lt(nums, target) == 4

    try:
        target = 6
        i = find_lt(nums, target)
    except Exception as e:
        assert isinstance(e, ValueError)


def test_find_lt_only_one_item():
    nums = [5]

    target = 7
    assert find_lt(nums, target) == 0
