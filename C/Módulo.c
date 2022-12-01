#include <stdio.h>
float modulo(float *n){
    float k;
    k=*n;
    if(*n<0) return -k;
    else return k;
}
int main()
{
    float x, n;
    printf("digite um numero:");
    scanf("%f", &x);
    n=modulo(&x);
    printf("%f", n);
    return 0;
}
