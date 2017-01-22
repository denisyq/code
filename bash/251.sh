#!/usr/bin/expect
spawn ssh luyq@109.123.123.251
expect "*password:"
send "yanqing1984\r"
expect "luyq*"
interact

