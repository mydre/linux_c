#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, const char * argv[]) {
    int pipe_fd[2];
    pid_t pid;
    char buf_r[100];
    long r_num;
    
    
    memset(buf_r,0,sizeof(buf_r));
    /*创建管道*/
    if(pipe(pipe_fd) < 0){
        printf("pipe create error\n");
        return -1;
    }
    /*创建子进程*/
    if((pid = fork()) == 0){// 子进程执行序列
        printf("\n");
        close(pipe_fd[1]);//子进程先关闭了管道的写法
        sleep(2);/*让父进程先运行，这样父进程先写，子进程才有内容读*/
        if((r_num = read(pipe_fd[0],buf_r,100) )> 0){//buf_r来存放从管道读取的内容
            printf("%lu numbers read from the pipe is %s\n",r_num,buf_r);
        }
        close(pipe_fd[0]);
        exit(0);
    }else if(pid > 0){
        close(pipe_fd[0]);//父进程关闭了管道的读端
        if(write(pipe_fd[1],"Hello",5) != -1)//将字符串写入管道
            printf("parent write1 Hello!\n");
        if(write(pipe_fd[1],"Pipe",5)!=-1)
            printf("parent write2 Pipe!\n");
        close(pipe_fd[1]);
        waitpid(pid,NULL,0);/*等待子进程结束*/
        exit(0);
    }
    return 0;
}

