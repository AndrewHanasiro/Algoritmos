#include<stdio.h>
#include<stdlib.h>
int **cheats(int **mat,int lin, int col){
    int i,j,count=1;
    for(i=0;i<lin;i++){
        for(j=0;j<col;j++){
            mat[i][j]=count;
            count++;
        }
    }
    return mat;
}
int main(){
    int qlin,qcol,count=1,lim=0,**mat;
    int i,j,direita=1,esquerda=0,baixo=0,cima=0,qlinteto,qcolteto,qlinpiso=0,qcolpiso=0;
    printf("Quantidade de linhas:");
    scanf("%d",&qlin);
    printf("Quantidade de colunas:");
    scanf("%d",&qcol);
    mat=(int**)malloc(qlin*sizeof(int*));
    for(i=0;i<qlin;i++){
        mat[i]=(int*)malloc(qcol*sizeof(int));
    }
    if(qlin==1||qcol==1){
        mat=cheats(mat,qlin,qcol);
    }
    else{
        lim=qlin*qcol;
        i=0;
        j=0;
        printf("lim=%d\n",lim);
        qlinteto=qlin;
        qcolteto=qcol;
        while(count<lim+1){
            mat[i][j]=0;
            mat[i][j]=count;
            printf("i=%d,j=%d,count=%d\n",i,j,count);
            if(direita==1&&esquerda==0&&baixo==0&&cima==0){
                printf("direita\n");
                j++;
            }
            if(direita==0&&esquerda==1&&baixo==0&&cima==0){
                printf("esquerda\n");
                j--;
            }
            if(direita==0&&esquerda==0&&baixo==1&&cima==0){
                printf("baixo\n");
                i++;
            }
            if(direita==0&&esquerda==0&&baixo==0&&cima==1){
                printf("cima\n");
                i--;
            }
            if(j==qcolteto-1&&direita==1){
                printf("direita->baixo\n");
                qlinpiso++;
                direita=0;
                esquerda=0;
                baixo=1;
                cima=0;
            }
            if(i==qlinteto-1&&baixo==1){
                printf("baixo->esquerda\n");
                qcolteto--;
                direita=0;
                esquerda=1;
                baixo=0;
                cima=0;
            }
            if(j==qcolpiso&&esquerda==1){
                printf("esquerda->cima\n");
                qlinteto--;
                direita=0;
                esquerda=0;
                baixo=0;
                cima=1;
            }
            if(i==qlinpiso&&cima==1){
                printf("cima->direita\n");
                qcolpiso++;
                direita=1;
                esquerda=0;
                baixo=0;
                cima=0;
            }
            count++;
        }
    }
    for(i=0;i<qlin;i++){
        for(j=0;j<qcol;j++){
            if(j==0) printf("\n");
            printf("%3d ",mat[i][j]);
        }
    }
    return 0;
}
