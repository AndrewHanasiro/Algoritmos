#include<stdio.h>
#include<math.h>
#define MAX 9
#define VAZIO 0
#define MOLDURA 1
#define HUMAN 7
#define BRANCO 2
#define DAMAB 4
#define BOT -7
#define PRETO -2
#define DAMAP -4
/*funções pré declaradas*/
void zera_tabuleiro(int Tab[][MAX]);
void imprime(int Tab[][MAX]);
int verifica(int Tab[][MAX],int lin,int col,int l,int c,int player);
void move(int Tab[][MAX],int lin,int col,int l,int c,int player);
int continua(int Tab[][MAX],int lin,int col,int l,int c, int player);
void contra_ataque(int Tab[][MAX], int player,int *Ppenal);
int vitoria(int Tab[][MAX],int Bpenalidade,int Ppenalidade);
/*programa principal*/
int main(){
    int Tab[MAX][MAX],fim=VAZIO,lin,col,l,c,Bpenalidade=0,Ppenalidade=0;
    zera_tabuleiro(Tab);
    printf("Voce e' o jogador branco, por favor comece.\n");
    while(fim==VAZIO){
        imprime(Tab);
        printf("Digite a linha (X) e a coluna (Y) da peca,\na qual deseja mover para a posicao (a;b), exemplo:X Y a b\nCaso nao tenha como moviemntar entao digite:0 0 0 0\n");
        scanf("%d %d %d %d",&lin,&col,&l,&c);
        fflush(stdin);
        if(lin+col+l+c!=0){
            printf("Origem(%d;%d)\nDestino(%d;%d)\n",lin,col,l,c);
            if(verifica(Tab,lin,col,l,c,HUMAN)){
                move(Tab,lin,col,l,c,HUMAN);
                if(continua(Tab,lin,col,l,c,HUMAN)==0){
                    contra_ataque(Tab,BOT,&Ppenalidade);
                }
                fim=vitoria(Tab,Bpenalidade,Ppenalidade);
            }
        }
        else{
            Bpenalidade++;
            contra_ataque(Tab,BOT,&Ppenalidade);
            fim=vitoria(Tab,Bpenalidade,Ppenalidade);
            printf("Voce sofreu uma penalidade!!\n");
        }
    }
    if(fim==BRANCO) printf("\n--------------//VOCE GANHOU//--------------");
    else printf("\n--------------//VOCE PERDEU//--------------");
    return 0;
}
void zera_tabuleiro(int Tab[][MAX]){
    int i, j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            Tab[i][j]=VAZIO;
            if(i==1&&j%2==0) Tab[i][j]=PRETO;
            if(i==2&&j%2==1) Tab[i][j]=PRETO;
            if(i==3&&j%2==0) Tab[i][j]=PRETO;
            if(i==6&&j%2==1) Tab[i][j]=BRANCO;
            if(i==7&&j%2==0) Tab[i][j]=BRANCO;
            if(i==8&&j%2==1) Tab[i][j]=BRANCO;
            if(i==0||j==0) Tab[i][j]=MOLDURA;
        }
    }
}
void imprime(int Tab[][MAX]){
    int i, j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            if(i==0&&j==0) printf(" ");
            if(i==0&&j>0) printf(" %d",j);
            if(i>0&&j==0) printf("\n +-+-+-+-+-+-+-+-+\n%d|",i);
            if(Tab[i][j]==PRETO) printf("%c|",'p');
            if(Tab[i][j]==DAMAP) printf("%c|",'P');
            if(Tab[i][j]==BRANCO) printf("%c|",'b');
            if(Tab[i][j]==DAMAB) printf("%c|",'B');
            if(Tab[i][j]==VAZIO) printf(" |");
        }
        if(i==MAX-1) printf("\n +-+-+-+-+-+-+-+-+\n");
    }
}
int verifica(int Tab[][MAX],int lin,int col,int l,int c,int player){
    int mypieces, Xmypieces;
    if(player==HUMAN){
        mypieces=BRANCO;
        Xmypieces=DAMAB;
    }
    if(player==BOT){
        mypieces=PRETO;
        Xmypieces=DAMAP;
    }
    /*verificando se o jogador esta selecionando um peça dele*/
    if(!(Tab[lin][col]==mypieces||Tab[lin][col]==Xmypieces)){
        if(player==HUMAN) printf("ERRO: Voce nao esta selecionando sua peca\n");
        return 0;
    }
    /*verificando se o lugar qual ele deseja é válido*/
    if(lin==l&&col==c){/*vendo se o jogador esta parado*/
        if(player==HUMAN) printf("ERRO: Por favor mova a peca\n");
        return 0;
    }
    if(l>MAX-1||l<1||c>MAX-1||c<1){/*vendo se ele esta colocando fora do tabuleiro*/
        if(player==HUMAN) printf("ERRO: Coloque a peca no tabuleiro\n");
        return 0;
    }
    if(Tab[l][c]!=VAZIO){/*vendo se o jogador nao esta sobrepondo peças*/
        if(player==HUMAN) printf("ERRO: Nao pode Sobrepor pecas\n");
        return 0;
    }
    if(fabs(lin-l)!=fabs(col-c)){/*neste caso vamos verificar se o jogador esta movendo na diagonal*/
        if(player==HUMAN) printf("ERRO: Mova-se somente na diagonal\n");
        return 0;
    }
    if(Tab[lin][col]==mypieces&&(fabs(lin-l)>2||fabs(col-c)>2)){/*se comeu uma peça, verificar que seja 1 por vez*/
        if(player==HUMAN) printf("ERRO: Peca normal tentando mover mais que 2 casas\n");
        return 0;
    }
    if(Tab[lin][col]==mypieces){
            if(player==HUMAN&&lin-l<0){/*vendo se com peça normal ele está indo pra frente*/
                printf("ERRO: Peca normal tentando mover para tras\n");
                return 0;
            }
            if(player==BOT&&lin-l>0){/*vendo se com peça normal ele está indo pra frente*/
                return 0;
            }
    }
    return 1;
}
void move(int Tab[][MAX],int lin,int col,int l,int c,int player){
    int mypieces, Xmypieces;
    if(player==HUMAN){
        mypieces=BRANCO;
        Xmypieces=DAMAB;
    }
    if(player==BOT){
        mypieces=PRETO;
        Xmypieces=DAMAP;
    }
    Tab[l][c]=Tab[lin][col];
    Tab[lin][col]=VAZIO;
    if(Tab[l][c]==mypieces){
        if(player==HUMAN&&l==1) Tab[l][c]=Xmypieces;
        if(player==BOT&&l==MAX-1) Tab[l][c]=Xmypieces;
    }
}
int vitoria(int Tab[][MAX],int Bpenalidade,int Ppenalidade){
    int i, j,black=0,white=0;
    for(i=1;i<MAX;i++){
        for(j=1;j<MAX;j++){
            if(Tab[i][j]==PRETO) black=1;/*encontro peça preta*/
            if(Tab[i][j]==BRANCO) white=1;/*encontro peça branca*/
        }
    }
    if((black==1&&white==0)||Bpenalidade>1) return PRETO; /*encontro apenas peças preta*/
    if((black==0&&white==1)||Ppenalidade>1) return BRANCO; /*encontro apenas peças branca*/
    else return VAZIO;
}
void contra_ataque(int Tab[][MAX], int player,int *Ppenal){
    int enemy, Xenemy, mypieces, Xmypieces,i,j,k,mov=0;
    if(player==HUMAN){
        mypieces=BRANCO;
        Xmypieces=DAMAB;
        enemy=PRETO;
        Xenemy=DAMAP;
    }
    if(player==BOT){
        mypieces=PRETO;
        Xmypieces=DAMAP;
        enemy=BRANCO;
        Xenemy=DAMAB;
    }
    /*procurando pecas pra comer*/
    for(i=1;i<MAX;i++){
        for(j=1;j<MAX;j++){
            if(Tab[i][j]==mypieces){
                if(Tab[i+1][j+1]==enemy||Tab[i+1][j+1]==Xenemy){/*vendo se tem peça inimiga na diagonal da direita*/
                    if(verifica(Tab,i,j,i+2,j+2,player)){
                        move(Tab,i,j,i+2,j+2,player);
                        if(continua(Tab,i,j,i+2,j+2,player)==0){
                            mov=1;
                            break;
                        }
                    }
                }
                if(Tab[i+1][j-1]==enemy||Tab[i+1][j-1]==Xenemy){/*vendo se tem peça inimiga na diagonal da esquerda*/
                    if(verifica(Tab,i,j,i+2,j-2,player)){
                        move(Tab,i,j,i+2,j-2,player);
                        if(continua(Tab,i,j,i+2,j-2,player)==0){
                            mov=1;
                            break;
                        }
                    }
                }
            }
            if(Tab[i][j]==Xmypieces){/*se for dama entao verifica nas diagonais*/
                k=1;
                while(k<6){
                    if(Tab[i+k][j+k]==enemy||Tab[i+k][j+k]==Xenemy){
                        if(verifica(Tab,i,j,i+(k+1),j+(k+1),player)){
                            move(Tab,i,j,i+(k+1),j+(k+1),player);
                            if(continua(Tab,i,j,i+(k+1),j+(k+1),player)==0){
                                mov=1;
                                break;
                            }
                        }
                    }
                    if(Tab[i+k][j-k]==enemy||Tab[i+k][j+k]==Xenemy){
                        if(verifica(Tab,i,j,i+(k+1),j-(k+1),player)){
                            move(Tab,i,j,i+(k+1),j-(k+1),player);
                            if(continua(Tab,i,j,i+(k+1),j-(k+1),player)==0){
                                mov=1;
                                break;
                            }
                        }
                    }
                    if(Tab[i-k][j+k]==enemy||Tab[i+k][j+k]==Xenemy){
                        if(verifica(Tab,i,j,i-(k+1),j+(k+1),player)){
                            move(Tab,i,j,i-(k+1),j+(k+1),player);
                            if(continua(Tab,i,j,i-(k+1),j+(k+1),player)==0){
                                mov=1;
                                break;
                            }
                        }
                    }
                    if(Tab[i-k][j-k]==enemy||Tab[i+k][j+k]==Xenemy){
                        if(verifica(Tab,i,j,i-(k+1),j-(k+1),player)){
                            move(Tab,i,j,i-(k+1),j-(k+1),player);
                            if(continua(Tab,i,j,i-(k+1),j-(k+1),player)==0){
                                mov=1;
                                break;
                            }
                        }
                    }
                    k++;
                }
            }
            if(mov==1) break;
        }
        if(mov==1) break;
    }
    if(mov!=1){
        /*procurando peças normais pra movimentar sem ser comida*/
        for(i=1;i<MAX-1;i++){
            for(j=1;j<MAX-1;j++){
                if(Tab[i][j]==mypieces){
                    if(Tab[i+2][j]!=enemy){ /*vendo se tem peça inimiga na frente*/
                        if(Tab[i+2][j+2]!=enemy){ /*vendo se tem peça inimiga na diagonal da direita*/
                            if(verifica(Tab,i,j,i+1,j+1,player)){
                                move(Tab,i,j,i+1,j+1,player);
                                if(continua(Tab,i,j,i+1,j+1,player)==0){
                                    mov=1;
                                    break;
                                }
                            }
                        }
                        if(Tab[i+2][j-2]!=enemy){ /*vendo se tem peça inimiga na diagonal da esquerda*/
                            if(verifica(Tab,i,j,i+1,j-1,player)){
                                move(Tab,i,j,i+1,j-1,player);
                                if(continua(Tab,i,j,i+1,j-1,player)==0){
                                    mov=1;
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        if(Tab[i][j+2]==mypieces){ /*vendo se tem peça aliada na direita*/
                            if(verifica(Tab,i,j,i+1,j+1,player)){
                                move(Tab,i,j,i+1,j+1,player);
                                if(continua(Tab,i,j,i+1,j+1,player)==0){
                                    mov=1;
                                    break;
                                }
                            }
                        }
                        if(Tab[i][j-2]==mypieces){/*vendo se tem peça aliada na esquerda*/
                            if(verifica(Tab,i,j,i+1,j-1,player)){
                                move(Tab,i,j,i+1,j-1,player);
                                if(continua(Tab,i,j,i+1,j-1,player)==0){
                                    mov=1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(mov==1) break;
        }
        if(mov!=1){
            /*procurando peças normais pra movimentar mesmo que seja comida*/
            for(i=1;i<MAX-1;i++){
                for(j=1;j<MAX-1;j++){
                    if(Tab[i][j]==mypieces){
                        if(verifica(Tab,i,j,i+1,j+1,player)){
                            move(Tab,i,j,i+1,j+1,player);
                            if(continua(Tab,i,j,i+1,j+1,player)==0){
                                mov=1;
                                break;
                            }
                        }
                        if(verifica(Tab,i,j,i+1,j-1,player)){
                            move(Tab,i,j,i+1,j-1,player);
                            if(continua(Tab,i,j,i+1,j-1,player)==0){
                                mov=1;
                                break;
                            }
                        }
                    }
                }
                if(mov==1) break;
            }
            if(mov!=1) (*Ppenal)++;
        }
    }
}
int continua(int Tab[][MAX],int lin,int col,int l,int c, int player){
    int enemy, Xenemy,l2,c2,comeu=0,vet,hor;
    if(player==HUMAN){
        enemy=PRETO;
        Xenemy=DAMAP;
    }
    if(player==BOT){
        enemy=BRANCO;
        Xenemy=DAMAB;
    }
    /*verificando se comeu uma da redondeza peça*/
    vet=lin-l; /*se for positivo entao está indo pra frente, caso contrário pra trás*/
    hor=col-c; /*se for positivo esta indo pra esquerda, caso contrário está indo pra direita*/
    /*vendo há uma peça preta em uma das direçoes e verificando se a peça veio desta mesma direção*/
    if((Tab[l+1][c+1]==enemy||Tab[l+1][c+1]==Xenemy)&&vet>0&&hor>0){
        comeu=1;
        Tab[l+1][c+1]=VAZIO;
    }
    if((Tab[l+1][c-1]==enemy||Tab[l+1][c-1]==Xenemy)&&vet>0&&hor<0){
        comeu=1;
        Tab[l+1][c-1]=VAZIO;
    }
    if((Tab[l-1][c+1]==enemy||Tab[l-1][c+1]==Xenemy)&&vet<0&&hor>0){
        comeu=1;
        Tab[l-1][c+1]=VAZIO;
    }
    if((Tab[l-1][c-1]==enemy||Tab[l-1][c-1]==Xenemy)&&vet<0&&hor<0){
        comeu=1;
        Tab[l-1][c-1]=VAZIO;
    }
    if(comeu==1){
        /*vendo se há mais peças pra comer*/
        if(((Tab[l+1][c+1]==enemy||Tab[l+1][c+1]==Xenemy)&&Tab[l+2][c+2]==VAZIO)||
            ((Tab[l+1][c-1]==enemy||Tab[l+1][c-1]==Xenemy)&&Tab[l+2][c-2]==VAZIO)||
            ((Tab[l-1][c+1]==enemy||Tab[l-1][c+1]==Xenemy)&&Tab[l-2][c+2]==VAZIO)||
            ((Tab[l-1][c-1]==enemy||Tab[l-1][c-1]==Xenemy)&&Tab[l-2][c-2]==VAZIO)){
                imprime(Tab);
                if(player==HUMAN){
                    printf("Voce pode comer mais peca inimiga com esta ultima peca movimentada\n");
                    printf("Digite a linha (a) e a coluna (b) para a qual a peça vai, exemplo:a b\n");
                    scanf("%d %d",&l2,&c2);
                    fflush(stdin);
                }
                if(player==BOT){
                    if(Tab[l+1][c+1]==enemy||Tab[l+1][c+1]==Xenemy){
                        l2=l+2;
                        c2=c+2;
                    }
                    if(Tab[l+1][c-1]==enemy||Tab[l+1][c-1]==Xenemy){
                        l2=l+2;
                        c2=c-2;
                    }
                    if(Tab[l-1][c+1]==enemy||Tab[l-1][c+1]==Xenemy){
                        l2=l-2;
                        c2=c+2;
                    }
                    if(Tab[l-1][c-1]==enemy||Tab[l-1][c-1]==Xenemy){
                        l2=l-2;
                        c2=c-2;
                    }
                }
                if(verifica(Tab,l,c,l2,c2,player)){
                    move(Tab,l,c,l2,c2,player);
                    if(continua(Tab,l,c,l2,c2,player)==0) return 0;
                }
                else{
                    if(player==HUMAN) printf("Movimento nao permitido\n");
                }

        }
    }
    return 0;
}
