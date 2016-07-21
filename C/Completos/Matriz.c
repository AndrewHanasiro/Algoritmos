#include <stdio.h>
#include <stdlib.h>
void imprime(int **matriz, int linhas, int colunas){
    int lin,col;
    for(lin=0;lin<linhas;lin++){
        for(col=0;col<colunas;col++){
            if(col==0) printf("\n");
            printf("%4d",matriz[lin][col]);
        }
    }
    printf("\n");
}
int **zera(int **matriz, int linhas, int colunas){
    int lin,col;
    for(lin=0;lin<linhas;lin++){
        for(col=0;col<colunas;col++){
            matriz[lin][col]=0;
        }
    }
    imprime(matriz,linhas,colunas);
    return matriz;
}
void desaloca(int **matriz, int linhas){
    int i;
    for(i=0;i<linhas;i++){
        free(matriz[i]);
    }
    free(*matriz);
}
void atribui_right2down(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(lin=0;lin<linhas;lin++){
        for(col=0;col<colunas;col++){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_left2down(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(lin=0;lin<linhas;lin++){
        for(col=colunas-1;col>=0;col--){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_right2up(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(lin=linhas-1;lin>=0;lin--){
        for(col=0;col<colunas;col++){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_left2up(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(lin=linhas-1;lin>=0;lin--){
        for(col=colunas-1;col>=0;col--){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_down2right(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(col=0;col<colunas;col++){
        for(lin=0;lin<linhas;lin++){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_up2right(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(col=0;col<colunas;col++){
        for(lin=linhas-1;lin>=0;lin--){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_down2left(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(col=colunas-1;col>=0;col--){
        for(lin=0;lin<linhas;lin++){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_up2left(int** matriz, int linhas, int colunas){
    int lin,col,count=1;
    for(col=colunas-1;col>=0;col--){
        for(lin=linhas-1;lin>=0;lin--){
            matriz[lin][col]=count;
            count++;
        }
    }
    imprime(matriz,linhas,colunas);
}
void atribui_SE(int **matriz, int linhas, int colunas){
    int lin=0,col=0,count;
    for(count=1;count<=linhas*colunas;count++){
        if(lin==linhas) lin=0;
        if(col==colunas) col=0;
        matriz[lin][col]=count;
        lin++;
        col++;
    }
    imprime(matriz,linhas,colunas);
}
void atribui_SW(int **matriz, int linhas, int colunas){
    int lin=0,col=colunas-1,count;
    for(count=1;count<=linhas*colunas;count++){
        if(lin==linhas) lin=0;
        if(col<0) col=colunas-1;
        matriz[lin][col]=count;
        lin++;
        col--;
    }
    imprime(matriz,linhas,colunas);
}
void atribui_NE(int **matriz, int linhas, int colunas){
    int lin=linhas-1,col=0,count;
    for(count=1;count<=linhas*colunas;count++){
        if(lin<0) lin=linhas-1;
        if(col==colunas) col=0;
        matriz[lin][col]=count;
        lin--;
        col++;
    }
    imprime(matriz,linhas,colunas);
}
void atribui_NW(int **matriz, int linhas, int colunas){
    int lin=linhas-1,col=colunas-1,count;
    for(count=1;count<=linhas*colunas;count++){
        if(lin<0) lin=linhas-1;
        if(col<0) col=colunas-1;
        matriz[lin][col]=count;
        lin--;
        col--;
    }
    imprime(matriz,linhas,colunas);
}
int main()
{
    int i,linhas,colunas,**matriz;
    printf("Quantidade de linhas:");
    scanf("%d",&linhas);
    printf("Quantidade de colunas:");
    scanf("%d",&colunas);
    matriz=(int**)malloc(linhas*sizeof(int*));
    if(matriz!=NULL){
        for(i=0;i<linhas;i++){
            matriz[i]=(int*)malloc(colunas*sizeof(int));
            if(matriz[i]==NULL){
                printf("Erro: Memória não alocada para M[%d]",i);
                return 0;
            }
        }
        printf("Zerando a matriz:\n");
        matriz=zera(matriz,linhas,colunas);
        /*atribuindo por linha*/
        printf("Imprimindo matriz por linha:\n");
        atribui_right2down(matriz,linhas,colunas);
        atribui_left2down(matriz,linhas,colunas);
        atribui_right2up(matriz,linhas,colunas);
        atribui_left2up(matriz,linhas,colunas);
        /*atribuindo por colunas*/
        printf("Imprimindo matriz por coluna:\n");
        atribui_down2right(matriz,linhas,colunas);
        atribui_up2right(matriz,linhas,colunas);
        atribui_down2left(matriz,linhas,colunas);
        atribui_up2left(matriz,linhas,colunas);
        if(colunas!=linhas){
            /*atribuindo pela diagonal, sim pela diagonal*/
            printf("Imprimindo matriz pela diagonal:\n");
            atribui_SE(matriz,linhas,colunas);
            system("pause");
            atribui_SW(matriz,linhas,colunas);
            atribui_NE(matriz,linhas,colunas);
            atribui_NW(matriz,linhas,colunas);
        }
        desaloca(matriz,linhas);
    }
    return 0;
}
