#include <string>

cons:
1. string s1;
2. string s2(s1);
3. string s3(10,'x');
4. string s4(s1.begin(),s1.begin()+7);
5. string s5(s1,3(position),7(length));
6. string s6("hello world");
7. string s7("hello world",6);

iter:
begin();
end();
rbegin();
rend();

capacity:
size();
empty();
resize();
length();
reserve();
clear();

element_access:
[];
at;
front();
back();

modify:
+=          //string s; s+="hello"

push_back(char c);
pop_back();

assign();   6 ways -  similar to cons

insert();   similar to cons
1. s1.insert(6,"hello world",4);                //this insert can return string&
2. s1.insert(s1.begin()+6,"hello world",4);     //this insert return void,iterator failed

erase();
1. erase(iterator);
2. erase(iter1, iter2);
3. erase(pos,length);   //this erase can return string&

swap();

append();           //6 ways. 
1.string.append(second);
2.string.append(second,npos,size);
3.string.append("hello");
4.string.append("hello",size);
5.string.append(10,'c');
6.string.append(second.begin(),second.begin()+4);

replace();
1. first.replace(npos,size,string& );
2. first.replace(it1, it2, string& );
3. using "hello" instead of string&
4. first.replace(npos, len, string& , subpos, sublen);
5. first.replace(npos, len, "hello", sublen);
6. first.replace(it1, it2, "hello", sublen);
7. first.replace(it1, it2, second.begin(), second.begin()+4);

substr();
string.substr(npos,len);

compare();
1. string.compare(string& );
2. string.compare(npos,len,string&);
3. string.compare(npos,len, string& ,subpos, sublen);
4. string.compare("hello");
5. string.compare(npos,len,"hello");
6. string.compare(npos.len,"hello",size);   //when related to char*, no subpos, no sublen, always size


find();             //return size_t, if(ret != string::npos)
1. string.find(string& );
2. string.find("hello");
3. string.find('c');

rfind();

//find_first_of means "abcdefg".find_first_of("cde"); when find 'c','d','e',will return
find_first_of();
find_last_of();

find_first_not_of();
find_last_not_of();

//----------------------------
c_str();
string dennis("Dennis");
const char* ptr = dennis.c_str();
c_str()应该拿到char*立刻就得用，如果后续有 dennis += ",hello world"; ptr就不再指向"Dennis,hello world"
为什么？因为string在执行+=之后，可能reserve空间发生变化，原先地址不够大，重新换地方申请空间了．
//----------------------------


/******************
 * 字符串匹配算法
 ******************/
在字符串匹配问题中,　我们应该有KMP, BM, Sunday算法，还有Trie和AC状态机
有一个字符串S1和模式串S2, 如何去查找Ｓ２在Ｓ１中的匹配位置

1. 暴力破解，　复杂度O(M*N)
	string s1, s2;
	s1 = "hello world";
	s2 = "orlr";
	int len = s1.length()-s2.length();
	for(int i=0;i<len;i++){
	    if(s2.compare(0, s2.length(), s1, i, s2.length()) == 0)
	        cout<<"Find: "<<i<<endl;
	}
	//or you can change to following
	int i = 0;
	int j = 0;
	int len1 = s1.length(), len2 = s2.length();
	while(i < len1 && j < len2){
		if(s1[i] == s2[j]){
			i++;j++;
		}else{
			i = i - j +1; //==>这个地方是将来ＫＭＰ算法需要改进的地方 next[j]
			j = 0;
		}	
	}
	if(j == len2) return i-j;
	else return -1;
	

在这个算法中，我们通过不断移动模式串来compare文本串，如果不对，就往后移动一位。
但是，只往后移动一位，太不高效了，这就是有了，如何去界定往后移动几位再去compare.


2. KMP
	KMP主要就是在next[i]函数，这个next数组用来保证往后走几步再去匹配，是对暴力解法的优化
	while(i < len1 && j < len2){
		if(j == -1 || s1[i] == s2[j]){
			i++;j++;
		}else{
			j = next[j];//最长前缀和后缀公共子串
		}
	}
	if(j == len2) return i-j;
	else return -1;

	next[j]是在ｊ匹配不上后，前面子川的最长前缀和后缀的公共部分，然后把前缀公共部分和后缀部分重合，就相当于移动这么多步伐。
	
	void getNext(char* p, int next[]){
		int pLen = strlen(p);
		next[0] = -1;
		int k = -1;
		int j = 0;
		while(j < pLen -1){
			//p[k] 表示前缀 p[j]表示后缀
			if (k == -1 || p[j] == p[k]){
				++k;
				++j;
				next[j] = k;
			}else
				k = next[k];
		}
	}
















