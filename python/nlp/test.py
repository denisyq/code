#!/usr/bin/python
#coding:utf-8
import jieba
import numpy as np
import scipy
import sklearn
import jieba.posseg as pseg
import os
import sys
from collections import deque

with open('./test_ch.txt','r') as f:
    text = f.read()
    text_seg = jieba.cut_for_search(text)
    result = " ".join(text_seg)
#result_output =result.encode('utf-8')
    print (result)

