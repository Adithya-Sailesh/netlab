//first run server.c
//gcc Server.c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int clisocket,port;
    int k=5,m=1;
    char buffer[200];
    struct sockaddr_in seraddr;
    clisocket=socket(AF_INET,SOCK_STREAM,0);
    if(clisocket<0){
        printf("error 1");
        exit(0);
    }
    printf("Enter the port:");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    printf("\nTrying to connect to the server.\n");
    if(connect(clisocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("\nConnection Failed");
        exit(EXIT_FAILURE);
    }
    printf("\nConnection Success!!!!!!!!!!!!\n");
    while(k!=0){
        if(m<=5){
            printf("\nSending Frame %d",m);
        }
        //Sending Frame(Error Happens Here)
        if(m%2==0){
            strcpy(buffer,"frame");
        }
        else{
            printf("\nFrame %d Lost",m);
            strcpy(buffer,"error");
            for(int p=1;p<=3;p++){
                printf("\nWaiting for %d seconds\n", p);
                sleep(1);
            }
            printf("\nRetransmitting Frame %d",m);
            strcpy(buffer,"frame");
        }
        int y=send(clisocket,buffer,sizeof(buffer),0);
        if(y==-1){
            printf("\n Error3 ----");
            exit(0);
        }
        else{
            printf("\nSend Packet%d",m);
        }
        //Reciving Ack
        int z=recv(clisocket,buffer,sizeof(buffer),0);
        if(z==-1){
            printf("\n Error in recieving----");
            exit(0);
        }
        if (strncmp(buffer, "ack", 3) == 0) {
            printf("\nAck received for %d\n",m);
        } else {
            printf("\n-----Ack not received for %d----\n",m);
        }
        k--;
        m++;
    }
}
