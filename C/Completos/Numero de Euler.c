#include<stdio.h>

int main(){
    float num=0, comeco=0, aumento=0, limite=0, temp=1;
    int i=0;
    printf("Estudo sobre o Numero de Euler que e´expressado por:\nlimite n->limite de(1+1/n)^n\n\n");
    printf("Digite um numero (n) inicial:");
    scanf("%f",&comeco);
    printf("Digite um numero para o limite:");
    scanf("%f",&limite);
    printf("Digite o aumento (inicial+aumento):");
    scanf("%f",&aumento);
    for(num=comeco;num<limite;num+=aumento){
        temp=1;
        for(i=0;i<num;i++){
            temp*=(1+(1/num));
        }
        printf("%f\n",temp);
    }
    return 0;
}
