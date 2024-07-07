#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
void handle(int clisocket){
    int n;
    char buff[4096];
    while(n=read(clisocket,buff,sizeof(buff))!=0){
        printf("\n----------------------------------\n");
        printf("\nMessage from %d is:%s",clisocket,buff);
        printf("\n----------------------------------\n");
    }
    if(n<0){
        close(clisocket);
    }

    
}
int main(){
    int sersocket,clisocket,port;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t len;
    sersocket=socket(AF_INET,SOCK_STREAM,0);
    if(sersocket<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("Enter the port value:");
    scanf("%d",&port);
    getchar();
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    bzero((char*)&cliaddr,sizeof(cliaddr));
    if(listen(sersocket,5)<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\nWaiting for client connection...\n");
    while(1){
        len=sizeof(cliaddr);
        clisocket=accept(sersocket,(struct sockaddr*)&cliaddr,&len);
        if(clisocket<0){
            printf("Error");
            exit(EXIT_FAILURE);
        }
        printf("\nClient Connected Scussfully");
        if(fork()==0){
            close(sersocket);
            handle(clisocket);
            exit(0);
        }
        else{
            close(clisocket);
        }
    }
    
}
