#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int clisocket,port,k=3;
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
    getchar();
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
    printf("----Enter exit to Stop chat----");
    char buf[4096];
    while(1){
        bzero(buf, 4096);
        printf("\nEnter the message:");
        fgets(buf, sizeof(buf), stdin);
        write(clisocket,buf,sizeof(buf));
        if(strncmp(buf,"exit",4)==0){
            printf("----CHAT CLOSED BY CLIENT-----");
            break;
        }
        printf("\nMessage Send");
        printf("\n----------REPLY FROM SERVER-------\n");
        read(clisocket,buf,sizeof(buf));
        if(strncmp(buf,"exit",4)==0){
            printf("----CHAT CLOSED BY SERVER-----");
            break;
        }
        printf("\nMessage is:%s",buf);
        printf("\n--------------------------------------\n");
    }
    close(clisocket);
}
