#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*ax^3 + b^x2 + cx + d = 0*/
/*Eeste programa segue o metodo de Tartaglia para soluções de esquções de 3º grau*/

int main()
{
    double a, b, c, d, p, q, m, a02, b02, a01, b01, U, r1, x, y, z, r2, r3, delta, deltar;
    printf("\nDigite os coeficientes do maior grau ate o termo independente,\nseparados por espaco\n\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("\na=%f, b=%f, c=%f e d=%f\n", a, b, c,d);
    p=(3*a*c-b*b)/3*a*a;
    q=(27*a*a*d-9*a*b*c+2*b*b*b)/27*a*a*a;
    m=(-1)*b/3*a;
    printf("\np=%f, q=%f e m=%f\n", p, q, m);
    U=sqrt ((q*q/4)+(p*p*p/27));
    a02=(-1)*p/2 + U;
    b02=(-1)*q/2 - U;
    a01=cbrt(a02);
    b01=cbrt(b02);
    r1=m+a01+b01;

    /*Sabendo agora uma das raízes, basta aplicar O dispositivo Briot-Ruffini para deixa a
    equação de terceiro grau em uam de segundo grau, tal que
    x, y e z sejam os coeficientes do maior grau
    até o termo independente: xt^2+yt+z=0*/

    x=a;
    y=r1*x+b;
    z=r1*y+c;
    delta=(y*y)-(4*x*z);
    deltar = sqrt (delta);
    r2=(-y+deltar)/2;
    r3=(-y-deltar)/2;
    printf("\nAs raizes sao:\nr1=%f\nr2=%f\nr3=%f\n", r1, r2, r3);
    system("PAUSE");
    return 0;
}
