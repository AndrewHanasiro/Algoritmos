#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float a, b, c, r1, r2, delta, deltar;
    printf("Digite os coeficientes do maior grau ate o termo independente,\nseparados por espaco\n\n");
    scanf("%f %f %f", &a, &b, &c);
    delta=(b*b)-(4*a*c);
    deltar = sqrt(delta);
    printf("\ndelta e igual a %f\n", deltar);
    if(deltar>=0){
        r1=(-b+deltar)/2;
        r2=(-b-deltar)/2;
        printf("As raizes sao %f %f\n\n", r1, r2);
    }
    else printf("raizes nao sao reais");
    return 0;
}
