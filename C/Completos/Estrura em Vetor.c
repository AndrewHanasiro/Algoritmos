#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int info;
}Info;
Info *cria(int quant){
    Info *temp;
    int i;
    temp=(Info*)malloc(quant*sizeof(Info));
    for(i=0;i<quant;i++){
        temp[i].info=i;
    }
    return temp;
}
void imprime(Info *F,int quant){
    int i;
    for(i=0;i<quant;i++){
        printf("%d",F[i].info);
    }
}
int main(){
    Info *F;
    int quant;
    printf("quantidade de estruturas:");
    scanf("%d",&quant);
    F=cria(quant);
    imprime(F,quant);
    return 0;
}
