#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>

#define INET_ADDRSTRLEN 16


int main(int argc,char *argv[])
{
	/*
	  *
	  *argc ---- 指示程序启动时命令行参数的个数
	  *
	  *argv ---- 则包含具体的参数字符串
	*/
	//预备工作：检查参数是否正确
	if (argc !=2)
	{
		printf("请输入正确的参数\n如：./server 5005\n\n");
		return -1;//非成功结束
	}
	//第一步：创建插座
	/*
	  *插座特点
		1.系统不自动分配端口
		2.初始化插座是主动的，需要手动调节成被动（监听）模式
	  *功能：创建一个用于网络通信的I/O描述符（插座）
	  *int socket(int family, int type, int protocol)
	   *int socket(协议族    ,插座类型,协议类别)
	*/
	int serverfd;	//服务器的插座
	if((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		return -1;
	}				//插座创建成功

	//第二步 把服务端用于通信的地址和端口绑定到socket上
	/*
	  *
	  *int bind(int sockfd,const struct sockaddr *myaddr,socklen_t addrlen)
	  *int bind(socket插座,指向特定于协议的地址结构指针,该地址结构的长度)
	  *功能 将本地协议地址与服务器插座文件符(serverfd)绑定

	  *sockaddr_in ：在IPv4因特网域(AF_INET)中,套接字地址结构用sockaddr_in命名
	*/

	struct sockaddr_in servaddr;	//定义服务端地址信息的数据结构
	memset(&servaddr,0,sizeof(servaddr));//初始化servaddr
	servaddr.sin_family = AF_INET;
	//协议族，在socket编程中只能是AF_INET
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//任意ip地址
	//inet_addr("192.168.190.134"); // 指定ip地址
	servaddr.sin_port = htons(atoi(argv[1]));//指定通信端口

	if(bind(serverfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
	{
		perror("bind");
		close(serverfd);
		return -1;
	}								//开始绑定

	//第3步：把socket设置为监听模式

	/*
	  *int listen(int sockfd, int backlog)
	  *int listen(socket监听插座，连接队列的长度)
	  *功能 将插座由主动修改为被动
	  *	   使os为该插座设置一个连接队列，用来记录所有连接到该插座的连接
	*/
	if(listen(serverfd,10) != 0)
	{
		perror("listen");
		close(serverfd);
		return -1;
	}

	//第4步：接受客户端的连接

	/*
	  *int accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen);
	  *int accept(socket监听插座,用于存放客户端插座地址结构,插座地址结构体长度);
	  *功能 从已连接队列中取出一个已经建立的连接，如果没有任何连接可用，则进入睡眠等待
	  *accept函数返回的是一个已连接套接字，这个套接字代表当前这个连接
	*/
	
	int clientfd;		//声明客户端的插座
	int socklen = sizeof(struct sockaddr_in);  //获得插座地址结构struct sockaddr_in的大小
	struct sockaddr_in clientaddr;		//声明客户端地址数据结构
	//接受连接
	clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,(socklen_t*)&socklen);
	printf("客户端（%s）已连接。\n",inet_ntoa(clientaddr.sin_addr));

	//第5步：与客户端通信，接收客户端发过来的报文后，回复ok。

	/*
	  *ssize_t recv(int sockfd, void *buf,size_t nbytes, int flags);
	  *ssize_t recv(客户端插座, 指向接收网络数据的缓冲区,
								接收缓冲区的大小(以字节为单位), 套接字标志(常为0));
	  *返回值：成功接收到的数据字节数


	  *ssize_t send(int sockfd, const void* buf, size_t nbytes, int flags);
	  *ssize_t send(服务端插座, 待发送数据缓存区的地址, 
								发送缓存区大小(以字节为单位), 套接字标志(常为0));
	  *功能：用于发送数据 注意：不能用TCP协议发送0长度的数据包
	  *返回值：成功发送的字节数
	*/
	char buffer[1024];		//声明缓冲区
	while (1)
	{
		int iret;
		memset(buffer,0,sizeof(buffer));//初始化缓冲区
		//接收客户端的请求报文
		if((iret = recv(clientfd,buffer,sizeof(buffer),0)) <= 0)
		{
			printf("iret=%d\n",iret);
			break;
		}
		printf("接受：%s\n",buffer);//显示接受到的消息

		//向客户端发送响应结果
		if ( (iret=send(clientfd,buffer,strlen(buffer),0))<=0) 
		{
			perror("send");
			break;
		}
		printf("发送：%s\n",buffer);//显示发送出去的消息
	}


	// 第6步：关闭socket，释放资源
	close(serverfd);
	close(clientfd);
	
}
