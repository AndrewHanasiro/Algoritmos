#include <stdio.h>
#include <stdlib.h>
#define MAX 11
#define MOLDURA -1

void inicializa_marca(int campo[][MAX], char marca[][MAX]){
    int lin=0, col=0;
    for(lin=0;lin<11;lin++){
        for(col=0;col<11;col++){
            campo[col][lin]=0;
            campo[0][lin]=MOLDURA;
            campo[col][0]=MOLDURA;
            campo[10][lin]=MOLDURA;
            campo[col][10]=MOLDURA;
        }
    }
}
void inicializa_campo(int campo[][MAX]){
    FILE *entrada;
    int col, lin, num, quant_num,i;
    entrada=fopen("sudoku.txt","r");
    if(entrada==NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }
    fscanf(entrada,"%d",&quant_num);
    printf("\nCampo com %d numeros\n\n",quant_num);
    for(i=0;i<quant_num;i++){
        fscanf(entrada, "%d %d %d", &col, &lin, &num);
        campo[col][lin]=num;
    }
}
void imprime(int campo[][MAX]){
    int lin, col;
    for(lin=1;lin<MAX-1;lin++){
        printf("\n");
        for(col=1;col<MAX-1;col++){
            if(campo[col][lin]==0)printf("   ");
            else printf(" %d ",campo[col][lin]);
            if(col==3) printf(" | ");
            if(col==6) printf(" | ");
        }
        if(lin==3) printf("\n ---------+-----------+---------");
        if(lin==6) printf("\n ---------+-----------+---------");
    }
    printf("\n\n");
}
void processa_campo(int campo[][MAX]){
    imprime(campo);
}
int main(){
    int campo[MAX][MAX];
    inicializa_marca(campo);
    inicializa_campo(campo);
    processa_campo(campo);
    imprime(campo);
    return 0;
}
