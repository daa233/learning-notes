import numpy as np


def l2_norm(X: np.ndarray) -> np.ndarray:
    return X / np.sqrt((X * X).sum(axis=1))[:, None]

