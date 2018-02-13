# 论文《Face Alignment at 3000 FPS via Regressing Local Binary Features》解读实现

> 2018/02/11

2016年开始做人脸对齐，试过ASM（STASM）和ERT（Dlib），最后在LBF这个方法上，优化，并最终实现稳定版本，在终端上运行，一张人脸8ms，人脸检测使用的S8/S9系统自带的（也可以考虑dlib自带和虹软开源的）。



论文中所说的”shape-indexed” features，就是指两点间像素值之差，灰度值之差。这个特征也将是用来做随机树的训练和用来生成LBF特征。在ESR论文出来后，state-of-art的关于Face Alignment就是1ms和这篇3000fps。1ms是ERT的方法，代表开原作品是Dlib。鉴于Dlib开源负责，底层实现多，解耦难度大，最后还是这篇LBF在实现上更容易。

论文最后并没有在随机森林建立后，在叶子节点放置偏移量Delta作为最后Predict的输出量。而是创造性的用叶子节点作为LBF特征分量，然后做全局线性回归去计算Delta。每棵树预测出稀疏矩阵32位，用uint32表示，每个特征点在tree_n=6棵树的预测后，得到6个uint32.



## 1. Dataset

数据集主要以helen为主，大概2k张。然后随机抓取了几百张不同类型的图片，并进行标注。主要有这么几类：

闭眼、戴眼镜，张大嘴，部分遮挡，侧脸，小角度Roll，和yaw的图片。

训练提供的人脸框，要和最后测试使用的人脸框算法，相一致。人脸框对于测试的结果，比较重要。





## 2. Train

训练的步骤：

1. 首先parse data. 将图片和人脸框数据，特征点数据，读进去。图片数据可以裁剪人脸框大小的。
2. data augmentation. 对于现有的数据集做flip处理，增加一倍数据集。
3. 得到mean shape 并 做LBF::Train.
4. 基于cascade，每个stage都建立随机森林。这个随机森林，是针对每个点来建。每个点，6棵树，每棵树的建立（splitNode）是基于整个数据集来做的。
5. 森林做好，对训练集中每张图片，做LBF提取。每张图存一个LBF分量，里面放着68个点的6棵树的结果。所以是N张图片 * 68个点 * 6棵树 * 32位LBF特征
6. 全局回归，根据LBF，得到对应的delta shape
7. 用新的偏移量得到下个阶段的初始shape模型



SplitNode 步骤：

1. 随机树的建立就是一个如何分裂特征的过程。一般挑选特征向量交叉熵比较大的。熵比较大，认为内部一致性小。
2. 随机在current shape 半径范围内找500个特征向量。对这个类似Mat(500,N)的向量里，找出最大下降Max reduce variance. 那个index中存储的两个点的(x,y)和当时分裂的threshold，保存至分裂的节点。
3. 每棵树的非叶子节点，都递归做一遍。作为LBF特征提取的依据。在相对两个位移的点，求灰度差，再对比threshold，决定往左还是往右去遍历树。
4. feats_m (500) & radius (0.3) 都是可以配置的参数。每个stage不同。为什么一开始的半径和feats_m都比后面的要大？因为一开始groundtruth的shape 和 mean shape肯定有比较大的距离差，所以半径和点数选大，有利于一开始的回归精确，后续stage，随着不断逼近groundtruth，半径和feats_m都越来越小。



## 3. Predict

预测的步骤：

1. 根据图片和meanShape， 求取LBF特征。这个求取的过程，是对随机森林的遍历。这里面应该保存了是5个阶段的数据。
2. 根据LBF特征，求取全局线性回归。
3. 算出Delta shape后，相应的偏移量就出来了。





## 4. Issues

---

**Flicker**

1. 图像预处理，人脸框里面区域做Blur
2. 人脸框检测后，如果每帧的人脸框都不断更新，对LBF的特征点检测也会有Flicker的影响。所以，对Camera Preview时的Face Rectangle做滤波处理，一定范围之内的位移做忽略处理。
3. 特征点检测完结后，对前后帧的特征点Flicker做滤波处理，大致和FaceRectangle一样。首先将前后帧的Shape映射到[-1,1]之间，各自占50%，然后再放回来。其次，对每个特征点，大位移做滤波，小位移做忽略。




---

**Orientation**

1. 270度的Orientation才可以不用做处理，其他方向的Orientation，全部需要对FaceRectangle 做处理之后，再特征点检测完，再处理回来。这个涉及到具体机型，depends on机子保存下来的图片。
2. 具体做法是: 无论图片保存下来，头是朝哪个方向的. 系统给的人脸框都是(左上, 右下)。你需要做的是，对照正脸方向的左上，右下，才是最后需要保存的人脸框数据。Predict之后，再转换回来。
3. 好处是可以节省整个image旋转的时间。自拍时的大脸，3000*4000像素是很大的。cv::resize又损失了精度。




---

**Challenge Roll Angle**

1. 用last Shape上一帧的数据来对mean shape做处理，将mean shape做一定程度的角度旋转。
2. 注意的是，这里是算calcSimilarityTransform。然后再将mean shape旋转。为什么不能直接用last shape做下一帧的mean shape? 因为训练时，并没有根据上一帧的shape去当做mean shape去做训练。所以，训练和预测，要保值一致性。如果以后可以用视频作为训练，这个方法就可行。
3. 这个对大角度的Roll比较好。但是如果是大动作，比如大嘴，就需要其他方法。




---

**Data Association Face Rectangle Detection**

1. 这个算法DA，主要是针对多张人脸来做的。效果是，前后帧的人脸对比。这帧的人脸框，是否是上帧的人脸框。如果人脸框1对应的是同一个人，可以用last Shape去做ChallengeRollAngle LBF检测，且可以做后期滤波处理。如果不是同一个人，就只能用MeanShape做LBF检测，且不可以做后期滤波处理。

   ​

## 5. Global Variables

1. Orientation

   如果前后帧的orientation不变，处理。如果变化了，前期的保留下来的数据都不能用了，得作为第一帧来处理。前期数据，包含last shape, last landmarks, last face rectangle 等。

2. last face rectangle

   这个全局数据，是用来滤波前后帧的人脸框数据。如果多人的检测，还牵涉到前后帧的人脸框是否是同一个人，这就涉及到这次对这个人脸框是否可以用last shape 和 last landmarks做后期滤波处理flicker。

3. last shape

   上次检测特征点得到的一个Mat类型。如果是同一个人，前后帧可以 用last shape归一化到[-1,1]做50%滤波。

4. last landmarks

   这一步和last shape 一样，last landmarks 是对每个点来做的。每个点在一定范围内，用前帧数据代替；在一定范围之外，用滤波处理再显示。





---

**refs:**

1.  https://7color94.github.io/2017/01/face-alignment-via-local-binary-features/
2. [paper](www.jiansun.org/papers/CVPR14_FaceAlignment.pdf)
3. [github](https://github.com/luoyetx/face-alignment-at-3000fps)
