# Matrix times Vector (easy)
# Write a Python function that takes the dot product of a matrix and a vector. return -1 if the matrix could not be dotted with the vector
# Example
# Example:
#         input: a = [[1,2],[2,4]], b = [1,2]
#         output:[5, 10]
#         reasoning: 1*1 + 2*2 = 5;
#                    1*2+ 2*4 = 10


def matrix_dot_vector(
    a: list[list[int | float]], b: list[int | float]
) -> list[int | float]:
    if not a or not b:
        return -1
    if len(a[0]) != len(b):
        return -1
    c = [0] * len(b)
    for i, row in enumerate(a):
        for j, k in zip(row, b):
            c[i] += j * k
    return c


if __name__ == "__main__":
    a = [[1, 2], [2, 4]]
    b = [1, 2]
    print(matrix_dot_vector(a, b))
