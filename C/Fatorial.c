#include <stdio.h>
int fatorial(int n){
    if(n==1) return n;
    else{
        return (n*fatorial(n-1));
    }
}
int main(){
    int prod1=1,prod2,i,n;
    printf("Digite um numero:");
    scanf("%d", &n);
    /*1� jeito*/
    for(i=1;i<=n;i++){
        prod1*=i;
    }
    printf("\n1 metodo: %d", prod1);
    /*2� jeito*/
    prod2=fatorial(n);
    printf("\n2 metodo: %d", prod2);
    return 0;
}
