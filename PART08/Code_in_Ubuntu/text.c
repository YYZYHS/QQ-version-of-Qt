#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define BUFLEN 1000
#define SEND_PORT 4000
#define RECV_PORT 4001
#define LISTEN_NUM 10

///set an connection, sockfd is the fd of socket, confd is the fd of one connetction
void set_conn(int *sockfd, int *confd, int port)
{
    struct sockaddr_in s_addr, c_addr;
    socklen_t len;
    /*建立socket*/
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(errno);
    }

    //fill the address
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    ///set the port as a reuseable port
    int opt = 1;
    setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ///bind
    if ((bind(*sockfd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr))) == -1)
    {
        perror("bind");
        exit(errno);
    }

    ///listen
    if (listen(*sockfd, LISTEN_NUM) == -1)
    {
        perror("listen");
        exit(errno);
    }

    ///accept
    len = sizeof(struct sockaddr);
    if ((*confd = accept(*sockfd, (struct sockaddr *)&c_addr, &len)) == -1)
    {
        perror("accept");
        exit(errno);
    }
}

///发送线程
void *th_send(void *arg)
{
    int sockfd, confd;
    char buf[BUFLEN];
    set_conn(&sockfd, &confd, SEND_PORT);
    while (1)
    {
        fgets(buf, BUFLEN, stdin);
        if (!strcmp(buf, "exit"))
        {
            printf("exiting\n");
            close(sockfd);
            close(confd);
            return 0;
        }
        if (send(confd, buf, strlen(buf), 0) == -1)
        {
            perror("消息发送失败");
            exit(errno);
        }
    }
}

///接收线程
void *th_recv(void *arg)
{
    int sockfd, confd;
    char buf[BUFLEN];
    set_conn(&sockfd, &confd, RECV_PORT);
    while (1)
    {
        memset(buf, 0, BUFLEN);
        switch (recv(confd, buf, BUFLEN, 0))
        {
        case -1: ///error occurred
            perror("接受消息失败");
            exit(errno);
        case 0: ///peer  has  performed  an orderly shutdown.
            printf("客户端退出了，聊天终止");
            return;
        default: /// receive succssed
            printf("client:%s", buf);
        }
    }
}

int main()
{
    pthread_t tid_send, tid_recv;

    pthread_create(&tid_send, NULL, th_send, NULL); ///发送线程
    pthread_create(&tid_recv, NULL, th_recv, NULL); ///接收线程

    pthread_join(tid_send, NULL);
    pthread_join(tid_recv, NULL);
    return 0;
}