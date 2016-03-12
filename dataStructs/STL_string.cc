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

















