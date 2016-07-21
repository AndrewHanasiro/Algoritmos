#include <stdio.h>

int main()
{
    int n, count, i;
    printf("Digite quantos impares deseja aparecer:");
    scanf("%d", &n);
    count=0;
    for(i=-1;count<n;count++)
    {
        i+=2;
        printf("%d ", i);
    }
    return 0;
}
