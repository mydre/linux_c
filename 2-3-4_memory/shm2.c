#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include "shm_com.h"
int main(int argc, const char * argv[]) {
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;
    /*创建共享内存*/
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
    if(shmid == -1){
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    /*映射共享内存*/
    shared_memory = shmat(shmid, (void *)0, 0);
    if(shared_memory == (void *) - 1){
        fprintf(stderr,"shmat failed");
        exit(EXIT_FAILURE);
    }
    printf("Memeory attached at %X\n",(unsigned int *)shared_memory);
    /*让结构体指针指向这块共享内存*/
    shared_stuff = (struct shared_use_st *)shared_memory;
    /*控制读写顺序*/
    shared_stuff->written_by_you = 0;
    /*循环的从共享内存中写数据，直到写入的为“end”为止*/
    while(running){
        while(shared_stuff->written_by_you ==1){
            sleep(1);//等到进程读完之后再写
            printf("waiting for client...\n");
        }
        printf("Enter sometext:");
        fgets(buffer,BUFSIZ,stdin);
        strncpy(shared_stuff->some_text,buffer,TEXT_SZ);
        shared_stuff->written_by_you = 1;
        if(strncmp(buffer, "end", 3) == 0){
            running = 0;//结束循环
        }
    }
    /*删除共享内存*/
    if(shmdt(shared_memory) == -1){
        fprintf(stderr,"shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    return 0;
}

