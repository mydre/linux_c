#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>
#include<sys/types.h>
#include<string.h>
int main(int argc, const char * argv[]) {
    pid_t child;
    /*创建子进程*/
    if((child = fork()) == -1){
        printf("Fork Error:%s\n",strerror(errno));
        exit(1);
    }else if(child == 0){
        printf("the child process is runing\n");
        sleep(1);//子进程睡眠一秒，但并没有去运行父进程
        printf("i am the child:%d\n",getpid());
        exit(0);
    }else{
        wait(NULL);//等到子进程退出，父进程才会运行
        printf("the father process is runing\n");
        printf("i am the father:%d\n",getpid());
        return 0;
    }
}

