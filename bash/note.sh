###############################################################################################
#Overview: Shell 是一门非常贴近于Unix的和Unix命令行的脚本语言，它在Unix系统中有着天然亲的地位
#Shell的语法很简单，没有太多需要记忆的。Unix的命令行和文本的sed/awk就足够应付日常的Unix管理工作
###############################################################################################

##1 basic principle
1. ";"作为分界符号
2. echo 自带'\n' 但是printf 不带
	echo "hello world"
	printf "%-5s %-10s\n" Hello World
	%s %d %c %-4.2f
	%-5s 左对齐　不带是右对齐
	color print: echo -e "\e[1;31m This is Red color \e[0m"
	RED="\e[1;31m"
	REDEND="\e[0m"
	echo -e "$RED this is red color $REDEND"
	颜色码　重置＝０　黑色＝４０　红色＝４１　绿色４２　黄色４３　蓝色４４　白色４７

3. 赋值 val=value #var赋值，中间没有空格
   比较 val = value
4. 字符串长度 length=${#val}
5. 默认变量 $UID $SHELL $HOME $PWD $USER
	if [ $UID -ne 0 ];then #$UID = 0 是超级用户
	echo Non Root user
	else
	echo Root User
	fi
6. 数学运算
	val=4
	let result=val+4
	let result++
	result=$[ val + 2 ]
	小数点浮点数
	echo "3*1.23" |bc
	echo "scale=2;3/8" | bc #精确到小数点后２位
7. 文件描述符
	0 stdin
	1 stdout
	2 stderr
	echo "hello world" > delu.txt
	echo "hello world" >> delu.txt
	错误cmd 2> err.txt 1>out.txt
	cmd > out.txt 2>&1
	cmd > /dev/null #不想要的信息，送给黑洞
8. 数组
	array=(1 2 3 4)
	echo ${array[0]}
	echo ${array[*]} #all elements
	echo ${#array[*]} #length of array
9. 函数
	function fname()
	{
		statements;
		echo $1, $2;
		echo "$@"; #以列表的方式打印所有参数,参数都是单独的string
		echo "$*"; #跟$@一样,是一个整体string
		echo "$#"; #入参个数
		return 0;
	}
	##$@ and $* -> list all parameters in,like ./a.sh hi "hello you" will get hi hello you
10. $? cmd执行结果返回值
	如果shell中执行了一个linux cmd，要根据执行结果判断执行问题

	cmd
	if [ $? -eq 0 ];then
		echo "successful"
	else
		echo "failure"
	fi

11. read
	read -n 2 var #读取两个字符
	echo $var

	read -p "input your passwd:" var
	read -t 2 var #2秒之内
	read -d ":" var #以：为分界符

12. for/if/while
	for i in {a..z}
	do
		echo $i
	done


	if [ ];then
		echo
	elif [ ];then
		echo
	else
		echo
	fi


	while condition
	do
		echo
	done


	break 
	continue

13. && || -a -o
14. -gt -lt -ge -le -eq -ne #这块内容看《shell脚本学习指南》Page140
15. 文件测试
	[ -f $file ] #文件存在
	[ -x $file ] #文件可执行
	[ -d $dir ] #目录存在
	[ -e $f ]   #exist
	文件夹测试
	if [ ! -e /home/tmp ];then #文件夹存在
		mkdir -rp home/tmp
	fi

16. 字符串比较
	[[ $str = $str1 ]]
	[[ $str != $str1 ]]
	[[ -z $str ]] #空字符，返回真
	[[ -n $str ]] #非空字符，返回真
	if [[ -n $str ]] && [[ $str = "hello" ]];then
	echo $str
	fi

17. 压缩多余空行
	cat a.txt | tr -s '\n'
	cat -s a.txt
	cat -n a.txt #显示行号

18. find
	find ./ -iname "*.jpg"
	find ./ \( -iname "*.jpg" -o -iname "*.txt" \) #找jpg txt
	find ./ ! -iname "*.jpg" #找非jpg文件
	find ./ -maxdepth 2 -type f #最深为２，格式是file(-type d 目录)(-type l符号链接)
	#-atime/-mtime 以天为单位
	find . -atime -7 #7天内访问过的
	find . -atime 7  #正好七天前访问的
	find . -atime +7 #超7天的
	#-amin / -mmin 以分钟为单位

	find . -type f -newer file.txt #比file.txt 更早的
	find . -type f -size +2k #k/M/G
	find . -type f -iname "*.txt" -print |xargs wc -l

19. 命令行
	#sort
	sort -n file.txt
	sort -r (-M -C) file.txt

	cat data.txt
	1 mac   2000
	2 winxp 4000
	3 bsd   3000
	若以第二列排列 sort -k 2 data.txt
	
	#uniq
	sort file.txt | uniq -c #计数每行出现的次数

	#cut
	按照列切文件
	cut -d : -f 1,5 /etc/passwd #以冒号分界符切割第一和第五个字段

	#paste
	按照列合并文件 
	paste paste1.txt paste2.txt -d ","
	

20. 临时文件名
	tmp_file="/tmp/var.$$"
	tmp_file="/tmp/file-$RANDOM"

21. 灌文件
	dd if=/dev/zero bs=100k count=1 of=data.file #10k 10M 10G
	分割文件
	split -b 10k data.file
	$ split -b 10k data.file -d -a 4 split_file
	$ ls
	data.file split_file0002 split_file0003 ... #将分割后文件命名split_file000N

22. 扩展名提取分割

	path=$(pwd) ## 1
	echo $path
	find $path -iname "*.h" > log 2>&1  ## 2
	while read file
	do
			newfile=${file##*/}   ## 3
			echo $newfile ${#newfile} >> newlog ## 4
	done < log  ## 4
	##1 $(command) - runs commands
	##2 2>log->stderr, 2>&1 -> stdout/stderr
	##3
		## file=home/sandbox/mailbox/mail.exe
		## ${file%/*}  == home/sandbox/mailbox
		## ${file%%/*} == home
		## ${file#*/}  == sandbox/mailbox/mail.exe	
		## ${file##*/} == mail.exe
		## ${file:0:5} == home/
		## ${file:5:5} == sandb
	##4 ${#var} -> length of var
	##5 while read and flush file into input
	
	%　从后往前删除，不贪婪，从后面删除到分隔符就停止
	#  从前往后删除，不贪婪，从前面删除到分隔符就停止
	%% ## 分别是贪婪的
	
	%.* %%.* 分隔符是*
	#*. ##*.

23. 批量重命名
	count=1
	for file in *.jpg
	do
		tmp=${file%.*}.txt
		mv $file $tmp 2>/dev/null
		if [ $? -eq 0 ];then #return status $?
			echo "rename $file to $tmp"
			let count++
		fi
	done

24. 自动化脚本登录ssh

　　#!/usr/bin/expect
　　set timeout 30
　　spawn ssh -l username 192.168.1.1
	#spawn ssh luyq@109.123.123.251
　　expect "*password:"
　　send "ispass\r"
　　interact

25. 重定向 从file.txt 读入然后打印
	#打印每行，每个字，每个char
	while read line
	do
		echo $line
		for word in $line
		do
			echo $word
			for((i=0;i<${#word};i++))
			do
				echo ${word:i:1}
			done
		done
	done < file.txt ##file.txt作为输入，另外>是输出到文件
	# > < >> <<


26. sed
	在vim里面替换是用:%s/old/new/g
	在shell里面用sed: 
	1. sed 's/old/new/g' file
	2. cat file | sed 's/old/new/g'

	sed -i 's/old/new/g' file #-i,修改后的保存在源文件里
	/g #每行都替换
	/Ng #从第几行开始替换，Ｎ设置为几
	sed 's:old:new:g'
	sed 's|old|new|g' # : | 作为分界符都可以

	#移除空白行
	sed -i '/^$/d' file  # /pattern/d 移除
	#删除某些行
	sed -i 'm,nd' file #delete m-n lines　删除m到n行
	#\w\+ 匹配一个单词,,,,已匹配的标记&
	echo this is an example | sed 's/\w\+/[&]/g' ==> [this] [is] [an] [example]
	##这些都是正则表达式的内容
	
	#大写小写转换
	echo "hellsdafd" | sed 's/[a-z]/\u&/g'
	echo "HELLO" | sed 's/[A-Z]/\l&/g'

27. #在本地挂载点挂在远程驱动器 sshfs
	#这个很厉害，直接可以在自己的ubuntu上挂载服务器，在本地驱动器直接打开文件夹，类似samba
	sshfs luyq@109.123.123.251:/home/luyq /home/251mount
	unmount /home/251mount

28. #特殊变量 shell脚本学习指南Page132
	$# 入参个数
	$@ 
	$*
	$? 前一个命令退出状态 Page135解释0＝成功 >0 失败
	$$ Shell进程号
	$0 Shell程序名称
	$HOME $IFS $PATH $PPID $PWD

29. $((3>2)) $((3 && 4)) 算术运算符
	if grep pattern myfile || ! grep pattern myfile;then
	fi

30. exit shell程序退出
31. Shell内置命令
	dir=$(ls -al)
	cd command eval exit export fg fc getopts jobs kill read return wait
32. 批量修改文件夹里文件名带空格
	for file in $(ls *.jpg)
	do
		mv $file $new_name
	done
	#这样写不行，因为文件吗带空格，$file会变成两个文件

	#正确的写法：
	find ./ -iname "*.jpg" | rename 's/ //g'

33. 处理文本字符串中的空格
	cat tmp.txt | sed 's/ //g'

34. 显示文本中某一行或者中间一段
	cat tmp.txt | head -n 20 | tail -n +5 //首先显示前20行，然后tail后面，+10 意思是从第5行开始往后,共显示15行
	cat tmp.txt | head -n 20 | tail -n 15 //这个跟上面的是一个结果


