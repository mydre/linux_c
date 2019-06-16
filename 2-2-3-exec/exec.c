#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, const char * argv[]) {
    if(argc < 2){
        perror("you haven't input the filename,please try again!\n");
        exit(EXIT_FAILURE);
    }
    /*调用execl函数，用可执行程序file_creat替换本进程*/
    if(execl("./file_creat","file_creat",argv[1],NULL) < 0){
        perror("execl error!");
    }
    
}
