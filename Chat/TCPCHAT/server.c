#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int sersocket,clisocket,port;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t len;
    char msg[4096];
    char buff[4096];
    sersocket=socket(AF_INET,SOCK_STREAM,0);
    if(sersocket<0){
        printf("\nError In socket Creation");
        exit(0);
    }
    printf("Enter The Port Number:");
    scanf("%d",&port);
    getchar();
    printf("\nListening.....");
    bzero((char*)&seraddr,sizeof(seraddr));
    bzero((char*)&cliaddr,sizeof(cliaddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("\nError In Binding");
        exit(0);
    }
    if(listen(sersocket,5)<0){
        printf("\nError In Binding");
        exit(0);
    }
    len=sizeof(cliaddr);
    clisocket=accept(sersocket,(struct sockaddr*)&cliaddr,&len);
    if(clisocket<0){
        printf("\nCannot Connect!!");
        exit(0);
    }
    printf("\n Connected to client");
    printf("\n Enter (exit) to Close Chat \n");
    while(1){
        printf("\nWaiting For Message....\n");
        read(clisocket,msg,sizeof(msg));
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Client!!!!!!!!!!!!!!!!\n");
            break;
        }
        printf("\n----------MESSAGE FROM CLIENT-------------\n");
        printf("%s",msg);
        printf("-------------------------------------------");
        printf("\nEnter the reply=");
        fgets(msg,sizeof(msg),stdin);
        write(clisocket,msg,sizeof(msg));
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Server!!!!!!!!!!!!!!!!\n");
            break;
        }

    }
    close(sersocket);
    close(clisocket);
}
