from find_ge import find_ge


def test_find_ge():
    nums = [5, 7, 7, 8, 8, 10]

    target = 7
    assert find_ge(nums, target) == 1

    target = 9
    assert find_ge(nums, target) == 5

    target = 10
    assert find_ge(nums, target) == 5

    target = 11
    try:
        i = find_ge(nums, target)
    except Exception as e:
        assert isinstance(e, ValueError)


def test_find_ge_only_one_item():
    nums = [5]

    target = 5
    assert find_ge(nums, target) == 0
