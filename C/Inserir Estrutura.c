#include<stdio.h>
#include<stdlib.h>
typedef struct no{
    int info;
    struct no *prox;
}Lista;
void imprime(Lista *X){
    Lista *pt;
    for(pt=X;pt!=NULL;pt=pt->prox){
        printf("%d-",pt->info);
    }
    printf("\n");
}
Lista *insere_return(Lista *A,int x){
    Lista *temp;
    temp=(Lista*)malloc(sizeof(Lista));
    temp->info=x;
    temp->prox=A;
    return temp;
}
void insere_void(Lista **B,int x){
    Lista *temp;
    temp=(Lista*)malloc(sizeof(Lista)); /*Aloca um espaço na memória*/
    temp->info=x;
    temp->prox=*B;
    *B=temp;
}
int main(){
    int x;
    Lista *A,*B;
    B=NULL;
    A=NULL;
    x=1;
    A=insere_return(A,x);
    x=2;
    A=insere_return(A,x);
    x=3;
    insere_void(&B,x);
    x=4;
    insere_void(&B,x);
    imprime(A);
    imprime(B);
    return 0;

}
