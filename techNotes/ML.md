#ML
##KNN K近邻
样本集里面有标准分类标签，然后新来测试数据，对每个训练集中数据进行距离计算（归一化），然后找出最近的K个分量
根据最近的K近邻，来进行分类
缺点：需要大量数据集的空间存储，计算量也比较大，耗时,无法给出数据的内在含义

##决策树
使用数据类型：数值型和标称型


监督学习
(分类 · 回归)
    决策树 表征（装袋, 提升，随机森林） k-NN 线性回归 朴素贝叶斯 神经网络 逻辑回归 感知器 支持向量机（SVM） 相关向量机（RVM）

聚类
    BIRCH 层次 k平均 期望最大化（EM）
    DBSCAN OPTICS 均值飘移

降维
    因子分析 CCA ICA LDA NMF PCA LASSO t-SNE

结构预测
    概率图模型（贝叶斯网络，CRF, HMM）

异常检测
    k-NN 局部离群因子

神经网络
    自编码 深度学习 多层感知机 RNN 受限玻尔兹曼机 SOM CNN

强化学习
    Q学习 SARSA 时间差分学习

##一个典型的金融领域的机器学习应用
1. 将研究报告等PDF文件，通过分类/学习/聚类主题提取/情绪分析等，变成有价值的投资建议
2. 涉及领域：NLP/ML/图像处理
3. 首先是PDF分析：pdf识别，opencv，OCR(tesseract)，然后文字要进入SQL/MySql等存储
4. 然后是NLP分析：word2vec/LSTM/SVM/情绪分析
5. 最后是ML分析 : 这里还有TensorFlow，Keras，SKlearn, seq2seq, python, java
