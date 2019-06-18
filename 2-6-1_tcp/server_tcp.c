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
    int sockfd,new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned int sin_size;
    long nbytes;
    char buffer[1024];
    /*服务器开始建立sockfd描述符*/
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1){
        //AF_INET:IPV4;SOCK_STREAM:TCP
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
    }
    /* 服务器填充 sockaddr结构 */
    bzero(&server_addr,sizeof(struct sockaddr_in));//初始化，置0
    server_addr.sin_family = AF_INET; //IPV4
    
    /*将本机器上的long数据转化为网络上的long数据，服务器程序能运行在任何ip的主机上。
     INADDR_ANY表示主机可以是任意IP地址，即服务器程序可以绑定到所有IP上
    */
     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*
     server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");用于绑定到一个固定
     ip的主机上，inet_addr用于把数字加格式的ip转化为整型ip
     server_addr.sin_port=htons(portnumber);用于将本机器上的short数据转化为网络上的short数据（端口号）
    */
    server_addr.sin_port=htons(portnumber);
    /*捆绑sockfd描述符到IP地址*/
    if((bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))) == -1){
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
    }
    /*设置允许连接的最大客户端数*/
    if(listen(sockfd,5) == -1){
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);
    }
    while(1){
        /*服务器阻塞，直到客户端程序建立连接*/
        sin_size = sizeof(struct sockaddr_in);
        if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size)) == -1){
            fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
            exit(1);
        }
        //将网络地址转换成字符串
        fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
        if((nbytes = read(new_fd,buffer,1024)) == -1){
            fprintf(stderr,"Read Error:%s\n",strerror(errno));
            exit(1);
        }
        buffer[nbytes] = '\0';//添加终止符
        printf("Server received %s\n",buffer);
        /*这个通讯已经结束*/
        close(new_fd);
        /* 循环下一个 */
    }
    /* 结束通讯 */
    close(sockfd);
    exit(0);
}

