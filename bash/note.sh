#!/bin/bash

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












