#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<signal.h>
#include<sys/wait.h>
#include<pthread.h>
#include<ctype.h>//其中定义的有toupper函数
#include<unistd.h>//这里定义的有read函数
//线程执行函数负责读写
void *thr_fn(void *arg){
    long size,j;
    char recv_buf[1024];
    int *parg = (int *)arg;
    int new_fd = *parg;
    printf("new_fd=%d\n",new_fd);
    while((size = read(new_fd,recv_buf,1024)) > 0){
        if(recv_buf[0] == '@') break;
        printf("Message from client(%ld):%s\n",size,recv_buf);
        for(j=0;j<size;j++){
            recv_buf[j] = toupper(recv_buf[j]);
        }
        write(new_fd,recv_buf,size);
    }
    close(new_fd);
    return 0;
}
int main(int argc,char *argv[]){
    socklen_t clt_addr_len;
    int listen_fd;
    int com_fd;
    int ret;
    int i;
    static char recv_buff[1024];
    //int len;
    unsigned int len;
    int port;
    pthread_t tid;
    
    struct sockaddr_in clt_addr;
    struct sockaddr_in srv_addr;
    //服务器端运行时要给出端口信息，该端口为监听端口
    if(argc!=2){
        printf("Usage:%s port\n",argv[0]);
        return 1;
    }
    //获得输入的端口
    port = atoi(argv[1]);
    
    //创建套接字用于服务器的监听
    listen_fd = socket(PF_INET,SOCK_STREAM,0);
    if(listen_fd < 0){
        perror("cannot create listening socket");
        return 1;
    }
    //填充关于服务器的套接字信息
    memset(&srv_addr,0,sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(port);
    //将服务器和套接字绑定
    ret = bind(listen_fd,(struct sockaddr *)&srv_addr,sizeof(srv_addr));
    if(ret == -1){
        perror("cannot bind server socket");
        close(listen_fd);
        return 1;
    }
    //监听指定端口，连接5个客户端
    ret = listen(listen_fd,5);
    if(ret == -1){
        perror("cannot listen the client connect request");
        close(listen_fd);
        return 1;
    }
    //对每个连接来的客户端创建一个线程，单独与其进行通信
    /*首先调用read函数读取客户端发送来的信息，将其转换成大写后发送回客户端
     当输入“@”时，程序退出*/
    while(1){
        len = sizeof(clt_addr);
        com_fd = accept(listen_fd,(struct sockaddr *)&clt_addr,&len);
        if(com_fd < 0){
            if(errno == EINTR){
                continue;
            }else{
                perror("cannot accept client connect request");
                close(listen_fd);
                return 1;
            }
        }
        printf("com_fd=%d\n",com_fd);//打印建立连接的客户端产生的套接字
        if((pthread_create(&tid,NULL,thr_fn,&com_fd)) == -1){
            perror("pthread_create error");
            close(listen_fd);
            close(com_fd);
            return 1;
        }
    }
    return 0;
}

