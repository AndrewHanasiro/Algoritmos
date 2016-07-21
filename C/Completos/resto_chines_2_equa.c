#include<stdio.h>
#include<stdlib.h>
int **criamatriz(int mod1, int mod2){
    int **temp,ind1,ind2,count=0;
    temp=(int**)malloc(mod1*sizeof(int*));
    for(ind1=0;ind1<mod1;ind1++){
        temp[ind1]=(int*)malloc(mod2*sizeof(int));
    }
    ind1=0;
    ind2=0;
    while(count<mod1*mod2){
        temp[ind1][ind2]=count;
        count++;
        ind1++;
        ind2++;
        if(ind1==mod1) ind1=0;
        if(ind2==mod2) ind2=0;
    }
    return temp;
}
int main(){
    int mod1,mod2,ind1,ind2,**matriz,X,escolha;
    printf("Digite o modulo da primeira equacao:");
    scanf("%d",&mod1);
    printf("Digite o modulo da segunda equacao:");
    scanf("%d",&mod2);
    matriz=criamatriz(mod1,mod2);
    printf("1-Resultado em relacao aos indices equacao\n");
    printf("2-Indices em relacao ao resultado equacao\n");
    printf("escolha:");
    scanf("%d",&escolha);
    switch(escolha){
        case 1:{
            printf("Digite os indices da equacao:");
            scanf("%d %d",&ind1,&ind2);
            if(ind1>=mod1)ind1%=mod1;
            if(ind2>=mod2)ind2%=mod2;
            printf("X=%d",matriz[ind1][ind2]);
        }
        break;
        case 2:{
            printf("Digite o resultado das equacoes:");
            scanf("%d",&X);
            for(ind1=0;ind1<mod1;ind1++){
                for(ind2=0;ind2<mod2;ind2++){
                    if(matriz[ind1][ind2]==X){
                        printf("ind1=%d\nind2=%d",ind1,ind2);
                        break;
                    }
                }
            }

        }
        break;
        default: printf("escolha uma delas\n");
    }
    printf("\n");
    system("pause");
    return 0;
}
