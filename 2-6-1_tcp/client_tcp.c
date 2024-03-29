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
#define portnumber 3333
/*线程清理函数*/

int main(int argc,char *argv[]){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    struct hostent *host;
    if(argc!=2){
        fprintf(stderr,"Usage:%s hostname \a\n",argv[0]);
        exit(1);
    }
    /*使用hostname查询host名字*/
    if((host = gethostbyname(argv[1])) == NULL){
        fprintf(stderr,"Get hostname error\n");
        exit(1);
    }
    /*客户端开始建立sockfd描述符*/
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){//AF_INET:internet;SOCK_STREAM:TCP
        fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
        exit(1);
    }
    /*客户端程序填充服务端的资料*/
    bzero(&server_addr,sizeof(server_addr));//初始化，置 0
    server_addr.sin_family = AF_INET;//IPV4
    server_addr.sin_port=htons(portnumber);//将本机上的short数据转化为网络上的short数据端口号
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);//IP地址
    /*客户端程序发起连接请求*/
    if((connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))) == -1){
        fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
        exit(1);
    }
    /*连接成功*/
    printf("Please input char:\n");
    /*发送数据*/
    fgets(buffer,1024,stdin);
    write(sockfd,buffer,strlen(buffer));
    /*结束通讯*/
    close(sockfd);
    exit(0);
}

