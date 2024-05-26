import torch.nn as nn
import copy


def clones(module, N):
    """Produce N identical layers."""
    return nn.ModuleList([copy.deepcopy(module) for _ in range(N)])


class TrainState:
    """Track number of steps, examples and tokens processed"""

    step: int = 0  # Steps in the current epoch
    accum_step: int = 0  # Number of gradient accumulation steps
    samples: int = 0  # Total number of examples used
    tokens: int = 0  # Total number of tokens processed
