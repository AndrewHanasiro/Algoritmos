#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int *placar_ini();/*Aloca o placar e zera*/
int **inicializa();/*Constroi o baralho*/
int ***hand_ini(int **baralho); /*A partir do baralho constroi-se as mãos dos jogadores*/
void organiza_hands(int ***hands);/*Organiza-se todas as mãos*/
void atribui_peso(int ***hands);/*Coloca um valor baseado no naipe e valor em cada carta no endereço hands[jogador][carta][2]*/
void imprime_hand(int ***hands);/*Imprime a mão do jogador*/
void imprime_placar(int *placar);/*Imprime o Placar*/
void tradecards(int ***hands,int *rodada);/*Escolhe que cartas trocar, e diz com quem trocar*/
void troca_move(int ***hands, int ***card,int rodada); /*faz realmente a troca das cartas*/
int start_game(int ***hands);/*Verifica quem está com 2 de Paus*/
void jogada(int ***hands,int *start,int fim_turno,int *placar);/*faz jogada*/
void trade_AI(int ***hands,int ***card,int jogador);/*Escolha as tres melhores cartas pra trocar*/
int **mesa_ini();/*Aloca a mesa*/
void jogada_AI(int ***hands,int **mesa,int jogador,int start,int fim_turno);/*Escolhe qual carta eh melhor jogar*/
int turn_winner(int **mesa,int start,int *placar);/*Analisa quem venceu no turno*/
int analisa_game(int *placar);/*Analisa se tem algum jogador com mais de 100 pontos e se tiver ve se eh o HUMAN*/
int maximo_peso(int ***hands,int jogador,int naipe,int max_valor);/*retorna a carta que tem mais peso,baseado no naipe e no valor limite*/
void reconhece_cartas(int naipe,int valor);/*reconhece a carta e imprime*/
void libera(int **baralho,int ***hands,int *placar);/*Libera todas as memórias*/
void contabiliza(int *placar,int *placar_rodada);/*ve o placar_rodada e se não tiver nada de especial soma no placar*/
int main(){
    int **baralho,***hands,rodada=0,start,*placar,fim_jogo=0,fim_turno,*placar_rodada;
    placar=placar_ini();
    while(fim_jogo==0){
        srand(time(NULL));
        imprime_placar(placar);
        placar_rodada=placar_ini();
        baralho=inicializa();
        hands=hand_ini(baralho);
        atribui_peso(hands);
        system("cls");
        imprime_hand(hands);
        tradecards(hands,&rodada);
        printf("Suas cartas ficaram assim apos a troca:\n");
        imprime_hand(hands);
        atribui_peso(hands);
        start=start_game(hands);
        system("pause");
        for(fim_turno=0;fim_turno<13;fim_turno++){
            jogada(hands,&start,fim_turno,placar_rodada);
        }
        contabiliza(placar,placar_rodada);
        fim_jogo=analisa_game(placar);
    }
    imprime_placar(placar);
    libera(baralho,hands,placar);
    return 0;
}
int *placar_ini(){
    int *temp,i;
    temp=(int*)malloc(4*sizeof(int));
    for(i=0;i<4;i++){
        temp[i]=0;
    }
    return temp;
}
int **inicializa(){
    int i,j,**baralho;
    baralho=(int**)malloc(4*sizeof(int*)); /*Quatro naipes*/
    for(i=0;i<4;i++){
        baralho[i]=(int*)malloc(13*sizeof(int));/*13 tipos de cartas*/
        for(j=0;j<13;j++){
            baralho[i][j]=1; /*1 ela ainda está no baralho, -1 ela foi retirada*/
        }
    }
    return baralho;
}
int ***hand_ini(int **baralho){
    int jogador,carta,naipe,valor,cond=0,***hands;
    hands=(int***)malloc(4*sizeof(int**)); /*Quatro jogadores sendo i=0 o HUMAN*/
    for(jogador=0;jogador<4;jogador++){
        hands[jogador]=(int**)malloc(13*sizeof(int*));/*13 cartas para cada jogador*/
        for(carta=0;carta<13;carta++){
            cond=0;
            hands[jogador][carta]=(int*)malloc(3*sizeof(int));/*k=0 indica o naipe k=1 indica o valor*/
            /*Sorteia uma carta do baralho que ainda existe*/
            while(cond==0){
                naipe=rand()%4;
                valor=rand()%13;
                if(baralho[naipe][valor]==1){
                    baralho[naipe][valor]=-1;
                    cond=1;
                }
            }
            hands[jogador][carta][0]=naipe;
            hands[jogador][carta][1]=valor;
            hands[jogador][carta][2]=0;
        }
    }
    organiza_hands(hands);
    return hands;
}
int **mesa_ini(){
    int jogador,j,**mesa;
    mesa=(int**)malloc(4*sizeof(int*));
    for(jogador=0;jogador<4;jogador++){
        mesa[jogador]=(int*)malloc(2*sizeof(int));
        for(j=0;j<2;j++){
            mesa[jogador][j]=-1;
        }
    }
    return mesa;
}
void organiza_hands(int ***hands){
    int jogador,carta,cond,temp;
    /*organiza a mão por naipe e depois por valor*/
    for(jogador=0;jogador<4;jogador++){
        cond=0;
        while(cond==0){/*Enquanto nao estiver em ordem faça a ordenação*/
            cond=1; /*inicialmente está em ordem*/
            for(carta=0;carta<13-1;carta++){
                if(hands[jogador][carta][0]>hands[jogador][carta+1][0]){ /*Se o naipe estiver fora de ordem*/
                    /*troca naipe*/
                    temp=hands[jogador][carta][0];
                    hands[jogador][carta][0]=hands[jogador][carta+1][0];
                    hands[jogador][carta+1][0]=temp;
                    /*troca o valor*/
                    temp=hands[jogador][carta][1];
                    hands[jogador][carta][1]=hands[jogador][carta+1][1];
                    hands[jogador][carta+1][1]=temp;
                    cond=0; /*house troca portanto não estava em ordem*/
                }
                if(hands[jogador][carta][0]==hands[jogador][carta+1][0]&&hands[jogador][carta][1]>hands[jogador][carta+1][1]){ /*Se o valor estiver fora de ordem*/
                    /*troca naipe*/
                    temp=hands[jogador][carta][0];
                    hands[jogador][carta][0]=hands[jogador][carta+1][0];
                    hands[jogador][carta+1][0]=temp;
                    /*troca o valor*/
                    temp=hands[jogador][carta][1];
                    hands[jogador][carta][1]=hands[jogador][carta+1][1];
                    hands[jogador][carta+1][1]=temp;
                    cond=0;
                }
            }
        }
    }
}
void atribui_peso(int ***hands){
    int jogador,carta,naipe[4][4],i,j;
    /*zerando*/
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            naipe[i][j]=0;
        }
    }
    /*vendo cada carta de cada jogador*/
    for(jogador=0;jogador<4;jogador++){
        /*Veja quantas cartas tem de cada naipe de cada jogador*/
        for(carta=0;carta<13;carta++){
            naipe[jogador][hands[jogador][carta][0]]++;
        }
        /*Calculando o peso de cada carta: 3*quantidade de carta do naipe + valor da carta*/
        for(carta=0;carta<13;carta++){
            hands[jogador][carta][2]+=hands[jogador][carta][1];
            hands[jogador][carta][2]+=(3*(13-naipe[jogador][hands[jogador][carta][0]]));
        }
    }
}
void imprime_hand(int ***hands){
    int carta,jogador;
    for(jogador=0;jogador<4;jogador++){

    printf("jogador %d\n",jogador+1);
    for(carta=0;carta<13;carta++){
        printf("%2d - ",carta);
        if(hands[jogador][carta][0]!=-1) reconhece_cartas(hands[jogador][carta][0],hands[jogador][carta][1]);
        else printf("\n");
    }
    }
}
void imprime_placar(int *placar){
    int jogador;
    system("cls");
    printf("/----PLACA:----/\n");
    for(jogador=0;jogador<4;jogador++){
        printf("Jogador %d: %d\n",jogador+1,placar[jogador]);
    }
    system("pause");
}
int start_game(int ***hands){
    int jogador,carta,cond=0;;
    for(jogador=0;jogador<4;jogador++){
        for(carta=0;carta<13;carta++){
            if(hands[jogador][carta][0]==0&&hands[jogador][carta][1]==0){ /*Verifica se é o 2 de Paus*/
               cond=1;
               break;
            }
        }
        if(cond==1) break;
    }
    return jogador;
}
int turn_winner(int **mesa,int start,int *placar){
    int jogador,winner,count=0;
    winner=start;
    for(jogador=0;jogador<4;jogador++){
        if(mesa[jogador][0]==3) count++;
        if(mesa[jogador][0]==2&&mesa[jogador][1]==10) count+=13;
        if(mesa[jogador][0]==mesa[start][0]){
            if(mesa[jogador][1]>mesa[winner][1]) winner=jogador;
        }
    }
    placar[winner]+=count;
    printf("O jogador %d venceu o turno\n",winner+1);
    return winner;
}
int analisa_game(int *placar){
    int i,min=100,fim=0;
    for(i=0;i<4;i++){
        if(i!=0&&placar[i]<min) min=placar[i];
        if(placar[i]>100)fim=1;
    }
    if(fim==1){
        if(placar[0]>min) printf("Voce perdeu\n");
        else printf("Voce ganhou, parabens!\n");
        return 1;
    }
    return 0;
}
int maximo_peso(int ***hands,int jogador,int naipe,int max_valor){
    int carta,ind,max=0;
    if(naipe==-1){ /*Sem requisito de ser um naipe específico*/
        for(carta=0;carta<13;carta++){
            /*se a carta ainda existe e for maior que o maximo*/
            if(hands[jogador][carta][0]!=-1&&hands[jogador][carta][2]>max){
                max=hands[jogador][carta][2];
                ind=carta;
            }
        }
    }
    else{/*Precisa ser do naipe da varável naipe*/
        if(max_valor==-1){/*Pode se qualquer carta do naipe*/
            for(carta=0;carta<13;carta++){
                /*se a carta ainda existe e for maior que o maximo e do mesmo naipe*/
                if(hands[jogador][carta][0]!=-1&&hands[jogador][carta][2]>max&&hands[jogador][carta][0]==naipe){
                    max=hands[jogador][carta][2];
                    ind=carta;
                }
            }
        }
        else{/*Tem um valor maximo dentro no naipe*/
            for(carta=0;carta<13;carta++){
                /*se a carta ainda existe e for maior que o maximo e do mesmo naipe*/
                if(hands[jogador][carta][0]!=-1&&hands[jogador][carta][2]>max&&hands[jogador][carta][0]==naipe&&hands[jogador][carta][1]<max_valor){
                    max=hands[jogador][carta][2];
                    ind=carta;
                }
            }
        }
    }
    return ind;
}
void reconhece_cartas(int naipe,int valor){
    switch(valor){
        case 0: printf("Dois de ");
        break;
        case 1: printf("Tres de ");
        break;
        case 2: printf("Quatro de ");
        break;
        case 3: printf("Cinco de ");
        break;
        case 4: printf("Seis de ");
        break;
        case 5: printf("Sete de ");
        break;
        case 6: printf("Oito de ");
        break;
        case 7: printf("Nove de ");
        break;
        case 8: printf("Dez de ");
        break;
        case 9: printf("Valete de ");
        break;
        case 10: printf("Dama de ");
        break;
        case 11: printf("Rei de ");
        break;
        case 12: printf("As de ");
        break;
    }
    switch(naipe){
        case 0: printf("Paus\n");
        break;
        case 1: printf("Ouros\n");
        break;
        case 2: printf("Espadas\n");
        break;
        case 3: printf("Copas\n");
        break;
    }
}
void tradecards(int ***hands,int *rodada){
    int ***card,jogador,carta,count;
    card=(int***)malloc(4*sizeof(int**));
    for(jogador=0;jogador<4;jogador++){
        card[jogador]=(int**)malloc(3*sizeof(int*));
        for(carta=0;carta<3;carta++){
            card[jogador][carta]=(int*)malloc(2*sizeof(int));
        }
    }
    if(*rodada!=3){ /*Apenas no rodada 0,1,2 há troca de cartas*/
        /*Processo de escolha das tres cartas*/
        for(jogador=0;jogador<4;jogador++){
            if(jogador==0){
                printf("Escolha tres cartas para trocar\n");
                for(count=0;count<3;count++){
                    printf("Escolha %d carta:",count+1);
                    scanf("%d",&carta);
                    /*retira a carta da mão e coloca na matriz card*/
                    card[jogador][count][0]=hands[jogador][carta][0];
                    card[jogador][count][1]=hands[jogador][carta][1];
                    hands[jogador][carta][0]=-1;
                    hands[jogador][carta][1]=-1;
                }
            }
            else trade_AI(hands,card,jogador);
        }
        troca_move(hands,card,*rodada);
        (*rodada)++;
    }
    else *rodada=0;/*Se for igual a tres então não há troca apenas zera a rodada*/
    organiza_hands(hands);
}
void troca_move(int ***hands, int ***card,int rodada){
    int jogador, carta,count;
    for(jogador=0;jogador<4;jogador++){
        count=0;
        for(carta=0;carta<13;carta++){
            if(hands[jogador][carta][0]==-1){ /*Ou seja não há carta naquela posição*/
                hands[jogador][carta][0]=card[(jogador+rodada+1)%4][count][0];
                hands[jogador][carta][1]=card[(jogador+rodada+1)%4][count][1];
                count++;
            }
        }
    }
}
void trade_AI(int ***hands,int ***card,int jogador){
    int count,ind;
    for(count=0;count<3;count++){
        ind=maximo_peso(hands,jogador,-1,-1);
        card[jogador][count][0]=hands[jogador][ind][0];
        card[jogador][count][1]=hands[jogador][ind][1];
        hands[jogador][ind][0]=-1;
        hands[jogador][ind][1]=-1;
    }
}
void jogada(int ***hands,int *start,int fim_turno,int *placar_rodada){
    int jogador,**mesa,carta,volta=0,cond=0,naipe[4],i;
    mesa=mesa_ini();
    system("cls");
    imprime_hand(hands);
    printf("O jogador %d abre\n",(*start)+1);
    /*Veja quantas cartas tem de cada naipe*/
    for(i=0;i<4;i++){naipe[i]=0;}
    for(carta=0;carta<13-1;carta++){
        naipe[hands[0][carta][0]]++;
    }
    /*Começando o turno por quem venceu o anterior*/
    for(jogador=*start;jogador<4;jogador++){
        if(jogador==0){
            while(cond==0){
                printf("Escolha uma carta para jogar:");
                scanf("%d",&carta);
                if(hands[0][carta][0]!=-1){ /*Vendo se a carta existe*/
                    if(naipe[mesa[(*start)][0]]>0){ /*vendo se tem alguma carta com o mesmo naipe de quem começou*/
                        if(hands[0][carta][0]==mesa[*start][0]||(*start)==0){
                            mesa[jogador][0]=hands[jogador][carta][0];
                            mesa[jogador][1]=hands[jogador][carta][1];
                            hands[jogador][carta][0]=-1;
                            hands[jogador][carta][1]=-1;
                            cond=1;
                        }
                        else printf("Jogada ilegal\n");
                    }
                    else{
                        mesa[jogador][0]=hands[jogador][carta][0];
                        mesa[jogador][1]=hands[jogador][carta][1];
                        hands[jogador][carta][0]=-1;
                        hands[jogador][carta][1]=-1;
                        cond=1;
                    }
                }
                else printf("Nao existe esse indice\n");
            }
        }
        else jogada_AI(hands,mesa,jogador,*start,fim_turno);
        if(volta==0&&jogador==3){
            volta=1;
            jogador=-1;
        }
        if(volta==1&&jogador==(*start)-1) break;
    }
    *start=turn_winner(mesa,*start,placar_rodada);
    system("pause");
}
void jogada_AI(int ***hands,int **mesa,int jogador,int start,int fim_turno){
    int naipe[4],carta,i,max_valor=0,ind;
    /*vendo qual valro máximo*/
    for(i=0;i<4;i++){
        if(mesa[i][0]==mesa[start][0]&&mesa[i][0]>max_valor) max_valor=mesa[i][0];
    }
    /*contando quantas cartas tem cada naipe*/
    for(i=0;i<4;i++){naipe[i]=0;}
    for(carta=0;carta<13-1;carta++){
        naipe[hands[jogador][carta][0]]++;
    }
    /*Escolhendo a carta e colocando na mesa*/
    if(jogador==start){ /*Jogador vai abrir o turno*/
        if(fim_turno==0){ /*É o primeiro turno, neste caso 2 de Paus*/
            mesa[jogador][0]=hands[jogador][0][0];
            mesa[jogador][1]=hands[jogador][0][1];
            hands[jogador][0][0]=-1;
            hands[jogador][0][1]=-1;
        }
        else{  /*Não é o primeiro turno, neste caso jogar a carta mais baixa*/
            for(carta=0;carta<13;carta++){
                if(hands[jogador][carta][0]!=-1){
                    mesa[jogador][0]=hands[jogador][carta][0];
                    mesa[jogador][1]=hands[jogador][carta][1];
                    hands[jogador][carta][0]=-1;
                    hands[jogador][carta][1]=-1;
                    break;
                }
            }
        }
    }
    else{ /*Jogador nao começa, neste caso verificar se tem naipe rpa responder*/
        if(naipe[mesa[start][0]]>0){ /*Possui carta pra responder */
            if(fim_turno==0){ /*É o primeiro turno, neste caso responder maior de Paus*/
                ind=maximo_peso(hands,jogador,0,-1);
                mesa[jogador][0]=hands[jogador][ind][0];
                mesa[jogador][1]=hands[jogador][ind][1];
                hands[jogador][ind][0]=-1;
                hands[jogador][ind][1]=-1;
                hands[jogador][ind][2]=-1;
            }
            else{  /*Não é o primeiro turno, neste caso jogar abaixo do que jah tem na mesa*/
                ind=maximo_peso(hands,jogador,mesa[start][0],max_valor);
                mesa[jogador][0]=hands[jogador][ind][0];
                mesa[jogador][1]=hands[jogador][ind][1];
                hands[jogador][ind][0]=-1;
                hands[jogador][ind][1]=-1;
                hands[jogador][ind][2]=-1;
            }
        }
        else{ /*Não possui carta pra responder*/
            if(fim_turno==0){ /*É o primeiro turno, neste caso responder maior peso, exceto Copas ou Damas de Espadas*/
                if(hands[jogador][maximo_peso(hands,jogador,-1,-1)][0]==3||(hands[jogador][maximo_peso(hands,jogador,-1,-1)][0]==2&&
                hands[jogador][maximo_peso(hands,jogador,-1,-1)][1]==10)){
                    if(naipe[2]>0){ /*Joga uma de Ouros*/
                        ind=maximo_peso(hands,jogador,1,-1);
                        mesa[jogador][0]=hands[jogador][ind][0];
                        mesa[jogador][1]=hands[jogador][ind][1];
                        hands[jogador][ind][0]=-1;
                        hands[jogador][ind][1]=-1;
                        hands[jogador][ind][2]=-1;
                    }
                    else{/*Joga de Espadas*/
                        ind=maximo_peso(hands,jogador,2,-1);
                        mesa[jogador][0]=hands[jogador][ind][0];
                        mesa[jogador][1]=hands[jogador][ind][1];
                        hands[jogador][ind][0]=-1;
                        hands[jogador][ind][1]=-1;
                        hands[jogador][ind][2]=-1;
                    }
                }
                else{
                    ind=maximo_peso(hands,jogador,-1,-1);
                    mesa[jogador][0]=hands[jogador][ind][0];
                    mesa[jogador][1]=hands[jogador][ind][1];
                    hands[jogador][ind][0]=-1;
                    hands[jogador][ind][1]=-1;
                    hands[jogador][ind][2]=-1;
                }
            }
            else{ /*Não é o primeiro turno, neste caso jogar carta de maior peso*/
                ind=maximo_peso(hands,jogador,-1,-1);
                mesa[jogador][0]=hands[jogador][ind][0];
                mesa[jogador][1]=hands[jogador][ind][1];
                hands[jogador][ind][0]=-1;
                hands[jogador][ind][1]=-1;
                hands[jogador][ind][2]=-1;
            }
        }
    }
    printf("Jogador %d jogou ",jogador+1);
    reconhece_cartas(mesa[jogador][0],mesa[jogador][1]);
}
void libera(int **baralho,int ***hands,int *placar){
    int i,j;
    for(i=0;i<4;i++){
        free(baralho[i]);
        for(j=0;j<13;j++){
            free(hands[i][j]);
        }
        free(hands[i]);
    }
    free(baralho);
    free(hands);
    free(placar);
}
void contabiliza(int *placar,int *placar_rodada){
    int jogador, moon=-1;
    for(jogador=0;jogador<4;jogador++){
        if(placar_rodada[jogador]==26) moon=jogador; /*Veja se alguém conseguiu fazer a lua, e marca o jogador*/
    }
    if(moon==-1){ /*Se não tiver alguém que consegui fazer a lua*/
        for(jogador=0;jogador<4;jogador++){
            placar[jogador]+=placar_rodada[jogador]; /*Soma normal*/
        }
    }
    else{ /*Caso contrario*/
        for(jogador=0;jogador<4;jogador++){
            if(jogador!=moon) placar[jogador]+=26; /*Todos ,exceto o jogador que fez a lua, soma 26*/
        }
    }
}
