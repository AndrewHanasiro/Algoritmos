/***********************************/
/** Jogo da Velha com 3 dimensões **/
/** Informações sobre a matriz:   **/
/** Tab[Piso][Linha][Coluna]      **/
/** Andrew Kenji Hanasiro         **/
/***********************************/
#include<stdio.h>
#include<stdlib.h>
#define HUMAN 'X'
#define BOT 'O'
#define VAZIO ' '
#define CONTINUA 'C'
#define EMPATE 'E'
#define NAO 9999
void zera(char ***tab, int tam);
void imprime(char ***tab, int tam);
char vitoria(char ***tab,int tam);
int analisa(char ***tab,int tam,int p,int l,int c);
void move(char ***tab,int p,int l,int c,char player);
void contra_ataque(char ***tab, int tam);
int *cria_vetor_count(int tam);
int **cria_matriz_count(int tam);
int main(){
    int tam,p,l,c;
    int i,j;
    char ***tab;
    printf("Qual tamanho do cubo:");
    scanf("%d",&tam);
    tam++;
    tab=(char***)malloc(tam*sizeof(char**));
    for(i=0;i<tam;i++){
        tab[i]=(char**)malloc(tam*sizeof(char*));
        for(j=0;j<tam;j++){
            tab[i][j]=(char*)malloc(tam*sizeof(char));
        }
    }
    zera(tab,tam);
    while(vitoria(tab,tam)==CONTINUA){
        system("cls");
        imprime(tab,tam);
        printf("\nDigite o piso, lin, coluna separados por espaco:");
        scanf("%d %d %d",&p,&l,&c);
        fflush(stdin);
        if(analisa(tab,tam,p,l,c)==1){
            move(tab,p,l,c,HUMAN);
            contra_ataque(tab,tam);
        }
    }
    if(vitoria(tab,tam)==HUMAN) printf("-----------//Parabens vc ganhou//-----------");
    else printf("-----------//Voce Perdeu//-----------");
    return 0;
}
void zera(char ***tab, int tam){
    int piso,lin,col;
    for(piso=0;piso<tam;piso++){
        for(lin=0;lin<tam;lin++){
            for(col=0;col<tam;col++){
                tab[piso][lin][col]=' ';
            }
        }
    }
}
void imprime(char ***tab, int tam){
    int i,piso,lin,col;
    for(piso=1;piso<tam;piso++){/*piso 0 nao tem nada*/
        for(lin=0;lin<tam;lin++){
            for(col=0;col<tam;col++){
                if(lin==0&&col==0) printf("\npiso=%d\n  ",piso);
                if(lin==0&&col>0) printf("%d ",col);
                if(lin>0&&col==0){
                    printf("\n +");
                    for(i=1;i<tam;i++) printf("-+");
                    printf("\n%d|",lin);
                }
                if(lin>0&&col>0) printf("%c|",tab[piso][lin][col]);
            }
        }
        printf("\n +");
        for(i=1;i<tam;i++) printf("-+");
    }
}
char vitoria(char ***tab,int tam){
    int i,j,piso,lin,col;
    int **count_lin,**count_col,**count_piso,*count_diag_piso_SE,*count_diag_col_SE,*count_diag_lin_SE,*count_diag_piso_NE,* count_diag_col_NE,*count_diag_lin_NE;
    /*alocando matrizes e vetores contadores*/
    count_diag_piso_SE=cria_vetor_count(tam);
    count_diag_col_SE=cria_vetor_count(tam);
    count_diag_lin_SE=cria_vetor_count(tam);
    count_diag_piso_NE=cria_vetor_count(tam);
    count_diag_col_NE=cria_vetor_count(tam);
    count_diag_lin_NE=cria_vetor_count(tam);
    count_lin=cria_matriz_count(tam);
    count_col=cria_matriz_count(tam);
    count_piso=cria_matriz_count(tam);
    /*buscando se alguem venceu*/
    for(piso=1;piso<tam;piso++){
        for(lin=1;lin<tam;lin++){
            for(col=1;col<tam;col++){
                if(tab[piso][lin][col]==HUMAN){
                    count_lin[piso][lin]++;
                    count_col[piso][col]++;
                    count_piso[lin][col]++;
                    if(lin==col)count_diag_piso_SE[piso]++;
                    if(lin==piso)count_diag_col_SE[col]++;
                    if(piso==col)count_diag_lin_SE[lin]++;
                    if(lin+col==tam)count_diag_piso_NE[piso]++;
                    if(lin+piso==tam)count_diag_col_NE[col]++;
                    if(piso+col==tam)count_diag_lin_NE[lin]++;
                }
                if(tab[piso][lin][col]==BOT){
                    count_lin[piso][lin]--;
                    count_col[piso][col]--;
                    count_piso[lin][col]--;
                    if(lin==col)count_diag_piso_SE[piso]--;
                    if(lin==piso)count_diag_col_SE[col]--;
                    if(piso==col)count_diag_lin_SE[lin]--;
                    if(lin+col==tam)count_diag_piso_NE[piso]--;
                    if(lin+piso==tam)count_diag_col_NE[col]--;
                    if(piso+col==tam)count_diag_lin_NE[lin]--;
                }
            }
        }
    }
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            if(count_lin[i][j]==tam-1) return HUMAN;/*venceu por linha*/
            if(count_col[i][j]==tam-1) return HUMAN;/*venceu por col*/
            if(count_piso[i][j]==tam-1) return HUMAN;/*venceu por piso*/
            if(count_diag_piso_SE[i]==tam-1) return HUMAN;/*venceu pela diagonal SE do piso i*/
            if(count_diag_col_SE[i]==tam-1) return HUMAN;/*venceu pela diagonal SE da coluna i*/
            if(count_diag_lin_SE[i]==tam-1) return HUMAN;/*venceu pela diagonal SE da linha i*/
            if(count_diag_piso_NE[i]==tam-1) return HUMAN;/*venceu pela diagonal NE do piso i*/
            if(count_diag_col_NE[i]==tam-1) return HUMAN;/*venceu pela diagonal NE da coluna i*/
            if(count_diag_lin_NE[i]==tam-1) return HUMAN;/*venceu pela diagonal NE da linha i*/
            if(count_lin[i][j]==1-tam) return BOT;/*perdeu por linha*/
            if(count_col[i][j]==1-tam) return BOT;/*perdeu por col*/
            if(count_piso[i][j]==1-tam) return BOT;/*perdeu por piso*/
            if(count_diag_piso_SE[i]==1-tam) return BOT;/*perdeu pela diagonal SE do piso i*/
            if(count_diag_col_SE[i]==1-tam) return BOT;/*perdeu pela diagonal SE da coluna i*/
            if(count_diag_lin_SE[i]==1-tam) return BOT;/*perdeu pela diagonal SE da linha i*/
            if(count_diag_piso_NE[i]==1-tam) return BOT;/*perdeu pela diagonal NE do piso i*/
            if(count_diag_col_NE[i]==1-tam) return BOT;/*perdeu pela diagonal NE da coluna i*/
            if(count_diag_lin_NE[i]==1-tam) return BOT;/*perdeu pela diagonal NE da linha i*/
        }
    }
    /*vendo se há espaços vazios,caso ache retorne CONTINUA*/
    for(piso=1;piso<tam;piso++){
        for(lin=1;lin<tam;lin++){
            for(col=1;col<tam;col++){
                if(tab[piso][lin][col]==VAZIO) return CONTINUA;
            }
        }
    }
    /*caso contrario, ou seja, todos os espaçoes estão preenchidos e ninguém ganhou*/
    return EMPATE;
}
int analisa(char ***tab,int tam,int p,int l,int c){
    /*vendo quais jogadas não são permitidas*/
    if(tab[p][l][c]!=VAZIO) return 0;
    if(p>tam-1||p<1||l>tam-1||l<1||c>tam-1||c<1) return 0;
    return 1;
}
void move(char ***tab,int p,int l,int c,char player){
    tab[p][l][c]=player;
}
int *cria_vetor_count(int tam){
    int i,*vetor;
    vetor=(int*)malloc(tam*sizeof(int));
    for(i=0;i<tam;i++) vetor[i]=0;
    return vetor;
}
int **cria_matriz_count(int tam){
    int i,j,**matriz;
    matriz=(int**)malloc(tam*sizeof(int*));
    for(i=0;i<tam;i++){
        matriz[i]=(int*)malloc(tam*sizeof(int));
        for(j=0;j<tam;j++) matriz[i][j]=0;
    }
    return matriz;
}
void contra_ataque(char ***tab, int tam){
    int i,piso,lin,col,mov;
    int **count_lin,**count_col,**count_piso,*count_diag_piso_SE,*count_diag_col_SE,*count_diag_lin_SE,*count_diag_piso_NE,* count_diag_col_NE,*count_diag_lin_NE;
    /*alocando matrizes e vetores contadores*/
    count_diag_piso_SE=cria_vetor_count(tam);
    count_diag_col_SE=cria_vetor_count(tam);
    count_diag_lin_SE=cria_vetor_count(tam);
    count_diag_piso_NE=cria_vetor_count(tam);
    count_diag_col_NE=cria_vetor_count(tam);
    count_diag_lin_NE=cria_vetor_count(tam);
    count_lin=cria_matriz_count(tam);
    count_col=cria_matriz_count(tam);
    count_piso=cria_matriz_count(tam);
    /*vendo se tem como atacar e defender ao mesmo tempo*/
    for(piso=1;piso<tam;piso++){
        for(lin=1;lin<tam;lin++){
            for(col=1;col<tam;col++){
                if(tab[piso][lin][col]==HUMAN){
                    count_lin[piso][lin]=NAO;
                    count_col[piso][col]=NAO;
                    count_piso[lin][col]=NAO;
                    if(lin==col)count_diag_piso_SE[piso]=NAO;
                    if(lin==piso)count_diag_col_SE[col]=NAO;
                    if(piso==col)count_diag_lin_SE[lin]=NAO;
                    if(lin+col==tam)count_diag_piso_NE[piso]=NAO;
                    if(lin+piso==tam)count_diag_col_NE[col]=NAO;
                    if(piso+col==tam)count_diag_lin_NE[lin]=NAO;
                }
                if(tab[piso][lin][col]==BOT){
                    count_lin[piso][lin]--;
                    count_col[piso][col]--;
                    count_piso[lin][col]--;
                    if(lin==col)count_diag_piso_SE[piso]--;
                    if(lin==piso)count_diag_col_SE[col]--;
                    if(piso==col)count_diag_lin_SE[lin]--;
                    if(lin+col==tam)count_diag_piso_NE[piso]--;
                    if(lin+piso==tam)count_diag_col_NE[col]--;
                    if(piso+col==tam)count_diag_lin_NE[lin]--;
                }
            }
        }
    }
    /*verificando onde tem peça HUMAN e onde não tem*/
    for(piso=1;piso<tam;piso++){
        for(lin=1;lin<tam;lin++){
            for(col=1;col<tam;col++){
                if(count_lin[piso][lin]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,piso,lin,i)==1){
                            move(tab,piso,lin,i,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_col[piso][col]<=0){/*Quer dizer que não tem peça humana na coluna,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,piso,i,col)==1){
                            move(tab,piso,i,col,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_piso[lin][col]<=0){/*Quer dizer que não tem peça humana na piso,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,i,lin,col)==1){
                            move(tab,i,lin,col,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_piso_SE[piso]<=0){/*Quer dizer que não tem peça humana na diagonal SE por piso,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,piso,i,i)==1){
                            move(tab,piso,i,i,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_col_SE[col]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,i,i,col)==1){
                            move(tab,i,i,col,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_lin_SE[lin]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,i,lin,i)==1){
                            move(tab,i,lin,i,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_piso_NE[piso]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,piso,i,tam-i)==1){
                            move(tab,piso,i,tam-i,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_col_NE[col]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,i,tam-i,col)==1){
                            move(tab,i,tam-i,col,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
                if(count_diag_lin_NE[lin]<=0){/*Quer dizer que não tem peça humana na linha,portanto há como vencer nesta*/
                    for(i=1;i<tam;i++){
                        if(analisa(tab,tam,tam-i,lin,i)==1){
                            move(tab,tam-i,lin,i,BOT);
                            mov=1;
                            break;
                        }
                    }
                    if(mov==1) break;
                }
            }
            if(mov==1) break;
        }
        if(mov==1) break;
    }
    /*liberando memoria*/
    free(count_diag_piso_SE);
    free(count_diag_col_SE);
    free(count_diag_lin_SE);
    free(count_diag_piso_NE);
    free(count_diag_col_NE);
    free(count_diag_lin_NE);
    for(i=0;i<tam;i++){
        free(count_lin[i]);
        free(count_col[i]);
        free(count_piso[i]);
    }
    free(count_lin);
    free(count_col);
    free(count_piso);
}

