# Info-Retrieval

## 安装
```bash
$ pip install -r requirements.txt
```

## TF-IDF
- 代码实现：[tfidf](tfidf.py)

运行命令：
```bash
$ python tfidf.py
>>> Please input your query: 选民选举资格的法律规定
Building prefix dict from the default dictionary ...
Loading model from cache /tmp/jieba.cache
Loading model cost 0.764 seconds.
Prefix dict has been built successfully.
>>> For the query: 选民选举资格的法律规定
Ranked documents:
  Rank 1 (score: 0.28): 公民对于选举委员会对选民的资格申诉的处理决定不服，能不能去法院起诉吗？
  Rank 2 (score: 0.18): 法律上餐具、饮具集中消毒服务单位的责任是不是对消毒餐具、饮具进行检验？
  Rank 3 (score: 0.00): 有人走私两万元，怎么处置他？
  Rank 4 (score: 0.00): 我在微信上被骗了，请问被骗多少钱才可以立案？
  Rank 5 (score: 0.00): 借钱给朋友到期不还得什么时候可以起诉？怎么起诉？
  Rank 6 (score: 0.00): 行政机关强行解除行政协议造成损失，如何索取赔偿？
>>> The most similar document (score: 0.28): 公民对于选举委员会对选民的资格申诉的处理决定不服，能不能去法院起诉吗？
```

