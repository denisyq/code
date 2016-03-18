#!/usr/bin/python

#jieba
import jieba 
import requests
from bs4 import BeautifulSoup

def extract_url(url):
	page_source = requests.get(url).content
	bs_source   = BeautifulSoup(page_source,"lxml")
	report_text = bs_source.find_all('p')

	text=''

	for p in report_text:
		text += p.get_text()
		text += '\n'
	return text 


def word_freqency(text,num):
	from collections import Counter

	words = [word for word in jieba.cut(text,cut_all=True) if len(word) >=2 ]
	c= Counter(words)

	for word_freq in c.most_common(num):
			word,freq = word_freq
			if freq >= 10:
				print word, freq
			else:
				break

def extract_file(filename):
	import re
	text = []
	with open(filename) as f:
		for line in f.readlines():
			words = [word for word in re.split(r'[\s,:;.|()]\s*',line) if len(word) >=2 ]
			text.extend(words)

	from collections import Counter
	c = Counter(text)
	for word,freq in c.most_common(10):
		if freq >= 3:
			print word,freq
		else:
			break

url="http://www.nytimes-se.com/"
filename="tmp"

text=extract_url(url)
word_freqency(text,20)

print "----extract file-------"
extract_file(filename)
