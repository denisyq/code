/* named pipe
 * 相较于匿名管道（只能在父子进程之间单向传送数据），
 * 有名管道可以在不同进程之间传输数据
 * 因为有名字，所以好找到。
 * July 8, 2016: update, copy code from internet, NO test run.
 */
 
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define FIFO_NAME "/oswork/pipe/myfifo"

int main()
{
        int res;
        int pipe_id;
        char buffer[] = "Hello world";
        if(access(FIFO_NAME,F_OK)==-1)
        {
                res = mkfifo(FIFO_NAME,O_WRONLY);
        if(res!=0)
                {
                        printf("Error in creating fifo.\n");
                        exit(1);
                }
        }
        pipe_id = open(FIFO_NAME,O_WRONLY);
        if(pipe_id!= -1)
        {
                if(write(pipe_id,buffer,PIPE_BUF)>0){
                        close(pipe_id);
                }else{
                        printf("Error in writing.\n");
                        exit(1);
                }
        }else
        {
                printf("Error in opening.\n");
                exit(1);
        }

//因为管道是通过本地磁盘上的文件进行信息的交换，因此我们需要给予其本地磁盘上的一个文件目录，然后根据该目录通过access（）函数来获取该管道，如果获取失败，那么我们就按照给定的目录创建一个，创建管道的时候，我们需要制定是对其进行读还是写，创建好之后，通过指定模式打开我们的管道，此时会得到一个管道号，然后根据获得管道标志号，作为参数，进行read和write操作。下面是读端的执行代码。

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define FIFONAME "/oswork/pipe/myfifo"
int main()
{
        char buffer[PIPE_BUF+1];
        int pipe_id;
        pipe_id = open(FIFONAME,O_RDONLY);
        if(pipe_id != -1)
        {
                read(pipe_id,buffer,PIPE_BUF);
                printf("%s",buffer);
        }else{
                printf("error in reading\n");
        }
}
