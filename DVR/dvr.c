#include<stdio.h>
#include<stdlib.h>
int costmatrix[20][20],n;
struct router{
    int adjNodes[20];
    int distance[20];

}node[10];
void readmatrix(){
    printf("\nEnter the number of nodes=");
    scanf("%d",&n);
    printf("\nEnterThe Cost Matrix: ");
    for(int i=0;i<n;i++){
        costmatrix[i][i]=0;
        for(int j=0;j<n;j++){
            scanf("%d",&costmatrix[i][j]);
            node[i].distance[j]=costmatrix[i][j];
            node[i].adjNodes[j]=j;
        }
    }
}
void calculate(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(node[i].distance[j]>(costmatrix[i][k]+node[k].distance[j])){
                        node[i].distance[j]=node[k].distance[j]+node[i].distance[k];
                        node[i].adjNodes[j]=k;
                }
            }
        }
    }
}
void display(){
    for(int i=0;i<n;i++){
         printf("\nRouter %d\n", i + 1);
        for(int j=0;j<n;j++){
            printf("Node %d via %d Disatance=%d",j+1,node[i].adjNodes[j]+1,node[i].distance[j]);
            printf("\n");
        }
        printf("\n");
    }
}
int main(){
    readmatrix();
    calculate();
    display();
}
