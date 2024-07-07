#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
int main(){
    int clisocket,port;
    struct sockaddr_in seraddr;
    socklen_t len;
    char msg[200];
    //Socket Creation
    clisocket=socket(AF_INET,SOCK_DGRAM,0);
    if(clisocket<0){
        printf("Error Socket Creation");
        exit(EXIT_FAILURE);
    }
    printf("Enter the port :");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    len=sizeof(seraddr);
    printf("\nConnecting to server");
    printf("\nSending message to client");
    sendto(clisocket,"Hi I Am Client Msg",sizeof("Hi I Am Client Msg"),0,(struct sockaddr*)&seraddr,sizeof(seraddr));
    printf("\nMessage Send");
    printf("\nRecieving Message");
    recvfrom(clisocket,msg,sizeof(msg),0,(struct sockaddr*)&seraddr,&len);
    printf("\n--------------------MSG FROM SERVER--------------------\n");
    printf("%s",msg);
    printf("\n----------------------------------------------------------");
    close(clisocket);
}
