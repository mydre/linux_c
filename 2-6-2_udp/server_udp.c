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
void udps_respon(int sockfd){
    struct sockaddr_in addr;
    unsigned int addrlen,n;
    char msg[MAX_MSG_SIZ];
    while(1){
        /*从网络上读，并写到网络上*/
        bzero(msg,sizeof(msg));//初始化，清零
        addrlen = sizeof(struct sockaddr);
        n = recvfrom(sockfd,msg,MAX_MSG_SIZ,0,(struct sockaddr*)&addr,&addrlen);//从客户端接受消息
        msg[n] = 0;//将收到的字符串尾端添加上字符串结束标志
        /*显示服务器已经收到了信息*/
        fprintf(stdout,"Server have received %s",msg);//显示消息
    }
}
int main(void){
    int sockfd;
    struct sockaddr_in addr;
    /*1  服务器端开始建立socket描述符*/
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        fprintf(stderr,"Socket Error:%s\n",strerror(errno));
        exit(1);
    }
    /*2  服务端填充。sockadddr结构*/
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);
    /*3  捆绑sockfd描述符*/
    if((bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))) < 0){
        fprintf(stderr,"Bind Error:%s\n",strerror(errno));
        exit(1);
    }
    /*4  */
    udps_respon(sockfd);//进行读写操作
    close(sockfd);
}

