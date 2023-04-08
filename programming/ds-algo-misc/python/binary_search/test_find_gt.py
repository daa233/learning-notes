from find_gt import find_gt


def test_find_gt():
    nums = [5, 7, 7, 8, 8, 10]

    target = 7
    assert find_gt(nums, target) == 3

    target = 9
    assert find_gt(nums, target) == 5

    target = 10
    try:
        i = find_gt(nums, target)
    except Exception as e:
        assert isinstance(e, ValueError)

    target = 6
    assert find_gt(nums, target) == 1


def test_find_gt_only_one_item():
    nums = [5]

    target = 1
    assert find_gt(nums, target) == 0
