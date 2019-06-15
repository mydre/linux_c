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
    if((child=fork()) == -1){
        printf("Fork Error: %s\n",strerror(errno));
        exit(1);
    }else if(child == 0){
        printf("i am the child:%d\n",getpid());
        exit(0);
    }else{//父进程
        printf("i am the father:%d\n",getpid());
        return 0;
    }
}

