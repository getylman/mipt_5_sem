import numpy as np


def get_dominant_eigenvalue_and_eigenvector(data, num_steps):
    """
    data: np.ndarray – symmetric diagonalizable real-valued matrix
    num_steps: int – number of power method steps

    Returns:
    eigenvalue: float – dominant eigenvalue estimation after `num_steps` steps
    eigenvector: np.ndarray – corresponding eigenvector estimation
    """
    # YOUR CODE HERE

    v0 = np.random.rand(data.shape[0])
    v0 = v0 / np.linalg.norm(v0)

    for _ in range(num_steps):
        v = data.dot(v0)
        v = v / np.linalg.norm(v)
        v0 = v

    eigenvalue = v.dot(data.dot(v))
    eigenvector = v
    return eigenvalue, eigenvector
