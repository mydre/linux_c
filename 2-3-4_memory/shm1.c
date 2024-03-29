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
    /*循环的从共享内存中读数据，直到读到“end”为止*/
    while(running){
        if(shared_stuff->written_by_you){
            printf("You wrote:%s",shared_stuff->some_text);
            sleep(1);//读进程睡一秒，同时会导致写进程睡一秒，这样做到读了之后再写
            shared_stuff->written_by_you = 0;
            if(strncmp(shared_stuff->some_text,"end",3) == 0){
                running = 0;//结束循环
            }
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

