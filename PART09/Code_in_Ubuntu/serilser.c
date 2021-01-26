#include<pthread.h>
#include<fcntl.h>
#include<netinet/in.h> 
#include<sys/types.h>   
#include<sys/socket.h> 
#include<sys/stat.h> 
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>    
#include<stdlib.h>  
#include<string.h>     
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

#define LENGTH_OF_LISTEN_QUEUE 20   
#define BUFFER_SIZE 1024   
#define SHMBUFSZ 2048
#define FILE_NAME_MAX_SIZE 512   
#define ClientMAX 10

typedef struct clientinfo 
{
    char name[10];
    int clientfd;
    //void *sock_fd;
}clientinfo;
clientinfo infolist[ClientMAX];//用户列表（数组）
pthread_mutex_t mutex;//互斥锁

//线程拷贝一份用户列表到自己
void freshlist(clientinfo*backup)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < ClientMAX; i++)
        backup[i]=infolist[i];
    pthread_mutex_unlock(&mutex);
    for(int i=0;i<ClientMAX;i++)
        printf("clientfd:%d,clientname:%s\n",backup[i].clientfd,backup[i].name);
}
//线程把用户列表发送出去
void sendlist(clientinfo* list,int sock_fd)
{
    freshlist(list);
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < ClientMAX; i++)
    {
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"%d",i);
        strcat(buffer,list[i].name);
        if (send(sock_fd,buffer,sizeof(buffer),0)<=0)
        {
            perror("User List send fail");
            continue;
        }
    }
}
//线程将用户注册进用户列表
void registe(char*buffer,int sock_fd)
{
    pthread_mutex_lock(&mutex);
    int j=1;
    for (int i = 0; i < ClientMAX; i++)
    {
        if(infolist[i].clientfd!=99)
        {
            infolist[i].clientfd=sock_fd;
            // do
            // {
            //     infolist[i].name[j-1]=buffer[j];
            //     j++;
            // } while (buffer[j]=='\0');
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}
//线程检查用户是否在用户列表里面
int check(clientinfo*backup,int sock_fd)
{
    for(int i=0;i<ClientMAX;i++)
        if(sock_fd==backup[i].clientfd)
            return 0;
    return 1;
}
//线程将自己对应的用户从列表里删除
void clean(int sock_fd)
{
    pthread_mutex_lock(&mutex);
    int j=1;
    for (int i = 0; i < ClientMAX; i++)
    {
        if(infolist[i].clientfd==sock_fd)
        {
            infolist[i].clientfd=99;
            memset(&infolist[i].name,0,sizeof(infolist[i].name));
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void servant(void * sock_fd)
{
    //init
    int master_fd = *((int *)sock_fd);
    char buffer[BUFFER_SIZE];
    //检查进程号，线程号和文件描述副
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("pid: %u, tid: %u (0x%x)\n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
    printf("The masterfd=%d\n",master_fd);
    //创立用户列表的备份
    clientinfo backup[ClientMAX];

    int masternum;//保存发送目标的编号
    int temp;//临时存储
    freshlist(backup);
    while(1)
    {
        memset(buffer,9,sizeof(buffer));//清空缓存
        if (recv(master_fd, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Server Recieve Data Failed:");
            continue;
        }
        printf("%s\n",buffer);
        /*如果用户不再列表里面，不与理会*/
        // if(check(backup,master_fd))
        //    continue;
        /*用户请求用户列表*/
        if (buffer[0]=='2')
        {
            printf("Client请求用户列表\n");
            sendlist(backup,master_fd);
        }
        /*用户退出聊天*/
        if(buffer[0]=='4')
        {
            printf("pid: %u, tid: %u (0x%x)out!\n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
            break;
        }
        /*用户注册用户列表*/
        // if(buffer[0]=='3')
        // {
        //     printf("Client register\n");
        //     pthread_mutex_lock(&mutex);
        //     int j=1;
        //     for (int i = 0; i < ClientMAX; i++)
        //     {
        //         if(infolist[i].clientfd!=99)
        //         {
        //             infolist[i].clientfd=master_fd;
        //             do
        //             {
        //                 infolist[i].name[j-1]=buffer[j];
        //                 j++;
        //             } while (buffer[j]=='\0');
        //             break;
        //         }
        //     }
        //     pthread_mutex_unlock(&mutex);
        //     //registe(buffer,master_fd);
        // }
        /*服务器转发信息*/
        if(buffer[0]=='0'||buffer[0]=='1')
        {
            temp=(int)buffer[1];
            // buffer[1]=master_fd;
            if (send(temp,buffer,sizeof(buffer),0)<=0)
                perror("message send");
        }
    }
    return;
}

int main(int argc,char *argv[])   
{
	int serverfd;
    int clientfd;
    int iret;
    pthread_t serverid;

    /*sockaddr_in详解*/
    //sockaddr_in 是internet环境下套接字的地址形式
    // struct sockaddr_in
    // {
    //    short sin_family;/*Address family一般来说AF_INET（地址族）PF_INET（协议族）*/
    //    unsigned short sin_port;/*Port number(必须要采用网络数据格式,普通数字可以用htons()函数转换成网络数据格式的数字)*/
    //    struct in_addr sin_addr;/*IP address in network byte order（Internet address）*/
    //    unsigned char sin_zero[8];/*Same size as struct sockaddr没有实际意义,只是为了　跟SOCKADDR结构在内存中对齐*/
    // };
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    //网络初始化
    int socklen = sizeof(struct sockaddr_in);
    /*socket()*/
    // 我们使用系统调用socket()来获得文件描述符：
    // #include<sys/types.h>
    // #include<sys/socket.h>
    // int socket(int domain,int type,int protocol);
    // 第一个参数domain设置为“AF_INET”。
    // 第二个参数是套接口的类型：SOCK_STREAM或
    // SOCK_DGRAM。第三个参数设置为0。
    // 系统调用socket()只返回一个套接口描述符，如果出错，则返回-1。
	if((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		return -1;
	}
    /*memset()*/
    // 这个函数在socket中多用于清空数组.如:原型是memset(buffer, 0, sizeof(buffer))
    // Memset 用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为‘ ’或‘/0’；
	memset(&servaddr,0,sizeof(servaddr));

    //TCP set
	servaddr.sin_family = AF_INET;
    /*htonl()*/
    //htonl就是把本机字节顺序转化为网络字节顺序
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*htons()*/
    //将主机的无符号短整形数转换成网络字节顺序。
	servaddr.sin_port = htons(atoi(argv[1]));

    /*TCP bind*/
    //bind()用来设置给参数sockfd的socket一个名称。此名称由参数my_addr指向一sockaddr结构，对于不同的socket domain定义了一个通用的数据结构
    //绑定一个端口
	if(bind(serverfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
	{
		perror("bind");
		close(serverfd);
		return -1;
	}

    /*TCP listen*/
    //监听来自客户端的tcp socket的连接请求
	if(listen(serverfd,10) != 0)
	{
		perror("listen");
		close(serverfd);
		return -1;
	}

    //localinit
    //clientlist init
    //初始化用户列表（数组）
    for (int i = 0; i < ClientMAX; i++)
    {
        infolist[i].clientfd=99;
        memset(&infolist[i].name,0,sizeof(infolist[i].name));
    }
    //实验用户列表
    char testname[]="testname1";
    infolist[0].clientfd=1;
    strcpy(infolist[0].name,testname);

    //初始化线程互斥锁
    pthread_mutex_init(&mutex, NULL);

	while (1)
	{
        //建立链接
        socklen_t clientaddrlength = sizeof(clientaddr);   
        clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,(socklen_t*)&clientaddrlength);
        if(clientfd < 0)   
        {   
            perror("Server Accept Failed");   
            break;   
        }
        else
        {            
            printf("Client（%s）has connected。Opening a new thread\n",inet_ntoa(clientaddr.sin_addr));
        }
        registe(infolist,clientfd);
        //连接已经建立，为每一个用户建立线程        
        if (pthread_create(&serverid, NULL, (void *)(&servant), (void *)(&clientfd)))
        {
            fprintf(stderr, "pthread_create error!\n");
        }
        //线程分离
        pthread_detach(serverid);
    }
    //摧毁线程互斥锁
    pthread_mutex_destroy(&mutex);
    //关闭套接子
	close(serverfd);
}