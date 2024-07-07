//server.c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define Max 4096
int main(){
    FILE *f1;
    int sersocket,clisocket,port;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t len;
    char buffer[Max],line[Max];
    sersocket=socket(AF_INET,SOCK_STREAM,0);
    if(sersocket<0){
        printf("Error in Socket Creation");
        exit(0);
    }
    bzero((char*)&seraddr,sizeof(seraddr));
    bzero((char*)&cliaddr,sizeof(cliaddr));
    printf("\nEnter the port number:");
    scanf("%d",&port);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    
    len=sizeof(cliaddr);
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("Error In Binding");
        exit(0);
    }
    printf("\nListening....");
    if(listen(sersocket,5)<0){
        printf("\nError in Listening");
        exit(0);
    }
    clisocket=accept(sersocket,(struct sockaddr*)&cliaddr,&len);
    if(clisocket<0){
        printf("\nError in Clisocket");
        exit(0);
    }
    printf("\n-------Connection Successfull------");
    int y=read(clisocket,buffer,Max);
    printf("\nFile Name is:%s",buffer);
    f1=fopen(buffer,"r");
    while((fgets(line,sizeof(line), f1))!=NULL){
        write(clisocket,line,sizeof(line));
        printf("\n");
    }
    fclose(f1);
    printf("\n---------File Transferred---------------");
}
