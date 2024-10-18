# Transpose of a Matrix (easy)
# Write a Python function that computes the transpose of a given matrix.
# Example
# Example:
#         input: a = [[1,2,3],[4,5,6]]
#         output: [[1,4],[2,5],[3,6]]
#         reasoning: The transpose of a matrix is obtained by flipping rows and columns.


def transpose_matrix(a: list[list[int | float]]) -> list[list[int | float]]:
    if not a:
        return []
    b = [[] for _ in range(len(a[0]))]
    for row in a:
        for i, e in enumerate(row):
            b[i].append(e)
    return b


if __name__ == "__main__":
    a = [[1, 2, 3], [4, 5, 6]]
    print(transpose_matrix(a))
