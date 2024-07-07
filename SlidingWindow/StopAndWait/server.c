#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int sersocket,clisocket,port;
    int k=5,m=1;
    char buffer[200];
    struct sockaddr_in seraddr,cliaddr;
    socklen_t len;
    sersocket=socket(AF_INET,SOCK_STREAM,0);
    if(sersocket<0){
        printf("Error");
        exit(0);
    }
    printf("\nEnter the port:");
    scanf("%d",&port);
    bzero((char*)&seraddr,sizeof(seraddr));
    bzero((char*)&cliaddr,sizeof(cliaddr));
    len=sizeof(cliaddr);
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sersocket,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        printf("error");
        exit(0);
    }
    printf("\nListening!!!!!!!!!!!");
    if(listen(sersocket,5)<0){
        printf("error");
        exit(0);
    }
    printf("\nWaiting for client connection...\n");
    clisocket=accept(sersocket,(struct sockaddr*)&cliaddr,&len);
    if(clisocket<0){
        printf("error");
        exit(0);
    }
    printf("\nConnection Successfull");
    while(k!=0){
        //Receiving Frame (no Error)
        int y=recv(clisocket,buffer,sizeof(buffer),0);
        if(y==-1){
            printf("\nError!!!!!");
            exit(0);
        }
        if(strncmp(buffer,"frame",5)==0){
            printf("\n --Frame %d Recieved Successfully",m);
        }else{
            printf("\n --Frame %d not Recieved ",m);
        }
        //Sending Ack(Error  Happens Here)
        if(m%2==0){
            strcpy(buffer,"ack");
        }else{
            strcpy(buffer,"kca");
            printf("\nAck lost\n");
            for (int p = 1; p <= 3; p++) {
                printf("Waiting for %d seconds\n", p);
                sleep(1);
            }
            printf("\nRetransmitting Ack");
            strcpy(buffer,"ack");
        }
        printf("\nSending %d Ack \n",m);
        int z = send(clisocket, buffer, strlen(buffer), 0);
        k--;
        m++;
    }
}
