#include<stdio.h>
#define MAX 50
int fibonacci(int quant,int menor,int maior){
    maior+=menor;
    if(quant>0) return fibonacci(quant-1,maior,menor);
    else return menor;
}
int main(){
    int quant;
    printf("%d",fibonacci(MAX-1,1,0));
    return 0;
}
/*1,1,2,3,5,8,13,21*/
