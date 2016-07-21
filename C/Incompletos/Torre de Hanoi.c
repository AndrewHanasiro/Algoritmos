#include<stdio.h>
#include<stdlib.h>
typedef struct h{
    int *vet
    int topo
}Haste;
int main(){
    int tam=5;
    Haste *orig,*temp,*dest
    orig=inicia(tam);
    temp=inicia(tam);
    dest=inicia(tam);
}
Haste *inicia(int tam){
    Haste *temp=(Haste*)malloc(sizeof(Haste));
    temp->vet=(int*)malloc(tam*sizeof(int));
    temp->topo=-1;
}
