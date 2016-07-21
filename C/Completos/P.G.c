#include<stdio.h>

int main(){
    int termo1=0,razao=0,cont=0,multiplicador=1,j=0;
    printf("Digite o primeiro termo:");
    scanf("%d",&termo1);
    printf("\nDigite a razao:");
    scanf("%d",&razao);
    while(cont<20){
        multiplicador=1;
        for(j=0;j<cont;j++){
            multiplicador=multiplicador*razao;
        }
        printf("\ntermo %d: %d",cont, termo1*multiplicador);
        cont++;
    }
    return 0;
}
/*
multiplicador=1
multiplicador=razao
multiplicador=razao*razao
multiplicador=razao*razao*razao
*/
