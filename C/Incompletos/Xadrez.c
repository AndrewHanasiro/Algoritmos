#include <stdio.h>
#define MAX 9
/*Jogador c/ peça branca*/
#define PEAOb 'P'
#define TORREb 'T'
#define BISPOb 'B'
#define CAVALOb 'C'
#define RAINHAb 'A'
#define REIb 'R'
/*Jogador c/ peça preta*/
#define PEAOp 'p'
#define TORREp 't'
#define BISPOp 'b'
#define CAVALOp 'c'
#define RAINHAp 'a'
#define REIp 'r'
/*Valores campo*/
#define VAZIO ' '
/*Valores do sistema*/
#define CONTINUA 1
void inicializa(char tab[][MAX]){
    int i, j;
    for(i=1;i<9;i++){
        for(j=1;j<9;j++){
            tab[i][j]=VAZIO;
            if(i==1||i==2){
                if(i==2) tab[i][j]=PEAOp;
                else{
                    if(j==1||j==8) tab[i][j]=TORREp;
                    if(j==2||j==7) tab[i][j]=BISPOp;
                    if(j==3||j==6) tab[i][j]=CAVALOp;
                    if(j==4) tab[i][j]=REIp;
                    if(j==5) tab[i][j]=RAINHAp;
                }
            }
            if(i==7||i==8){
                if(i==2) tab[i][j]=PEAOb;
                else{
                    if(j==1||j==8) tab[i][j]=TORREb;
                    if(j==2||j==7) tab[i][j]=BISPOb;
                    if(j==3||j==6) tab[i][j]=CAVALOb;
                    if(j==4) tab[i][j]=REIb;
                    if(j==5) tab[i][j]=RAINHAb;
                }
            }
        }
    }
}
int vitoria(char tab[][MAX]){
}
void imprime(char tab[][MAX]){
}
int analise(char tab[][MAX], int lin, int col){
}
void jogada(char tab[][MAX], int lin, int col, int player){
}
int main(){
    int lin, col;
    char tab[9][9];
    inicializa(tab);
    while(vitoria(tab)==CONTINUA){
        imprime(tab);
        printf("\nDigite onde que jogar:");
        scanf("%d %d",&lin,&col);
        if(analise(tab,lin,col)==1){
            jogada(tab,lin,col,player);
            contra_ataque(tab);
        }
    }
    imprime(tab);
    if(vitoria(tab)!=EMPATE) printf("\nO jogador %c ganhou",vitoria(tab));
    else printf("\nEmpate");
    return 0;
}

