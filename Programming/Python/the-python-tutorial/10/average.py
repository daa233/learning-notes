def average(values):
    """Computes the arithmetic mean of a list of numbers.

    >>> print average([20, 30, 70])
    40.0
    """
    return sum(values, 1.0) / len(values)

import doctest
doctest.testmod()   # automatically validate the embedded tests
