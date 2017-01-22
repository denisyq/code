#1 basic
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

3. 赋值 val=value
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
		return 0;
	}
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

13. && || -a -o
14. -gt -lt -ge -le -eq -ne
15. 文件测试
	[ -f $file ] #文件存在
	[ -x $file ] #文件可执行
	[ -d $file ] #目录存在

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






function subfun { ## 5
	if [ -f /bin/tar ];then ## 6
		tar -zxvf a.tar.gz $1
	fi
	if [ ! -e delu ];then   ## 6
		mkdir -p delu
	fi
}
##5 function 
##6 -f file; -d dir; -e file exist;






count=1
for file in *.cpp    ## 7
	do
		cp $file $file.bak 2> /dev/null  ## 2
		if [ $? -eq 0 ];then             ## 8
			echo "good"
			let count++                  ## 9
		fi
	done
##7 for loop
##8 $? cp command return status
##9 let used in integer





myfunc() {
	echo "$#"  ## 10
}
echo "the number of parameter in "$@" is " $(myfunc "$@")  ##11
echo "the number of parameter in "$*" is " $(myfunc "$*")
##10 $# = number of parameters in
##11 $@ and $* -> list all parameters in,like ./a.sh hi "hello you" will get hi hello you
				# but when "$@"->"hi" "hello you" and "$*"->"hi hello you"











