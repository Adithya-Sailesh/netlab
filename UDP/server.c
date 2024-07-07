// First Run gcc server.c
//             ./a.out
// Second Run gcc client.c
//             ./a.out
// Third Enter port address in server.c first
// Fourth Enter port address in client.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int sersocket,port;
    struct sockaddr_in seraddr,cliaddr;
    char msg[200];
    socklen_t len;
    sersocket=socket(AF_INET,SOCK_DGRAM,0);
    if(sersocket<0){
        printf("Error!");
        exit(EXIT_FAILURE);
    }
    //bind Socket
    printf("\nEnter the Port:");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("Error Binding");
        exit(EXIT_FAILURE);
    }
    printf("\nWaiting For client connection");
    bzero((char*)&cliaddr,sizeof(cliaddr));
    len=sizeof(cliaddr);
    printf("\nRecieving msg From cient");
    recvfrom(sersocket,msg,sizeof(msg),0,(struct sockaddr*)&cliaddr,&len);
    printf("-\n------------------MSG FROM CLIENT----------------\n");
    printf("%s",msg);
    printf("\n---------------------------------------------------\n");
    printf("Sending msg to client\n");
    sendto(sersocket,"Helllo this is server msg",sizeof("Helllo this is server msg"),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    printf("--MESSAGE SENT--\n");
    close(sersocket);


}
