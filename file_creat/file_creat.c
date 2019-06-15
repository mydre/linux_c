#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void create_file(const char *filename){
    /*创建的文件具有可读可写的属性*/
    if(creat(filename,0666)<0){
        printf("create file %s failure!\n",filename);
        exit(EXIT_FAILURE);
    }else{
        printf("create file %s success!\n",filename);
    }
}
int main(int argc, const char * argv[]) {
    /*判断入參有没有传入文件名*/
    if(argc < 2){
        perror("you haven't input the filename, please try again!\n");
        exit(EXIT_FAILURE);
    }
	printf("%s\n",argv[0]);
	create_file(argv[1]);
    exit(EXIT_SUCCESS);
    return 0;
}

