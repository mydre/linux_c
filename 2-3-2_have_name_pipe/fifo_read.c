#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define FIFO "/tmp/myfifo"
int main(int argc, const char * argv[]) {
    char buf_r[100];
    int fd;
    long nread;
    printf("Preparing for reading bytes...\n");
    memset(buf_r,0,sizeof(buf_r));
    /*打开管道*/
    fd = open(FIFO,O_RDONLY|O_NONBLOCK,0);
    if(fd == -1){
        perror("open");
        exit(1);
    }
    while(1){
        memset(buf_r,0,sizeof(buf_r));
        if((nread = read(fd, buf_r, 100)) == -1){
            if(errno == EAGAIN)
                printf("no data yet\n");
        }
        printf("read %s from FIFO\n",buf_r);
        sleep(1);
    }
    /*〃后面三句话是不会被运行到的,但 不会影响程序运行的效杲当 在上面的死循环中执行时收到信号后会马上结束运行而没有执
     面的三句话。这些会在后面的信号处理中讲到,现 在不理解没 系,这 个问题留给大家学习了信号处理之*/
    close(fd);//关闭管道
    pause();//暂停，等待信号
    unlink(FIFO);//删除文件
    return 0;
}

