# Scalar Multiplication of a Matrix (easy)
# Write a Python function that multiplies a matrix by a scalar and returns the result.
# Example
# Example:
#         input: matrix = [[1, 2], [3, 4]], scalar = 2
#         output: [[2, 4], [6, 8]]
#         reasoning: Each element of the matrix is multiplied by the scalar.


def scalar_multiply(
    matrix: list[list[int | float]], scalar: int | float
) -> list[list[int | float]]:
    result = []
    for row in matrix:
        row_result = []
        for e in row:
            row_result.append(e * scalar)
        result.append(row_result)
    return result


if __name__ == "__main__":
    matrix = [[1, 2], [3, 4]]
    scalar = 2
    print(scalar_multiply(matrix, scalar))
