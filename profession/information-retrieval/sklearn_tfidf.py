from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import jieba
from common import get_corpus, get_query


def main():
    corpus = get_corpus()
    query = get_query()

    # 创建TfidfVectorizer对象并拟合语料库
    tfidf_vectorizer = TfidfVectorizer()
    tfidf_matrix = tfidf_vectorizer.fit_transform(
        [" ".join(jieba.cut(doc)) for doc in corpus]
    )

    # 将query转换为TF-IDF特征向量
    query_vector = tfidf_vectorizer.transform([" ".join(jieba.cut(q)) for q in query])

    # 计算query与语料库中每个文档的余弦相似度
    similarities = cosine_similarity(query_vector, tfidf_matrix)

    # 找到最匹配的文档索引
    most_similar_index = similarities.argmax()

    # 获取最匹配的文档内容
    most_similar_document = corpus[most_similar_index]

    print(most_similar_document)


if __name__ == "__main__":
    main()
