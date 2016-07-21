#include <stdio.h>
#include <stdlib.h>
#define MAX 11
#define MOLDURA -1
#define ERRO -1
#define CONTINUA 0
#define VITORIA 1

int error=0;
int mov=0;
void inicializa_marca(int campo[][MAX], char marca[][MAX]){
    int lin=0, col=0;
    for(lin=0;lin<11;lin++){
        for(col=0;col<11;col++){
            campo[col][lin]=0;
            campo[0][lin]=MOLDURA;
            campo[col][0]=MOLDURA;
            campo[10][lin]=MOLDURA;
            campo[col][10]=MOLDURA;
            marca[col][lin]='L';
            campo[0][lin]='M';
            campo[col][0]='M';
            campo[10][lin]='M';
            campo[col][10]='M';
        }
    }
}
void inicializa_campo(int campo[][MAX], char marca[][MAX]){
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
        marca[col][lin]='P';
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
int procura_erro(int campo[][MAX], char marca[][MAX], int c, int l, int num){
    int col, col_class, lin, lin_class;
    for(col=1;col<MAX-1;col++){/*percorre a linha em busca doe numero repetido*/
        if(campo[col][l]==num){
            printf("\nErro: Esta linha ja possui o numero\n");
            error++;
            return ERRO;
        }
    }
    for(lin=1;lin<MAX-1;lin++){/*percorre a coluna em busca doe numero repetido*/
        if(campo[c][lin]==num){
            printf("\nErro: Esta coluna ja possui o numero\n");
            error++;
            return ERRO;
        }
    }
    if(marca[c][l]=='P'){
        printf("\nNao pode alterar o original");
        return ERRO;
    }
    /*classificando o quadrado das entradas*/
    if(c>3){
        if(c>6)col_class=8;
        else col_class=5;
    }
    else col_class=2;
    if(l>3){
        if(l>6) lin_class=8;
        else lin_class=5;
    }
    else lin_class=2;
    /*Vendo se no quadrado ja possui o numero*/
    for(lin=lin_class-1;lin<lin_class+1;lin++){
        for(col=col_class-1;col<col_class+1;col++){
            if(campo[col][lin]==num){
                printf("\neste quadrado ja possui o numero");
                error++;
                return ERRO;
            }
        }
    }
    return CONTINUA;
}
int procura_vitoria(int campo[][MAX]){
    int lin, col;
    /*procurando espaço em branco*/
    for(lin=1;lin<MAX-1;lin++){
        for(col=1;col<MAX-1;col++){
            if(campo[col][lin]==0) return CONTINUA;
        }
    }
    return VITORIA;
}
int processa_escolha(int campo[][MAX], char marca[][MAX], int c, int l, int num){
    int resp;
    mov++;
    if(c>9||c<1||l>9||l<1||num>9||num<1){/*Filtrando as entradas*/
        printf("\nEscolha numeros entre 1-9");
        error++;
        return ERRO;
    }
    else{
        resp=procura_erro(campo,marca,c,l,num);
        if(resp!=ERRO){
            campo[c][l]=num;
            resp=procura_vitoria(campo);
            if(resp==VITORIA){
                printf("\n\n-----//Parabens voce venceu//----\n-----//   Voce e' o foda   //----\n");
                return VITORIA;
            }
        }
        else return ERRO;
    }
    return CONTINUA;
}
int main(){
    int resultado=CONTINUA, campo[MAX][MAX], l, c, num;
    char marca[MAX][MAX];
    inicializa_marca(campo,marca);
    inicializa_campo(campo,marca);
    printf("\nDigite numeros entre 1-9, na seguinte ordem:linha, coluna e numero\nEx:X X X\n");
    while(resultado!=VITORIA){
        imprime(campo);
        scanf("%d %d %d", &l, &c, &num);
        resultado=processa_escolha(campo, marca, c, l, num);
    }
    printf("\nEstatistica do jogo:\n%d movimentos\n%d erros\n\n",mov,error);
    return 0;
}
