#include <stdio.h>
#include <stdlib.h>
int main(){
    int limite=0, cont=0, i, j=0, cond, num;
    int *primos;
    printf("Digite quantidade de primos:");
    scanf("%d", &limite);
    primos=(int*)malloc(limite*sizeof(int));
    primos[0]=2;
    cont++;
    printf("2\n");
    for(num=2;num<=limite;num++){
        cond=0;
        for(i=0;i<num;i++){
            if(num%primos[i]==0){
                cond=1;
                break;
            }
        }
        if(cond==0){
            printf("%d\n", num);
            j++;
            cont++;
            primos[j]=num;
        }
    }
    printf("Tem %d numeros primos ate %d\n", cont, limite);
    return 0;
}
