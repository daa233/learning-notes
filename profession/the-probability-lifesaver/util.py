def factorial(n: int) -> int:
    p = 1
    while n > 0:
        p *= n
        n -= 1
    return p


def c_n_m(n: int, m: int) -> int:
    return int(factorial(n) / factorial(n - m) / factorial(m))


def test_factorial() -> None:
    assert factorial(5) == 120


def test_c_n_m() -> None:
    assert c_n_m(5, 0) == 1
    assert c_n_m(5, 1) == 5
    assert c_n_m(5, 2) == 10
    assert c_n_m(5, 5) == 1

