#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int sersocket,port;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t len;
    char msg[4096];
    sersocket=socket(AF_INET,SOCK_DGRAM,0);
    if(sersocket<0){
        printf("\nError In socket Creation");
        exit(0);
    }
    printf("Enter The Port Number:");
    scanf("%d",&port);
    getchar();
    printf("\nListening.....");
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("\nError In Binding");
        exit(0);
    }
    bzero((char*)&cliaddr,sizeof(cliaddr));
    len=sizeof(cliaddr);
    while (1)
    {   printf("\nWaiting For Message....\n");
        recvfrom(sersocket,msg,sizeof(msg),0,(struct sockaddr*)&cliaddr,&len);
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Client!!!!!!!!!!!!!!!!\n");
            break;
        }
        printf("\n----------MESSAGE FROM CLIENT-------------\n");
        printf("%s",msg);
        printf("-------------------------------------------");
        printf("\nEnter the reply=");
        fgets(msg,sizeof(msg),stdin);
        sendto(sersocket,msg,sizeof(msg),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Server!!!!!!!!!!!!!!!!\n");
            break;
        }
    }
    
}
