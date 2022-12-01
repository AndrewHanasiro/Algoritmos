#include<stdio.h>
#include<stdlib.h>
#define MAX 4
#define VAZIO ' '
#define CONTINUA 'C'
#define EMPATE 'E'
#define HUMAN 'X'
#define BOT 'O'
void imprime(char tab[][MAX]){
    int i,j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            if(i==0&&j==0) printf(" ");
            if(i==0&&j>0) printf("%d ",j);
            if(i>0&&j==0) printf("\n%d",i);
            if(i>0&&j>0) printf("%c",tab[i][j]);
            if((j==1||j==2)&&i>0) printf("|");
            if(j==3&&(i==1||i==2)) printf("\n -+-+-");
        }
    }
}
void zera(char tab[][MAX]){
    int i,j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            tab[i][j]=VAZIO;
        }
    }
}
char vitoria(char tab[][MAX]){
    int i,j;
    /*vitoria por linha*/
    for(i=1;i<MAX;i++){
        if((tab[i][1]==tab[i][2])&&(tab[i][1]==tab[i][3])){
            if(tab[i][2]!=VAZIO) return tab[i][2];
        }
    }
    /*vitoria por coluna*/
    for(j=1;j<MAX;j++){
        if((tab[1][j]==tab[2][j])&&(tab[1][j]==tab[3][j])){
            if(tab[2][j]!=VAZIO) return tab[2][j];
        }
    }
    /*vitoria por diagonal*/
    if((tab[1][1]==tab[2][2])&&(tab[1][1]==tab[3][3])){
        if(tab[2][2]!=VAZIO)return tab[2][2];
    }
    if((tab[3][1]==tab[2][2])&&(tab[3][1]==tab[1][3])){
        if(tab[2][2]!=VAZIO)return tab[2][2];
    }
    /*analisa se CONTINUA*/
    for(i=1;i<MAX;i++){
        for(j=1;j<MAX;j++){
            if(tab[i][j]==VAZIO) return CONTINUA;
        }
    }
    /*se nao tem vazio, nem vitoria enta retorna empate*/
    return EMPATE;
}
int analise(char tab[][MAX],int lin,int col){
    if(tab[lin][col]!=VAZIO)return 0;
    if(lin<1||lin>MAX-1) return 0;
    if(col<1||col>MAX-1) return 0;
    return 1;
}
void jogada(char tab[][MAX],int lin,int col,char player){
    tab[lin][col]=player;
}
void contra_ataque(char tab[][MAX]){
    int i,j,mov=0;
    /*ver se tem vitoria por linha*/
    for(i=1;i<MAX;i++){
        if(tab[i][1]==BOT&&tab[i][2]==BOT){
            if(analise(tab,i,3)==1){
                jogada(tab,i,3,BOT);
                mov=1;
                break;
            }
        }
        if(tab[i][1]==BOT&&tab[i][3]==BOT){
            if(analise(tab,i,2)==1){
                jogada(tab,i,2,BOT);
                mov=1;
                break;
            }
        }
        if(tab[i][2]==BOT&&tab[i][3]==BOT){
            if(analise(tab,i,1)==1){
                jogada(tab,i,1,BOT);
                mov=1;
                break;
            }
        }
    }
    /*ver se tem vitoria por coluna*/
    if(mov==0){
        for(j=1;j<MAX;j++){
            if(tab[1][j]==BOT&&tab[2][j]==BOT){
                if(analise(tab,3,j)==1){
                    jogada(tab,3,j,BOT);
                    mov=1;
                    break;
                }
            }
            if(tab[1][j]==BOT&&tab[3][j]==BOT){
                if(analise(tab,2,j)==1){
                    jogada(tab,2,j,BOT);
                    mov=1;
                    break;
                }
            }
            if(tab[2][j]==BOT&&tab[3][j]==BOT){
                if(analise(tab,1,j)==1){
                    jogada(tab,1,j,BOT);
                    mov=1;
                    break;
                }
            }
        }
    }
    /*ver se tem vitoria por diagona*/
    if(tab[1][1]==BOT&&tab[2][2]==BOT&&mov==0){
        if(analise(tab,3,3)==1){
            jogada(tab,3,3,BOT);
            mov=1;
        }
    }
    if(tab[1][1]==BOT&&tab[3][3]==BOT&&mov==0){
        if(analise(tab,2,2)==1){
            jogada(tab,2,2,BOT);
            mov=1;
        }
    }
    if(tab[2][2]==BOT&&tab[3][3]==BOT&&mov==0){
        if(analise(tab,1,1)==1){
            jogada(tab,1,1,BOT);
            mov=1;
        }
    }
    if(tab[1][3]==BOT&&tab[2][2]==BOT&&mov==0){
        if(analise(tab,3,1)==1){
            jogada(tab,3,1,BOT);
            mov=1;
        }
    }
    if(tab[1][3]==BOT&&tab[3][1]==BOT&&mov==0){
        if(analise(tab,2,2)==1){
            jogada(tab,2,2,BOT);
            mov=1;
        }
    }
    if(tab[2][2]==BOT&&tab[3][1]==BOT&&mov==0){
        if(analise(tab,1,3)==1){
            jogada(tab,1,3,BOT);
            mov=1;
        }
    }
    /*defender por linha*/
    if(mov==0){
        for(i=1;i<MAX;i++){
            if(tab[i][1]==HUMAN&&tab[i][2]==HUMAN){
                if(analise(tab,i,3)==1){
                    jogada(tab,i,3,BOT);
                    mov=1;
                    break;
                }
            }
            if(tab[i][1]==HUMAN&&tab[i][3]==HUMAN){
                if(analise(tab,i,2)==1){
                    jogada(tab,i,2,BOT);
                    mov=1;
                    break;
                }
            }
            if(tab[i][2]==HUMAN&&tab[i][3]==HUMAN){
                if(analise(tab,i,1)==1){
                    jogada(tab,i,1,BOT);
                    mov=1;
                    break;
                }
            }
        }
    }
    /*defender por coluna*/
    for(j=1;j<MAX;j++){
        if(tab[1][j]==HUMAN&&tab[2][j]==HUMAN&&mov==0){
            if(analise(tab,3,j)==1){
                jogada(tab,3,j,BOT);
                mov=1;
                break;
            }
        }
        if(tab[1][j]==HUMAN&&tab[3][j]==HUMAN&&mov==0){
            if(analise(tab,2,j)==1){
                jogada(tab,2,j,BOT);
                mov=1;
                break;
            }
        }
        if(tab[2][j]==HUMAN&&tab[3][j]==HUMAN&&mov==0){
            if(analise(tab,1,j)==1){
                jogada(tab,1,j,BOT);
                mov=1;
                break;
            }
        }
    }
    /*defender por diagona*/
    if(tab[1][1]==HUMAN&&tab[2][2]==HUMAN&&mov==0){
        if(analise(tab,3,3)==1){
            jogada(tab,3,3,BOT);
            mov=1;
        }
    }
    if(tab[1][1]==HUMAN&&tab[3][3]==HUMAN&&mov==0){
        if(analise(tab,2,2)==1){
            jogada(tab,2,2,BOT);
            mov=1;
        }
    }
    if(tab[2][2]==HUMAN&&tab[3][3]==HUMAN&&mov==0){
        if(analise(tab,1,1)==1){
            jogada(tab,1,1,BOT);
            mov=1;
        }
    }
    if(tab[1][3]==HUMAN&&tab[2][2]==HUMAN&&mov==0){
        if(analise(tab,3,1)==1){
            jogada(tab,3,1,BOT);
            mov=1;
        }
    }
    if(tab[1][3]==HUMAN&&tab[3][1]==HUMAN&&mov==0){
        if(analise(tab,2,2)==1){
            jogada(tab,2,2,BOT);
            mov=1;
        }
    }
    if(tab[2][2]==HUMAN&&tab[3][1]==HUMAN&&mov==0){
        if(analise(tab,1,3)==1){
            jogada(tab,1,3,BOT);
            mov=1;
        }
    }
    /*colocar estratégicamente*/
    if(mov==0){
        if(tab[1][1]==BOT&&tab[1][3]==BOT){
            if((tab[2][1]==VAZIO&&tab[2][2]==VAZIO)||(tab[1][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[1][2]==VAZIO)){
                if(analise(tab,3,1)==1&&mov==0){
                    jogada(tab,3,1,BOT);
                    mov=1;
                }
            }
            if((tab[1][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[1][2]==VAZIO)){
                if(analise(tab,3,3)==1&&mov==0){
                    jogada(tab,3,3,BOT);
                    mov=1;
                }
            }
            if((tab[3][1]==VAZIO&&tab[3][3]==VAZIO)||(tab[3][1]==VAZIO&&tab[1][2]==VAZIO)||(tab[3][3]==VAZIO&&tab[1][2]==VAZIO)){
                if(analise(tab,2,2)==1&&mov==0){
                    jogada(tab,2,2,BOT);
                    mov=1;
                }
            }
        }
        if(tab[1][1]==BOT&&tab[3][1]==BOT){
            if((tab[1][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[2][2]==VAZIO)||(tab[1][2]==VAZIO&&tab[2][1]==VAZIO)){
                if(analise(tab,1,3)==1&&mov==0){
                    jogada(tab,1,3,BOT);
                    mov=1;
                }
            }
            if((tab[3][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[3][2]==VAZIO)){
                if(analise(tab,3,3)==1&&mov==0){
                    jogada(tab,3,3,BOT);
                    mov=1;
                }
            }
            if((tab[1][3]==VAZIO&&tab[3][3]==VAZIO)||(tab[1][3]==VAZIO&&tab[2][1]==VAZIO)||(tab[3][3]==VAZIO&&tab[2][1]==VAZIO)){
                if(analise(tab,2,2)==1&&mov==0){
                    jogada(tab,2,2,BOT);
                    mov=1;
                }
            }
        }
        if(tab[1][3]==BOT&&tab[3][3]==BOT){
            if((tab[1][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[2][2]==VAZIO)||(tab[1][2]==VAZIO&&tab[2][3]==VAZIO)){
                if(analise(tab,1,1)==1&&mov==0){
                    jogada(tab,1,1,BOT);
                    mov=1;
                }
            }
            if((tab[3][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[3][2]==VAZIO)){
                if(analise(tab,3,1)==1&&mov==0){
                    jogada(tab,3,1,BOT);
                    mov=1;
                }
            }
            if((tab[1][1]==VAZIO&&tab[3][1]==VAZIO)||(tab[1][1]==VAZIO&&tab[2][3]==VAZIO)||(tab[3][1]==VAZIO&&tab[2][3]==VAZIO)){
                if(analise(tab,2,2)==1&&mov==0){
                    jogada(tab,2,2,BOT);
                    mov=1;
                }
            }
        }
        if(tab[3][1]==BOT&&tab[3][3]==BOT){
            if((tab[2][2]==VAZIO&&tab[3][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][1]==VAZIO&&tab[3][2]==VAZIO)){
                if(analise(tab,1,1)==1&&mov==0){
                    jogada(tab,1,1,BOT);
                    mov=1;
                }
            }
            if((tab[3][2]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[2][2]==VAZIO)||(tab[2][3]==VAZIO&&tab[3][2]==VAZIO)){
                if(analise(tab,1,3)==1&&mov==0){
                    jogada(tab,1,3,BOT);
                    mov=1;
                }
            }
            if((tab[1][1]==VAZIO&&tab[1][3]==VAZIO)||(tab[1][1]==VAZIO&&tab[3][2]==VAZIO)||(tab[1][3]==VAZIO&&tab[3][2]==VAZIO)){
                if(analise(tab,2,2)==1&&mov==0){
                    jogada(tab,2,2,BOT);
                    mov=1;
                }
            }
        }
    }
    /*colocando de qualquer jeito*/
    while(mov==0){
        i=(rand()*rand())%3;
        j=(rand()*rand())%3;
        if(analise(tab,i,j)==1){
            jogada(tab,i,j,BOT);
            mov=1;
        }
    }
}
int main(){
    char tab[MAX][MAX];
    char player=HUMAN;
    int lin,col;
    zera(tab);
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
