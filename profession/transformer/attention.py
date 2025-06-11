import torch
import torch.nn as nn
import math
from util import clones


def attention(query, key, value, mask=None, dropout=None):
    """Compute 'Scaled Dot Product Attention'"""
    d_k = query.size(-1)
    scores = torch.matmul(query, key.transpose(-2, -1)) / math.sqrt(d_k)
    if mask is not None:
        scores = scores.masked_fill(mask == 0, -1e9)
    p_attn = scores.softmax(dim=-1)
    if dropout is not None:
        p_attn = dropout(p_attn)
    return torch.matmul(p_attn, value), p_attn


class MultiHeadAttention(nn.Module):
    def __init__(self, h, d_model, dropout=0.1):
        """Take in model size and number of heads."""
        super().__init__()
        assert d_model % h == 0
        # We assume d_v always equals d_k
        self.d_k = d_model // h
        self.h = h
        self.linears = clones(nn.Linear(d_model, d_model), 4)
        self.attn = None
        self.dropout = nn.Dropout(p=dropout)

    def forward(self, query, key, value, mask=None):
        """Implements Figure 2"""
        if mask is not None:
            # Same mask applied to all h heads.
            mask = mask.unsqueeze(1)
        nbatches = query.size(0)

        # 1) Do all the linear projections in batch from d_model => h x d_k
        query, key, value = [
            lin(x).view(nbatches, -1, self.h, self.d_k).transpose(1, 2)
            for lin, x in zip(self.linears, (query, key, value))
        ]

        # 2) Apply attention on all the projected vectors in batch.
        x, self.attn = attention(query, key, value, mask=mask, dropout=self.dropout)

        # 3) "Concat" using a view and apply a final linear.
        x = (
            x.transpose(1, 2)
            .contiguous()
            .view(nbatches, -1, self.h * self.d_k)
        )
        del query
        del key
        del value
        return self.linears[-1](x)
    
### MQA实现
#和MHA的不同点在于, MQA只对query做multi-head, K,V为单头
# 减少了K,V的参数量
class MultiQueryAttention(nn.Module):
    def __init__(self, h, d_model):
        super().__init__()
        self.h = h
        self.d_k = d_model // h
        assert d_model % h == 0
        self.q_linear = nn.Linear(d_model, d_model)

        ### k, v输出为单头
        self.k_linear = nn.Linear(d_model, self.d_k)
        self.v_linear = nn.Linear(d_model, self.d_k)

        self.o_linear = nn.Linear(d_model, d_model)
        
    def forward(self, q, k, v, mask, dropout):
        q = self.q_linear(q)
        k = self.k_linear(k)
        v = self.v_linear(v)
        batch_size = q.size()[0]

        q = q.view(batch_size, -1, self.h, self.d_k).transpose(1, 2)
        k = k.view(batch_size, -1, 1, self.d_k).transpose(1,2)
        v = v.view(batch_size, -1, 1, self.d_k).transpose(1,2)
        ## q --> batch_size, self.h, q_len, self.d_k
        ## k,v --> batch_size, 1, q_len, self.d_k

        ## q*k转置 -> batch_size, self.h, q_len, q_len(k被广播为, batch_size, self.h, q_len, self.d_k)
        ##  --> *v --> batch_size, self.h, q_len, self.d_k
        output = attention(q, k, v)
        output = output.transpose(1, 2).view(batch_size, -1, self.h*self.d_k)
        output = self.o_linear(output)
        return output