#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define PLAYER 'P'
#define HOUSE 'H'
#define MAXCARD 11
int **inicializa(){
    int i,j,**cartas;
    cartas=(int**)malloc(4*sizeof(int*)); /*Quatro naipes*/
    for(i=0;i<4;i++){
        cartas[i]=(int*)malloc(13*sizeof(int));/*13 tipos de cartas*/
        for(j=0;j<13;j++){
            cartas[i][j]=1; /*1 ela ainda está no baralho, -1 ela foi retirada*/
        }
    }
    return cartas;
}
int *placar_ini(){
    int *placar;
    placar=(int*)malloc(2*sizeof(int));
    placar[0]=0;
    placar[1]=0;
    return placar;
}
int **hand_ini(){
    int i,j,**hand;
    hand=(int**)malloc(11*sizeof(int*));/*No maximo 11 cartas pra estourar*/
    for(i=0;i<MAXCARD;i++){
        hand[i]=(int*)malloc(2*sizeof(int));/*primeira coluna para o naipe e segunda coluna para o valor*/
        for(j=0;j<2;j++){
            hand[i][j]=-1; /*Carta vazia*/
        }
    }
    return hand;
}
void reconhece_cartas(int naipe,int valor){
    switch(valor){
        case 0: printf("As de ");
        break;
        case 1: printf("Dois de ");
        break;
        case 2: printf("Tres de ");
        break;
        case 3: printf("Quatro de ");
        break;
        case 4: printf("Cinco de ");
        break;
        case 5: printf("Seis de ");
        break;
        case 6: printf("Sete de ");
        break;
        case 7: printf("Oito de ");
        break;
        case 8: printf("Nove de ");
        break;
        case 9: printf("Dez de ");
        break;
        case 10: printf("Valete de ");
        break;
        case 11: printf("Dama de ");
        break;
        case 12: printf("Rei de ");
        break;
    }
    switch(naipe){
        case 0: printf("Ouros\n");
        break;
        case 1: printf("Espadas\n");
        break;
        case 2: printf("Copas\n");
        break;
        case 3: printf("Paus\n");
        break;
    }
}
void jogada(int **cartas,int *naipe,int *valor,char player){
    int cond=0;
    srand(time(NULL));
    while(cond==0){
        *naipe=rand()%4;
        *valor=rand()%13;
        if(cartas[*naipe][*valor]!=-1){ /*Se ela ainda não foi tirada*/
            cond=1;
            cartas[*naipe][*valor]=-1; /*Retira ela do baralho*/
        }
    }
    if(player==PLAYER) printf("Voce recebeu a carta ");
    if(player==HOUSE) printf("A Casa recebeu a carta ");
    reconhece_cartas(*naipe,*valor);
}
int hand_reg(int **handX,int naipe,int valor,int quant){
    int count=0;
    int i;
    handX[quant][0]=naipe;
    handX[quant][1]=valor;
    /*Calculando a soma das cartas*/
    for(i=0;i<MAXCARD;i++){
        if(handX[i][0]==-1) break;/*Nao tem mais carta*/
        else{
            if(handX[i][1]>0&&handX[i][1]<10) count+=(handX[i][1]+1); /*Se a carta for diferente de AS,REIS DAMAS VALETE então soma normal*/
            else{
                if(handX[i][1]>=10) count+=10; /*Neste caso é figura*/
                else{ /*Neste caso é o As que pode valer 11 ou 1 dependendo da situação*/
                    if(count+11>21) count+=1;
                    else count+=11;
                }
            }
        }
    }
    return count;
}
int analisa_Player(int countP){
    int fim=1,escolha;
    printf("Voce ");
    if(countP<21){
        printf("soma %d\n",countP);
        printf("0-sim\n1-nao\nDeseja mais uma carta:");
        scanf("%d",&escolha);
        if(escolha==1) return 1; /*Nao continua*/
        else return 0; /*Continua*/
    }
    if(countP==21) printf("fez uma pontuacao perfeita!\n");
    if(countP>21) printf("estourou\n");
    return fim;
}
int analisa_House(int countP,int countH){
    printf("A casa ");
    if(countH<21){
        printf("soma %d\n",countH);
        if(countH>=countP||countP>21) return 1;/*Neste caso a Casa ganha ou empata*/
        else return 0;
    }
    if(countH==21) printf("fez uma pontuacao perfeita!\n");
    if(countH>21) printf("estourou\n");
    return 1;
}
int analisa_Game(int *countP, int *countH,int *placar){
    int fim_jogo;
    int BOT,HUMAN;
    HUMAN=(*countP);
    BOT=(*countH);
    if((HUMAN>BOT&&HUMAN<=21)||BOT>21){
        printf("Parabens voce ganhou\n");
        placar[0]++;
    }
    if(HUMAN==BOT) printf("Voce empatou\n");
    if((HUMAN<BOT&&BOT<=21)||HUMAN>21){
        printf("Voce perdeu\n");
        placar[1]++;
    }
    printf("Placar: Voce %d X PC %d\n",placar[0],placar[1]);
    *countP=0;
    *countH=0;
    printf("0-Sim\n1-Nao\nDeseja jogar mais uma:");
    scanf("%d",&fim_jogo);
    return fim_jogo;
}
void fimturno(int *fim_turno,int *quant,char *player){
    *fim_turno=0;
    *quant=0;
    if(*player==PLAYER) *player=HOUSE;
    else *player=PLAYER;
}
int analisa_baralho(int **cartas){
    int i,j,count=0;
    for(i=0;i<4;i++){
        for(j=0;j<13;j++){
            if(cartas[i][j]!=-1){
                if(j>=9) count+=10;
                else count+=(j+1);
            }
        }
    }
    if(count<42) return 1;
    else return 0;
}
void libera(int **cartas,int **handP,int **handH){
    int i;
    for(i=0;i<4;i++){
        free(cartas[i]);
    }
    free(cartas);
    for(i=0;i<MAXCARD;i++){
        free(handP[i]);
        free(handH[i]);
    }
    free(handP);
    free(handH);
}
int main(){
    int **cartas,fim_turno=0,fim_jogo=0,countP=0,countH=0,**handP,**handH,naipe,valor,quant=0,troca=0,*placar;
    char player=PLAYER;
    placar=placar_ini();
    cartas=inicializa();
    while(fim_jogo==0){
        system("cls");
        handP=hand_ini();
        handH=hand_ini();
        /*Começo do turno do PLAYER*/
        while(fim_turno==0){
            jogada(cartas,&naipe,&valor,player); /*Sorteia uma carta do baralho*/
            countP=hand_reg(handP,naipe,valor,quant); /*Coloca na mão e calcula quantos pontos*/
            quant++;
            fim_turno=analisa_Player(countP); /*Analisa a situação*/
        }
        fimturno(&fim_turno,&quant,&player);/*zera as duas primeiras variaveis e troca a terceira*/
        /*Começo do turno do HOUSE*/
        while(fim_turno==0){
            jogada(cartas,&naipe,&valor,player);
            countH=hand_reg(handH,naipe,valor,quant);
            quant++;
            fim_turno=analisa_House(countP,countH);
        }
        fimturno(&fim_turno,&quant,&player);
        fim_jogo=analisa_Game(&countP,&countH,placar);/*analisa quem ganhou ou perdeu ou empatou*/
        troca=analisa_baralho(cartas);/*analisa o baralho para ver se tem quantidade de pontos suficiente*/
        if(troca==1){
            printf("Trocamos o baralho por falta de pontos\n");
            cartas=inicializa();
            troca=0;
        }
    }
    libera(cartas,handP,handH);
    return 0;
}
