//Client.c UDPCHAT
// First run server.c then ./a.out
// Second run client.c them ./a.out
// Give Port number has 4000(or any 4digitNumber)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int clisocket,port;
    struct sockaddr_in seraddr;
    socklen_t len;
    char msg[4096];
    clisocket=socket(AF_INET,SOCK_DGRAM,0);
    if(clisocket<0){
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
    len=sizeof(seraddr);
    while (1)
    {
        printf("\nEnter the Message=");
        fgets(msg,sizeof(msg),stdin);
        sendto(clisocket,msg,sizeof(msg),0,(struct sockaddr*)&seraddr,sizeof(seraddr));
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Client!!!!!!!!!!!!!!!!\n");
            break;
        }
        printf("\nWaiting For Reply....\n");
        recvfrom(clisocket,msg,sizeof(msg),0,(struct sockaddr*)&seraddr,&len);
        if(strncmp(msg,"exit",4)==0){
            printf("\n!!!!!!!!!Connection Closed By Server!!!!!!!!!!!!!!!!\n");
            break;
        }
        printf("\n----------MESSAGE FROM SERVER-------------\n");
        printf("%s",msg);
        printf("--------------------------------------------");
    }
    
    
}
