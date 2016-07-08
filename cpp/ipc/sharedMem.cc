/* IPC: shared memory
 * July 8, 2016: copy code from internet, no test run
 */
//写入方

#include <stdlib.h>   
#include <sys/shm.h>
#include <sys/ipc.h>  
#include <unistd.h>  
#include <string.h>

#define PATH ""
#define SIZE 512
#define ID 0
int main()
{
    char * shmAddr;
    char * dataAddr = "Hello";
    int key = ftok(PATH,ID);
    int shmID = shmget(key,SIZE,IPC_CREAT);
    shmAddr = shmat(shmID,NULL,0);
    strcpy(shmAddr,dataAddr);
    shmdt(shmAddr);
    exit(0);
}

//接收方

#include <stdlib.h> 
#include <stdio.h>  
#include <unistd.h>  
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>  

#define PATH ""
#define SIZE 0
#define ID 0
int main()
{
    char * shmAddr;
    char * dataAddr = "Hello";
    int key = ftok(PATH,ID);
    int shmID = shmget(key,SIZE,0);
    shmAddr = shmat(shmID,NULL,0);
    printf("%s\n",shmAddr);
    shmdt(shmAddr);
    shmctl(shmID, IPC_RMID, NULL);
    exit(0);
}

代码比较简单，不难看出，通过函数shmget(),我们得到了对一块共享内存的标记，然后通过shmdt()，然后和我们的进程绑定得到这块共享内存的地址，然后即可输出该块内存区域中的数据。主要涉及几个参数，ftok(),shmget(),shmat()。

    ftok():接受两个参数一个是文件目录，一个是我们的projectid，对于第二个id，我们这里可以随便制定，此处指定0，该函数可以为当前IPC生成一个唯一的键值。
    shemget():第一个参数是我们进程的键值，第二个参数是我们指定内存区域的大小，如果制定为0则代表我们只是打开，而不是去创建，第三个参数是制定我们对该内存区域的操作模式权限。
    shmat:该参数的作用是将我们的共享内存映射到我们的当前进程的内存空间。得到了其地址。第一个参数是我们要映射的共享内存的标示符。第二个参数是制定将共享内存的映射到我们进程空间的起始地址，如果制定为null，则会由系统自动分配一个。第三个参数是指定我们的操作模式，是读还是写，此处指定为0，表示既可以对其读又可以对其写。
    shmdt:这个函数是用来断开当前进程和该共享内存区域的连接，
    shmctl:该函数通过对于一些参数的指定来对共享内存区域进行一系列的控制，对于共享内存区域，设有一个计时器，当到达一定时间之后，如果没有进程和其绑定，该内存将会被回收。也可以不用手动对其回收。
