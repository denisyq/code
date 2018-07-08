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
from sklearn import preprocessing

#jieba
jieba.cut("",cut_all=True)
jieba.cut("")
jieba.cut_for_search("")
jieba.set_dictionary('dict.txt.big')#jieba use new dict words to cut
jieba.load_userdict('userdict.txt')#user dict defines specific words

#词性
import jieba.posseg as pseg 
words=pseg.cut(f.read().strip())
for word in words:
    print word.word, word.flag #词性形容词等

#jieba TF-IDF
import jieba
from jieba import analyse
tf_idf = analyse.extract_tags
tags = jieba.analyse.extract_tags(sentence,topK=20, withWeight=False, allowPos=())#待提取文本，返回K最大的关键词，是否一并返回权重值
#这个功能，jieba需要判断stopWords,用的自己的，需要判断IDF,也是用的自己的语料库。所以这个功能，在高精确度的地方，无法使用
analyse.set_stop_words("stop_words.txt")#自己设置停用词
analyse.set_idf_path(file_name)
keywords = tf_idf(text)

def stopWordsList(filepath):
    stopwords=[ line.strip() for line in open(filepath,'r',encoding='utf-8').readlines()]
    return stopwords

def seg_sentence(line):
    sentence_seg = jieba.cut_for_search(line.strip())
    stopwords = stopWordsList('/home/luyq/nlp/stopWords_ch.txt')
    outStr=""
    for word in sentence_seg:
        if word not in stopwords:
            if word != '\t':
                outStr += word
                outStr += " "
    return outStr

def seg_text(text):
    text_seg = jieba.cut_for_search(text.strip())
    stopwords=stopWordsList('/home/luyq/nlp/stopWords_ch.txt')
    outStr=""
    for word in text_seg:
        if word not in stopwords:
            outStr += word + " "
    return outStr

def wordFreq(filename):#词频统计，降序排序
    text = open(filename,'r').read()
    words = jieba.cut(text)
    words_freq = {}
    for word in words:
        if word in words_freq:
            words_freq[word] += 1
        else:
            words_freq[word] = 1
    #dict => list
    freqs = []
    for word, freq in words_freq.items():
            freqs.append((word,freq))#list里放tuple
    freqs.sort(key = lambda x: x[1], reverse=True)
            num = 10
    for word, freq in freqs[:num]:
            print (word,freq)


def deleteStopwords(stopWordsFile):
    stopWords = stopWordsList(stopWordsFile)
    text = jieba.cut(open("test.txt").read())
    output = []
    for word in text:
        if word.encode("utf-8") not in stopWords:
            output.append(word)

with open('/home/luyq/nlp/test_ch.txt','r') as f:
    text = f.read()
    words_seg=seg_text(text.strip())
    print (len(words_seg))
    print (len(set(words_seg)))
    '''
    for line in f:
        line_seg = seg_sentence(line)
        print (len(line_seg), line_seg)
    '''

with open('/home/luyq/nlp/test.cpp', 'r') as f:
    test = f.read();
    for line in f.readlines():
        print (len(line))


'''
#NLTK 对中文的分割句子，单词不行，可另外选择jieba
#中文


#英文
#nltk分割句子
from nltk import sent_tokenize
sentences = sent_tokenize(text)
print (sentences[:1])

#nltk分割单词
from nltk.tokenize import word_tokenize
tokens = word_tokenize(text)
print (tokens[:100])
tokens = [w.lower() for w in tokens]
import string
table = str.maketrans('','',string.punctuation)#标点符号去掉
stripped = [w.translate(table) for w in tokens]
words = [word for word in stripped if word.isalpha()]#只保留字母级别的单词

#nltk英文停用词
from nltk.corpus import stopwords
stop_words = set(stopwords.words('english'))
words = [w for w in words if not w in stop_words]#去掉停止词

#单词提取词干
from nltk.stem.porter import PorterStemmer
porter = PorterStemmer()
stemmed = [porter.stem(word) for word in words]
print (len(stemmed))
print (len(set(stemmed)))
print (stemmed[:100])
'''

