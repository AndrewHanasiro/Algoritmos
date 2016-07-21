#include<stdio.h>
#include<stdlib.h>
int **inicializa(int tam){
    int i, j,**temp;
    temp=(int**)malloc(tam*sizeof(int*));
    for(i=0;i<tam;i++){
        temp[i]=(int*)malloc(tam*sizeof(int));
        for(j=0;j<tam;j++){
            temp[i][j]=rand()%50;
            if(j==0) printf("\n");
            printf("%2d ",temp[i][j]);
        }
    }
    return temp;
}
int confere(int **mat,int tam){
    int i, j,count,lim;
    /*verificando linha*/
    for(i=0;i<tam;i++){
        count=0;
        for(j=0;j<tam;j++){
            count+=mat[i][j];
        }
        if(i==0)lim=count;
        else{
            if(lim!=count) return 0;
        }
    }
    /*verificando coluna*/
    for(j=0;j<tam;j++){
        count=0;
        for(i=0;i<tam;i++){
            count+=mat[i][j];
        }
        if(lim!=count) return 0;
    }
    /*verificando diagonais*/
    j=0;
    count=0;
    for(i=0;i<tam;i++){
        count+=mat[i][j];
        j++;
    }
    if(lim!=count) return 0;
    j=tam-1;
    count=0;
    for(i=0;i<tam;i++){
        count+=mat[i][j];
        j--;
    }
    if(lim!=count) return 0;
    /*se deu nenhum return 0 então retorna 1*/
    return 1;
}
int main(){
    int tam,**mat;
    printf("Digite o tamanho do quadrado:");
    scanf("%d",&tam);
    mat=inicializa(tam);
    if(confere(mat,tam)) printf("\nSIM");
    else printf("\nNAO");
    return 0;
}
