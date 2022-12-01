#include <stdio.h>

int main ()
{
    int n, i, count;
    printf("Digite a quantidade de pares:");
    scanf("%d", &n);
    count=0;
    for(i=0;count<n;count++)
    {
        i+=2;
        printf("%d ", i);
    }
    return 0;
}

