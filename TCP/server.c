
// First Run gcc server.c
//             ./a.out
// Second Run gcc client.c
//             ./a.out
// Third Enter port address in server.c first
// Fourth Enter port address in client.c

#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include <string.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
    int sersocket,clisocket,port;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t length;
    char msg[50];
    //Creating Server Socket
    sersocket=socket(AF_INET,SOCK_STREAM,0);
    if(sersocket<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    //Bind Socket
    printf("Enter the port value:");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    //listen
    bzero((char*)&cliaddr,sizeof(cliaddr));
    length=sizeof(cliaddr);
    if(listen(sersocket,5)<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\nWaiting for client connection...\n");
    //accpet connection
    clisocket=accept(sersocket,(struct sockaddr*)&cliaddr,&length);
    if(clisocket<0){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\nClient Connected Scussfully");
    //Read and Write
    printf("\nReading Message !!!!!!!!!");
    read(clisocket,msg,sizeof(msg));
    printf("\n------------------------------------");
    printf("\nMessage From client is:%s",msg);
    printf("\n------------------------------------\n");
    write(clisocket,"Hello I am msg from server",sizeof("Hello I am msg from server"));
    close(sersocket);
    close(clisocket);
}
