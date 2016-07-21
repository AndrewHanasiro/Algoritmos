#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int sex; /*1-Man,2-Woman*/
    char name[20];
    int life;
    int attack;/*ataque fisico*/
    int endurance;/*defesa, quanto maior, meno dano vc toma*/
    int mana;/*ataque magico*/
    int skill;/*ataque preciso*/
    int level; /*baseado na soma de todos os XP*/
    int XPattack; /*Quanto mais vc usar ataque fisico, mais o dano fisico aumenta*/
    int XPmana;/*Quanto mais vc usar magia, mais o dano mágico aumenta*/
    int XPskill;/*Quanto mais vc usar ataque preciso, mais o dano aumenta*/
    int story; /*por enquanto nao tem historia*/
    int type;/*1-Warrior,2-Rogue,3-Mage*/
}Player;
typedef struct{
    int life;
    int attack;
    int endurance;
    int mana;
    int skill;
    int level;
}Enemy;
/*Funções*/
Player *newgame(Player *Profile);
Player *loadgame(Player *Profile);
void savegame(Player *Profile);
void credits();
void chapter0(Player *Profile,int *end);
void imprimestatus(Player *Profile, Enemy *enemyX);
Enemy *createenemy(Player *Profile,Enemy *EnemyX);
Player *battle(Player *Profile,Enemy *enemyX);
int openspecial(Player *Profile);
Player *levelup(Player *Profile);
int main(){
    int escolha,end=0;
    Player *Profile;
    while(end==0){
        printf("Welcome to Pro7RPG\n");
        printf("1-New Game\n");
        printf("2-Load Game\n");
        printf("3-Credits\n");
        printf("4-Exit\n");
        scanf("%d",&escolha);
        fflush(stdin);
        switch(escolha){
            case 1:Profile=newgame(Profile);
            break;
            case 2:Profile=loadgame(Profile);
            break;
            case 3:credits();
            break;
            case 4:end=1;
            break;
            default: printf("Escolha uma das opcoes!Noob");
        }
        while(end==0){
            chapter0(Profile,&end);
        }
    }
    return 0;
}
Player *newgame(Player *Profile){
    Player *Profile_temp=Profile;
    Profile_temp=(Player*)malloc(sizeof(Player));
    /*Iniciar profile padrão*/
    Profile_temp->life=100;
    Profile_temp->attack=0;
    Profile_temp->endurance=0;
    Profile_temp->mana=0;
    Profile_temp->skill=0;
    Profile_temp->level=1;
    Profile_temp->XPattack=0;
    Profile_temp->XPmana=0;
    Profile_temp->XPskill=0;
    Profile_temp->story=0;
    /*Vendo o Sexo*/
    printf("1-Homen,+defesa +ataque\n2-Mulher,+mana,+foco\nEscolha o sexo:");
    scanf("%d",&Profile_temp->sex);
    fflush(stdin);
    switch(Profile_temp->sex){
        case 1:{
            Profile_temp->attack+=10;
            Profile_temp->endurance+=10;
        }
        break;
        case 2:{
            Profile_temp->mana+=10;
            Profile_temp->skill+=10;
        }
        break;
    }
    /*Vendo o Nome*/
    printf("Qual seu nome:");
    scanf("%s",Profile_temp->name);
    fflush(stdin);
    /*Vendo o tipo de personagem*/
    printf("1-Warrior, +ataque e +defesa\n");
    printf("2-Stealth, +ataque,+foco\n");
    printf("3-Combat Mage,+ataque +mana\n");
    printf("4-Constructor,+endurance +mana\n");
    printf("5-Evoque,+endurance +skill\n");
    printf("6-Classic Mage,+mana,+foco\n");
    printf("Escolha o tipo de personagem:");
    scanf("%d",&Profile_temp->type);
    fflush(stdin);
    switch(Profile_temp->type){
        case 1:{
            Profile_temp->attack+=10;
            Profile_temp->endurance+=10;
            Profile_temp->mana+=5;
            Profile_temp->skill+=5;
        }
        break;
        case 2:{
            Profile_temp->attack+=10;
            Profile_temp->endurance+=5;
            Profile_temp->mana+=5;
            Profile_temp->skill+=10;
        }
        break;
        case 3:{
            Profile_temp->attack+=10;
            Profile_temp->endurance+=5;
            Profile_temp->mana+=10;
            Profile_temp->skill+=5;
        }
        break;
        case 4:{
            Profile_temp->attack+=5;
            Profile_temp->endurance+=10;
            Profile_temp->mana+=10;
            Profile_temp->skill+=5;
        }
        break;
        case 5:{
            Profile_temp->attack+=5;
            Profile_temp->endurance+=10;
            Profile_temp->mana+=5;
            Profile_temp->skill+=10;
        }
        break;
        case 6:{
            Profile_temp->attack+=5;
            Profile_temp->endurance+=5;
            Profile_temp->mana+=10;
            Profile_temp->skill+=10;
        }
        break;
    }
    savegame(Profile_temp);
    return Profile_temp;
}
void savegame(Player *Profile){
    FILE *arquivo;
    arquivo=fopen("savegame.txt","w");
    fprintf(arquivo,"%d\n",Profile->sex);
    fprintf(arquivo,"%s\n",Profile->name);
    fprintf(arquivo,"%d\n",Profile->life);
    fprintf(arquivo,"%d\n",Profile->attack);
    fprintf(arquivo,"%d\n",Profile->endurance);
    fprintf(arquivo,"%d\n",Profile->mana);
    fprintf(arquivo,"%d\n",Profile->skill);
    fprintf(arquivo,"%d\n",Profile->level);
    fprintf(arquivo,"%d\n",Profile->XPattack);
    fprintf(arquivo,"%d\n",Profile->XPmana);
    fprintf(arquivo,"%d\n",Profile->XPskill);
    fprintf(arquivo,"%d\n",Profile->story);
    fprintf(arquivo,"%d\n",Profile->type);
    fclose(arquivo);
    printf("game salvo\n");
}
Player *loadgame(Player *Profile){
    FILE *arquivo;
    Player *Profile_temp=Profile;
    Profile_temp=(Player*)malloc(sizeof(Player));
    arquivo=fopen("savegame.txt","r");
    fscanf(arquivo,"%d",&Profile_temp->sex);
    fscanf(arquivo,"%s",Profile_temp->name);
    fscanf(arquivo,"%d",&Profile_temp->life);
    fscanf(arquivo,"%d",&Profile_temp->attack);
    fscanf(arquivo,"%d",&Profile_temp->endurance);
    fscanf(arquivo,"%d",&Profile_temp->mana);
    fscanf(arquivo,"%d",&Profile_temp->skill);
    fscanf(arquivo,"%d",&Profile_temp->level);
    fscanf(arquivo,"%d",&Profile_temp->XPattack);
    fscanf(arquivo,"%d",&Profile_temp->XPmana);
    fscanf(arquivo,"%d",&Profile_temp->XPskill);
    fscanf(arquivo,"%d",&Profile_temp->story);
    fscanf(arquivo,"%d",&Profile_temp->type);
    fclose(arquivo);
    return Profile_temp;
}
void chapter0(Player *Profile,int *end){
    Enemy *EnemyX;
    int fim=0;
    while(fim==0){
        printf("Começou uma batalha!!\n");
        EnemyX=createenemy(Profile,EnemyX);
        Profile=battle(Profile,EnemyX);
        printf("1-SIM\n0-NAO\nDeseja sair:");
        scanf("%d",&fim);
    }
    *end=fim;
    savegame(Profile);
}
Enemy *createenemy(Player *Profile,Enemy *EnemyX){
    Enemy *EnemyX_temp=EnemyX;
    EnemyX_temp->life=(Profile->life)-rand()%20;
    EnemyX_temp->attack=(Profile->attack)-rand()%5;
    EnemyX_temp->endurance=(Profile->endurance)-rand()%5;
    EnemyX_temp->mana=(Profile->mana)-rand()%5;
    EnemyX_temp->skill=(Profile->skill)-rand()%5;
    EnemyX_temp->level=Profile->level;
    return EnemyX_temp;
}
Player *battle(Player *Profile,Enemy *EnemyX){
    int choose=0,endbattle=0,damage;
    Profile->life=100;
    while(endbattle==0){
        if(Profile->life>0&&endbattle==0){
            RETORNO:
            imprimestatus(Profile,EnemyX);
            printf("-----//MENU//-----\n");
            printf("1-Ataque Fisico Normal\n");
            printf("2-Ataque com Magia\n");
            printf("3-Ataque que precisa de foco\n");
            printf("4-Abrir Habilidades Especial\n");
            if(rand()%2==0){
                scanf("%d",&choose);
                switch(choose){
                    case 1:{
                        damage=(Profile->attack)-EnemyX->endurance/(EnemyX->life);
                        Profile->XPattack++;
                    }
                    break;
                    case 2:{
                        damage=(Profile->mana)-(EnemyX->endurance)/(EnemyX->life);
                        Profile->XPmana++;
                    }
                    break;
                    case 3:{
                        damage=(Profile->skill)-EnemyX->endurance/(EnemyX->life);
                        Profile->XPskill+=1;
                    }
                    break;
                    case 4:{
                        damage=(openspecial(Profile))-EnemyX->endurance/(EnemyX->life);
                        if(damage==0) goto RETORNO;
                    }
                    break;

                }
                printf("voce deu %d de dano",damage);
                EnemyX->life-=damage;
            }
            else printf("voce errou\n");
        }
        else{
            endbattle=1;
            printf("voce morreu\n");
        }
        /*Contra ataque*/
        if(EnemyX->life>0&&endbattle==0){
            if(rand()%2==0){
                choose=rand()%4;
                switch(choose){
                    case 1: damage=(EnemyX->attack)-(Profile->endurance)/(Profile->life);
                    break;
                    case 2: damage=(EnemyX->mana)-(Profile->endurance)/(Profile->life);
                    break;
                    case 3: damage=(EnemyX->skill)-(Profile->endurance)/(Profile->life);
                    break;
                }
                printf("voce recebeu %d de dano\n",damage);
                Profile->life-=damage;
            }
            else printf("Ele errou, mas que sorte\n");
        }
        else{
            if(EnemyX->life<=0){
                endbattle=1;
                printf("Voce ganhou\n");
                Profile=levelup(Profile);
            }
        }
    }
    return Profile;
}
int openspecial(Player *Profile){
    int escolha;
    printf("1-Super Chute(-2XP)\n");
    printf("2-Explosao(-2XP)\n");
    printf("3-Ponto fraco(-2XP)\n");
    scanf("%d",&escolha);
    switch(escolha){
        case 1:{
            Profile->XPattack-=2;
            return Profile->attack+10;
        }
        break;
        case 2:{
            Profile->XPmana-=2;
            return Profile->mana+10;
        }
        break;
        case 3:{
            Profile->XPskill-=2;
            return Profile->skill+10;
        }
        break;
        default: printf("Escolha uma delas\n");
    }
    return 0;
}
Player *levelup(Player *Profile){
    if(Profile->XPattack>(Profile->level)*10) Profile->attack+=Profile->level;
    if(Profile->XPmana>(Profile->level)*10) Profile->mana+=Profile->level;
    if(Profile->XPskill>(Profile->level)*10) Profile->skill+=Profile->level;
    if((Profile->XPattack)+(Profile->XPmana)+(Profile->XPskill)>Profile->level*100) Profile->level+=1;
    return Profile;
}
void imprimestatus(Player *Profile, Enemy *enemyX){
    printf("--//Voce://--\n");
    printf("Vida=%d\n",Profile->life);
    printf("Ataque=%d\n",Profile->attack);
    printf("Defesa=%d\n",Profile->endurance);
    printf("Mana=%d\n",Profile->mana);
    printf("Foco=%d\n",Profile->skill);
    printf("Nivel=%d\n",Profile->level);
    printf("--//Inimigo://--\n");
    printf("Vida=%d\n",enemyX->life);
    printf("Level=%d\n",enemyX->level);
}
void credits(){
    printf("Diretor:Andrew Kenji Hanasiro\n");
    printf("Programador:Andrew Kenji Hanasiro\n");
}
