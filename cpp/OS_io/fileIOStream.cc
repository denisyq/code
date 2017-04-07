/*********************
* file io stream [cpp]
**********************/
#include <fstream>

1. 文件打开:
fstream file("a.txt", ios::in|ios::out);
fstream file; file.open("a.txt",ios::in|ios::out);

ios::in　　　　//供读，文件不存在则创建(ifstream默认的打开方式)
ios::out　　　 //供写，文件不存在则创建，若文件已存在则清空原内容(ofstream默认的打开方式)
ios::ate　　　 //文件打开时，指针在文件最后。可改变指针的位置，常和in、out联合使用
ios::app　　　 //供写，文件不存在则创建，若文件已存在则在原文件内容后写入新的内容，指针位置总在最后
ios::trunc　　 //在读写前先将文件长度截断为0（默认）
ios::nocreate　//文件不存在时产生错误，常和in或app联合使用
ios::noreplace //文件存在时产生错误，常和out联合使用
ios::binary　　//二进制格式文件

ios::app ----- 不能同时给read，指针已到最后，read不到数据
iOS::nocreate ios::noreplace 不是平台通用，注意

//检查成功失败
if (file)
if (file.good())

if (!file)
if (file.fail())
file.good()
file.bad()
file.eof()



2. 文件关闭
file.close()


3. 文件seek
file.seekg(绝对位置)
file.seekg(相对位置，参照位置)
file.seekg(ios::end)
file.seekg(5,ios::beg)
int pos = file.tellg() //返回指针位置k
//tellg用法
file.readline((char*)str.c_str(),100);
int len = file.tellg();
/* 等同于 */
size_t pos = str.find("\n");
if(pos != string::npos)
	pos == len;

//参照位置：
ios::beg
ios::end
ios::cur


4. 文件读写
file.read(char*, int length)
file.write(char*, int length)
file.getline(char*, int length) //若length很长，读到'\n‘结束
file.get(char)
file.put(char)
文件新写入一行，在中间某处，会覆盖后面的文字，所有中间插入一行的方法是：
->读取文件进一个string，string足够大
->在中间找“\n”, 确定是哪行
->string中插入待写入字符串（带换行符），所有重写文件中
‘
 44                 fstream ff1, ff2;
 45                 ff1.open("abc", ios::in);
 46                 ff2.open("abc1", ios::out);
 47                 if(ff1 && ff2){
 48                     ff1.seekg(0, ios::end);
 49                     size_t len = ff1.tellg();
 50                     ff1.seekg(0, ios::beg);
 51                     string tmp; tmp.resize(len,'\0');
 52                     ff1.read((char*)tmp.c_str(),len);
 53                     size_t pos = tmp.find("\n");
 54                     if(pos != string::npos){
 55                         string hello = tmp.substr(0,pos+1) + "hello\n" + tmp.substr(pos+1, len-pos-1);
 56                         cout<<hello;
 57                     }
 58                 }else
 59                     cout<<"open file failed"<<endl;
 60                 ff1.close();
 61                 ff2.close();
’

5. gcount
cin.get 后 cin.gcount()
file.read 后 file.gcount()


/*************
* IO stream 
**************/
1. cin/cout/cerr [ stdin/stdout/stderr]

cin.get(char* , int size) //只能读size-1个数据，最后一个是'\0'
cin.getline(char* int size)
cin.get() //将你输入的换行符\n也放进了cin buffer里，这次get没问题，后面再调用cin.get()将首先得到\n
cin.getline()//将输入的换行符抛弃，所以下次再调用cin.get() 就没问题
//总结：cin.get()连续的重复调用不行
#include <string> getline(cin,string&) //这个没size限制，跟gets一样有安全问题



/**************
* string stream
***************/
1. int/double 转 string

template<typename T>
void to_string(string& str, const T& t){
	stringstream ss;
	ss.clear();
	ss<<t;
	ss>>str;	
}


/******************
* file IO stream [c]
*******************/
1. FILE* fp = fopen("note.cpp","a+");
2. fgets(char* , int size, fp);
3. fputs(char* , fp);//no size parameter

//demo code
char buf[100];
fgets(buf, 100, fp)
fputs(buf, fp);

string s;
s.reserve(100);
fgets((char*)s.c_str(), 100, fp);
fputs((char*)s.c_str(),fp);

/*********
*binary IO
**********/
//针对结构体等数据类型（非字符串）
4. size_t fread(void*, size_t, int num_obj, FILE*) //数据指针，单个类型大小，读写几个类型，fp
5. size_t fwrite(void*, size_t, int num_obj, FILE*)
//demo code
float data[10];
if(fwrite(&data[1], sizeof(float), 4, fp) != 4) err_sys("fwrite error");

struct{
	short a;
	int b;
}item;
fwrite(&item, sizeof(item), 1, fp)

/*********
* snprintf
***********/
6. int snprintf(char* buf, size_t n, "%d",...)


/***********/
