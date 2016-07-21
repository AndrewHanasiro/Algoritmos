#include<stdio.h>
#include<stdlib.h>
void imprime(int **tab,int tam){
    int i,j;
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            if(j==0) printf("\n");
            if(tab[i][j]!=0) printf("%3d ",tab[i][j]);
        }
    }
}
void pascal(int tam){
    int i,j,**tab;
    tam++;
    tab=(int**)malloc(tam*sizeof(int*));
    for(i=0;i<tam;i++){
        tab[i]=(int*)malloc(tam*sizeof(int));
        for(j=0;j<tam;j++){
            tab[i][j]=0;
            if(j==0&&i>0) tab[i][j]=1;
        }
    }
    for(i=1;i<tam;i++){
        for(j=1;j<tam;j++){
            tab[i][j]=tab[i-1][j-1]+tab[i-1][j];
        }
    }
    imprime(tab,tam);
}
int main(){
    int tam;
    scanf("%d",&tam);
    pascal(tam);
    return 0;
}
