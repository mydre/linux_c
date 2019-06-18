#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *thread(void *str){
    int i;
    for(i=0;i<3;i++){
        sleep(2);
        printf("This in the thread:%d\n",i);
    }
    return NULL;
}

int main(){
    pthread_t pth;
    /*创建线程并执行线程执行函数*/
    int ret = pthread_create(&pth, NULL, thread, NULL);
    printf("The main process will be to run,but will be blocked soon\n");
    /*进程阻塞等待线程退出之后进程被唤醒*/
    pthread_join(pth, NULL);
    printf("thread was exit\n");
    for(int i=0;i<3;i++){
        sleep(1);
        printf("This is the main:%d\n",i);
    }
    return 0;
}
