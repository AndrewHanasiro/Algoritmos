#include<stdio.h>
int potencia(int base, int quantidade, int potencia){
    int i=0,temp=1;
    for(i=1;i<=potencia;i++){
        temp*=base;
    }
    temp*=quantidade;
    return temp;
}
int main(){
    int valor=0, q0=0, q1=0, q2=0, q3=0, letra=0, continuar=0, validade=0;    
    while(continuar==0){
        validade=0;
        while(validade==0){
            printf("Entre com uma numero binario:");
            scanf("%d", &valor);              
            q3=(valor-(valor%1000))/1000;
            q2=((valor-(valor%100))/100)-q3*10;
            q1=(valor-(valor%10))/10-q3*100-q2*10;
            q0=(valor-(valor%1))/1-q3*1000-q2*100-q1*10;      
            if(q3==0||q3==1) validade=1; else validade=0;
            if(q2==0||q2==1) validade=1; else validade=0;
            if(q1==0||q1==1) validade=1; else validade=0;
            if(q0==0||q0==1) validade=1; else validade=0;
            if(validade==0) printf("Entra com uma valor normal porra\n\n");
            else validade=1;
        }
        q3=potencia(2,q3,3);
        q2=potencia(2,q2,2);
        q1=potencia(2,q1,1);
        q0=potencia(2,q0,0);
        printf("\nNumero corespondente:%d",q3+q2+q1+q0);
        printf("\nDeseja sair S=0 ou N=1:");
        scanf("%d",&letra);
        if(letra==0) continuar=1;
    }    
    return 0;   
}
