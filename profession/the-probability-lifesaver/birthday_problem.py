from util import c_n_m


def no_one_same_prob(n: int, days: int = 365) -> float:
    p = 1
    for i in range(n):
        p *= c_n_m(days - i, 1) / days
    return p


def birthday_problem() -> int:
    p = 1
    n = 0
    while p > 0.5:
        n += 1
        p = no_one_same_prob(n)

    return n


if __name__ == "__main__":
    n = birthday_problem()
    print("n =", n)
