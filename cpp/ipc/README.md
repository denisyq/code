# IPC的四种方式
1. 共享内存 shared memory
2. 消息队列 MQ
3. 管道，有名管道 pipe
4. 套接字  socket

陈硕在他的书里提过，IPC他比较推荐的是socket
所以，既然都需要跑两个main，起两个进程，为什么不直接用socket
unnamed pipe 可以在一个main里fork出两个进程。
所以一个main代表一个进程，多线程可以分享这个main里面的全局变量
果然是比多进程要高效的多
