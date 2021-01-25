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
clientinfo infolist[ClientMAX];//Clientlist
pthread_mutex_t mutex;

void servant(void * sock_fd)
{
    //init
    int master_fd = *((int *)sock_fd);
    char buffer[BUFFER_SIZE];
    clientinfo Clientbuf[ClientMAX];
    int masternum;
    int temp;
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < ClientMAX; i++)
        Clientbuf[i]=infolist[i];
    pthread_mutex_unlock(&mutex);
    while(1)
    {
        memset(buffer,9,sizeof(buffer));
        if (recv(master_fd, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Server Recieve Data Failed:");
            break;
        }
        //idenfy message
        //请求用户列表
        if (buffer[0]=='2')
        {
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < ClientMAX; i++)
                Clientbuf[i]=infolist[i];
            pthread_mutex_unlock(&mutex);
            for (int i = 0; i < ClientMAX; i++)
            {
                memset(buffer,9,sizeof(buffer));
                buffer[0]='2';
                buffer[1]=(char)i;
                strcat(buffer,Clientbuf[i].name);
                if (send(master_fd,buffer,sizeof(buffer),0))
                    perror("User List send fail");
            }
        }
        //注册用户列表
        if (buffer[0]=='3')
        {
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < ClientMAX; i++)
            {
                if (infolist[i].clientfd=99)
                {
                    infolist[i].clientfd=master_fd;
                    for (int j = 1; j < strlen(buffer); j++)
                    {
                        infolist[i].name[j-1]=buffer[j];
                    } 
                    masternum=i;                   
                    break;
                }
            }
            pthread_mutex_unlock(&mutex);
        }
        //转发
        if(buffer[0]=='0'||buffer[0]=='1')
        {
            temp=buffer[1];
            buffer[1]=master_fd;
            if (send(Clientbuf[temp].clientfd,buffer,sizeof(buffer),0))
                perror("User List send fail");
        }
        //退出
        if(buffer[0]=='4')
        {
            pthread_mutex_lock(&mutex);
                infolist[masternum].clientfd=99;
                memset(infolist[masternum].name,9,sizeof(infolist[masternum].name));
            pthread_mutex_unlock(&mutex);
            close(master_fd);
            pthread_exit(NULL);   //terminate calling thread!
        }
    } 
}


int main(int argc,char *argv[])   
{
    int logfd;
	int serverfd;
    int clientfd;
    int iret;
    int shmid;
	char *shmadd;
    char wrbuf[]=" connected.\n";
    char buffer[1024];
    key_t key;
    pthread_t serverid;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    //netinit
    int socklen = sizeof(struct sockaddr_in);
	if((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		return -1;
	}
	memset(&servaddr,0,sizeof(servaddr));

    //TCP set
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

    //TCP bind
	if(bind(serverfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
	{
		perror("bind");
		close(serverfd);
		return -1;
	}

    //TCP listen
	if(listen(serverfd,10) != 0)
	{
		perror("listen");
		close(serverfd);
		return -1;
	}

    //localinit
    //clientlist init
    for (int i = 0; i < ClientMAX; i++)
    {
        infolist[i].clientfd=99;
        memset(&infolist[i].name,0,sizeof(infolist[i].name));
    }
    //open logfile
    // if(logfd=open("./log.txt",O_RDWR|O_CREAT|O_APPEND,0777))
    // {
    //     printf("Fail to open the logfile!\n");
    //     return 1;
    // }
    //init pthread mutex
    pthread_mutex_init(&mutex, NULL);

	while (1)
	{
        //get connection
        socklen_t clientaddrlength = sizeof(clientaddr);   
        memset(buffer,0,sizeof(buffer));
        clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,(socklen_t*)&clientaddrlength);
        if(clientfd < 0)   
        {   
            perror("Server Accept Failed");   
            break;   
        }
        else
        {
            //write connection to the log
            printf("Client（%s）has connected。Opening a new thread\n",inet_ntoa(clientaddr.sin_addr));
            strcpy(buffer,inet_ntoa(clientaddr.sin_addr));
            strcat(buffer,wrbuf);
            write(logfd,buffer,strlen(buffer));
        }
    
        if (pthread_create(&serverid, NULL, (void *)(&servant), (void *)(&clientfd)) == -1)
        {
            fprintf(stderr, "pthread_create error!\n");
            break;
        }
    }
    pthread_mutex_destroy(&mutex);
	close(serverfd);
    close(logfd);
}