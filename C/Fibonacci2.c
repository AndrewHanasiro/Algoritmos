#include<stdio.h>
#define MAX 50
int fibonacci(int num){
    if(num<2) return num;
    else return (fibonacci(num-1)+fibonacci(num-2));
}
int main(){
    int quant;
    printf("%d",fibonacci(MAX));
    return 0;
}
/*1,1,2,3,5,8,13,21*/
