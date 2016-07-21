#include<stdio.h>
void divisao(int nume,int divi,int precisao){
    int i, count;
    if(nume>=divi){
        count=0;
        while(nume>=divi){
            count++;
            nume-=divi;
        }
        printf("%d",count);
    }
    else printf("0");
    if(nume<divi){
        printf(".");
        for(i=0;i<precisao;i++){
            count=0;
            nume*=10;
            while(nume>=divi){
                count++;
                nume-=divi;
            }
            printf("%d",count);
        }
    }
}
int main(){
    int nume,divi,precisao;
    printf("Digite o numerador:");
    scanf("%d",&nume);
    printf("Digite o divisor:");
    scanf("%d",&divi);
    printf("Digite quantas casas de precisao:");
    scanf("%d",&precisao);
    divisao(nume,divi,precisao);
    return 0;
}
