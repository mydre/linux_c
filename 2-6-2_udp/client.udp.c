#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>//这里定义的有read函数
/*线程清理函数*/
#define SERVER_PORT 8888
#define MAX_MSG_SIZ 1024
void udpc_requ(int sockfd,const struct sockaddr_in *addr,int len){
    char buffer[MAX_MSG_SIZ];
    int n;
    while(1){
        /*从键盘读入，写到服务端*/
        printf("Please input char:\n");
        fgets(buffer,MAX_MSG_SIZ,stdin);
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)addr,len);
        bzero(buffer,MAX_MSG_SIZ);
    }
}
int main(int argc,char **argv){
    int sockfd;
    struct sockaddr_in addr;
    if(argc != 2){
        fprintf(stderr,"Usage:%s server_ip\n",argv[0]);
        exit(1);
    }
    /*1  客户端开始建立socket描述符*/
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        fprintf(stderr,"Socket Error:%s\n",strerror(errno));
        exit(1);
    }
    /*2  服务端填充。sockadddr结构*/
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    if((inet_aton(argv[1],&addr.sin_addr)) < 0){
        /*inet_aton函数用于把字符串的ip转化为网络2进制数字*/
        fprintf(stderr,"IP error:%s\n",strerror(errno));
        exit(1);
    }

    udpc_requ(sockfd, &addr, sizeof(struct sockaddr_in));//进行读写操作
    close(sockfd);
}

