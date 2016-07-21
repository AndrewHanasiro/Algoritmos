/*a e b sao numeros, d=mdc(a,b),m=mmc(a,b)*/
#include<stdio.h>
int main(){
    int a ,b,d,m,resto=1,nume,divi;
    printf("Digite dois numeros, separado por espaco:");
    scanf("%d %d",&a,&b);
    if(a>b){
        nume=a;
        divi=b;
    }
    else{
        nume=b;
        divi=a;
    }
    resto=nume%divi;
    while(resto!=0){
        nume=divi;
        divi=resto;
        resto=nume%divi;
    }
    d=divi;
    m=a*b/d;
    printf("mdc(%d,%d)=%d\n",a,b,d);
    printf("mmc(%d,%d)=%d\n",a,b,m);
    return 0;
}
