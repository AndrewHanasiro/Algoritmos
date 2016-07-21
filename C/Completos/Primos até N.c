#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n=2, i, lim, cond;
    printf("Digite um numero:");
    scanf("%d", &lim);
    while (n<=lim){
        cond=0;
        for(i=2;i<n;i++){
            if(n%i==0){
                cond=1;
                break;
            }
        }
        if(cond==0){
            printf("%d ", n);
        }
        n++;
    }
    printf("\n\n");
    system("pause");
    return 0;
}
