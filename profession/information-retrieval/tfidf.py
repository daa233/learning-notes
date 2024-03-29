"""
TF-IDF 代码示例

参考：
- 传统方法TF-IDF解决短文本相似度问题 - 刘聪NLP的文章 - 知乎 https://zhuanlan.zhihu.com/p/113017752
- https://scikit-learn.org/stable/modules/generated/sklearn.feature_extraction.text.TfidfTransformer.html

"""

import numpy as np
import jieba
from sklearn.metrics.pairwise import cosine_similarity
from typing import List
from collections import defaultdict
from common import get_query, get_corpus


class TfidfModel:
    def __init__(self) -> None:
        """
        - documents_list: 分词后的文档列表
        """
        # 文档总个数
        self.tf = []  # 每个文档中每个词的词频
        self.idf = {}  # 每个词汇的逆文档频率
        self.feature = None

    def clean_up(self) -> None:
        self.tf.clear()
        self.idf.clear()
        self.feature = None

    def get_feature_names_out(self) -> List[str]:
        return list(self.idf.keys())

    def fit_transform(self, documents_list: List) -> np.ndarray:
        self.clean_up()

        self.documents_list = documents_list
        self.documents_number = len(self.documents_list)

        df = defaultdict(int)

        for doc in self.documents_list:
            doc_tf = defaultdict(float)
            for word in doc:
                doc_tf[word] += 1 / len(doc)
            self.tf.append(doc_tf)

            for word in doc_tf.keys():
                df[word] += 1

        for word, count in df.items():
            self.idf[word] = np.log(self.documents_number / (count + 1))

        feature_names = self.get_feature_names_out()
        feature = np.zeros(
            (self.documents_number, len(feature_names)), dtype=np.float32
        )
        for i in range(self.documents_number):
            for j in range(len(feature_names)):
                word = feature_names[j]
                feature[i][j] = self.tf[i][word] * self.idf[word]

        self.feature = feature

        return feature

    def transform(self, query: List) -> np.ndarray:
        if not self.idf:
            raise ValueError(
                "You should call `fit_transform` with your corpus at first!"
            )

        feature_names = self.get_feature_names_out()
        score = np.zeros((len(query), len(feature_names)), dtype=np.float32)
        for i, q in enumerate(query):
            for j, word in enumerate(feature_names):
                if word in q:
                    score[i][j] += 1 / len(q) * self.idf[word]
        return score


def main():
    corpus = get_corpus()
    query = get_query()

    # 创建 TfidfModel 对象并拟合语料库
    tfidf_model = TfidfModel()
    tfidf_matrix = tfidf_model.fit_transform([list(jieba.cut(i)) for i in corpus])

    # 将query转换为TF-IDF特征向量
    query_vector = tfidf_model.transform([list(jieba.cut(i)) for i in query])

    # 计算query与语料库中每个文档的余弦相似度
    similarities = cosine_similarity(query_vector, tfidf_matrix)

    # 找到最匹配的文档索引
    most_similar_index = similarities.argmax()

    # 获取最匹配的文档内容
    most_similar_document = corpus[most_similar_index]

    print(most_similar_document)


if __name__ == "__main__":
    main()
