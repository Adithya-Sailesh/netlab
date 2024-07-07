// First Run gcc server.c
//             ./a.out
// Second Run gcc client.c
//             ./a.out
// Third Enter port address in server.c first
// Fourth Enter port address in client.c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int clisocket,port;
    struct sockaddr_in servaddr;
    char msg[50];
    //1) create client scocket
    clisocket=socket(AF_INET,SOCK_STREAM,0);
    if(clisocket<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    //2) Connect
    printf("\nEnter the Port Number:");
    scanf("%d",&port);
    bzero((char*)&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    printf("\nTrying to connect to the server.\n");
    if(connect(clisocket,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("\nConnection Failed");
        exit(EXIT_FAILURE);
    }
    printf("\nConnection Success!!!!!!!!!!!!\n");
    printf("\nMsg Send to Server\n");
    write(clisocket,"Message From Client",sizeof("Message From Client"));
    read(clisocket,msg,sizeof(msg));
    printf("\n---------------------------------\n");
    printf("Message from server :%s",msg);
    printf("\n---------------------------------\n");
    close(clisocket);
}
