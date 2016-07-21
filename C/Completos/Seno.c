#include<stdio.h>
#include<math.h>
#define PI  3.14159265358979323846264338327950288
double fatorial(double num){
    int i;
    double FAT=1;
    if(num==0) return 1;
    else{
        for(i=1;i<=num;i++){
            FAT*=i;
        }
    }
    return FAT;
}
int main(){
    double x,k,denominador,numerador,soma=0;
    int i,n,negpos;
    printf("Entre com um angulo, em graus:");
    scanf("%lf",&x);/*angulo*/
    printf("Entre com a quantidade de termos:");
    scanf("%d",&n);/*quantidade de termos*/
    x=PI*(x/180); /*Transformando em radianos*/
    for(i=0;i<n;i++){
        /*vendo se o termo é positivo ou negativo*/
        if(i%2==0) negpos=1;
        else negpos=-1;
        /*calculando o numerador e denominador*/
        k=2*i+1;
        numerador=pow(x,k);
        denominador=fatorial(k);
        /*atualizando o valor*/
        soma+=(double)negpos*numerador/denominador;
    }
    printf("Soma=%0.10f\n",soma);
    return 0;
}
