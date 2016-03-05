#!/usr/bin/python

def foo(a,b):
	print('{}==a,{}==b'.format(a,b))

while True:
	for i in ["/","*","|","\\","|"]:
		print("%s\r",i)


首先，服务端开发涉及到的东西比较多：
1、操作系统
操作系统现在的情况是三分天下：unix、linux、windows。建议学习linux，主要是掌握基本的服务器管理与配置命令，能够编写shell脚本进行部署以及自动化管理等。
2、服务器
Nginx、Apache都是常见的服务器。这两个服务器各有各的特点，我这里不能说哪个一定比哪个好。网上也有很多对这两个服务性能的对比与讨论可供参考。
3、数据库
数据库有Mysql、Oracle、SQL server等这些都是关系型数据库，还有非关系型数据库：memcached、mongodb、redis等。建议了解各种数据库的特点，根据自己的业务模型，选择最优的搭配。
4、开发语言
开发语言有很多python、php、perl、c++、java...基本上大部分语言都可以开发后台。每种语言都有自己的特点与框架，像这些语言都有很多公司用。
据我所知，使用python作为后台开发的有知乎、豆瓣、quora，而且现在大部分的新型互联网公司都倾向于使用python作为后台的开发语言。
python作为后台开发主要是可以实现快速的开发，同时可供选择的开发框架也有很多，比如：flask、django、tornado、bottle等。建议了解这些框架的特点。
5、TCP/IP协议
了解基本的协议：HTTP、DNS、SMTP、SNMP。。。
6、数据交换格式
protobuf、json、xml。。。
这里面最节约空间与速度最快的是protobuf，一般使用json就好了，json的在空间与速度上都优于xml。如果是特别追求节约空间与速度就使用protobuf。
...


主流的app的服务端：
应该没有所谓的主流吧 - - 我只知道instagram使用了nginx、django、Gunicorn。。。
像instagram这么多用户的应用后台绝对不是这么简单。What Powers Instagram: Hundreds of Instances, Dozens of Technologies这篇文章是他们公布的架构，可供参考，另外网上也有一些逼人翻译与分析的文章。

最后说下我的用法：
目前使用nginx+uWSGI+flask
flask是python的一个轻量级框架，上面有介绍。
nginx主要是处理静态的请求，动态的交给uWSGI。
uWSGI是一个服务器，使用它可以很方便的部署python应用，而且处理速度也比较快。
网上可以找到很多关于nginx+uWSGI+flask的配置介绍
