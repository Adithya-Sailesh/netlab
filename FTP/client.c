//client.c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define Max 4096
int main(){
    int clisocket,port;
    struct sockaddr_in seraddr;
    socklen_t len;
    char name[Max],lines[Max];
    clisocket=socket(AF_INET,SOCK_STREAM,0);
    if(clisocket<0){
         printf("Error in Socket Creation");
         exit(0);
    }
    printf("\nEnter the Port Number:");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    len=sizeof(seraddr);
    printf("\nTrying to connect to the server.\n");
    if(connect(clisocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
         printf("\nConnection Failed");
        exit(EXIT_FAILURE);
    }
    printf("\nConnection Success!!!!!!!!!!!!\n");
    printf("\nEnter the FileName:");
    scanf("%s",name);
    write(clisocket,name,Max);
    while ((read(clisocket,lines,Max))!=0)
    {
        printf("%s",lines);
    }
    
}
