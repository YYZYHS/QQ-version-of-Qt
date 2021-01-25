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

void freshlist(clientinfo*backup)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < ClientMAX; i++)
       backup[i]=infolist[i];
    pthread_mutex_unlock(&mutex);
}

void sendlist(clientinfo* list,int sock_fd)
{
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < ClientMAX; i++)
    {
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"%d",i);
        strcat(buffer,list[i].name);
        if (send(sock_fd,buffer,sizeof(buffer),0))
        {
            perror("User List send fail");
            continue;
        }
    }
}

void registe(char*buffer,int sock_fd)
{
    pthread_mutex_lock(&mutex);
    int j=1;
    for (int i = 0; i < ClientMAX; i++)
    {
        if(infolist[i].clientfd!=99)
        {
            infolist[i].clientfd=sock_fd;
            do
            {
                infolist[i].name[j-1]=buffer[j];
                j++;
            } while (buffer[j]=='\0');
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int check(clientinfo*backup,int sock_fd)
{
    for(int i=0;i<ClientMAX;i++)
        if(sock_fd==backup[i].clientfd)
            return 0;
    return 1;
}

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
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("pid: %u, tid: %u (0x%x)\n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
    printf("The masterfd=%d\n",master_fd);
    clientinfo backup[ClientMAX];
    int masternum;
    int temp;
    freshlist(backup);
    while(1)
    {
        memset(buffer,9,sizeof(buffer));
        if (recv(master_fd, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Server Recieve Data Failed:");
            continue;
        }
        printf("%s\n",buffer);
        if(check(backup,master_fd))
            continue;
        if (buffer[0]=='2')
        {
            printf("Client请求用户列表\n");
            sendlist(backup,master_fd);
        }
        if(buffer[0]=='4')
        {
            printf("pid: %u, tid: %u (0x%x)out!\n", (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
            clean(master_fd);
            close(master_fd);
            pthread_exit(NULL);
            break;
        }
        if(buffer[0]=='3')
        {
            printf("Client register\n");
            registe(buffer,master_fd);
        }
        if(buffer[0]=='0'||buffer[0]=='1')
        {
            temp=(int)buffer[1];
            buffer[1]=master_fd;
            if (send(backup[temp].clientfd,buffer,sizeof(buffer),0))
                perror("User List send fail");
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
    //init pthread mutex
    pthread_mutex_init(&mutex, NULL);

	while (1)
	{
        //get connection
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
        if (pthread_create(&serverid, NULL, (void *)(&servant), (void *)(&clientfd)))
        {
            fprintf(stderr, "pthread_create error!\n");
        }
        pthread_detach(serverid);
        char* rev = NULL;
    }
    pthread_mutex_destroy(&mutex);
	close(serverfd);

}