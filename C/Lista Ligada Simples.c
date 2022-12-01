#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct listaid{
    int id;
    struct listaid *prox;
}ListID;
typedef struct vetor{
    int quant;
    ListID *list;
}Vet;
void incluir(ListID **L,int k){
    ListID *pt,*temp;
    temp=(ListID*)malloc(sizeof(ListID));
    temp->id=k;
    temp->prox=NULL;
    if(*L==NULL){
        *L=temp;
    }
    else{
        if(k<(*L)->id){
            temp->prox=*L;
            *L=temp;
        }
        else{
            pt=*L;
            while(pt->prox!=NULL&&pt->prox->id<k){
                pt=pt->prox;
            }
            temp->prox = pt->prox;
            pt->prox = temp;
        }
    }
}
void mostrar(ListID *L){
    ListID *pt;
    for(pt=L;pt!=NULL;pt=pt->prox){
        printf("%d ",pt->id);
    }
    printf("\n");
}
void remover(ListID **L,int k){
    ListID *pt,*aux;
    if(*L!=NULL){
        pt=*L;
        if(pt->id==k){
            printf("teste1\n");
            *L=pt->prox;
            free(pt);
        }
        else{
            pt=*L;
            while(pt->prox!=NULL&&pt->prox->id!=k){
                pt=pt->prox;
            }
            /*verificando se está no meio*/
            if(pt->prox!=NULL){
                if(pt->prox->id==k){
                    aux=pt->prox;
                    pt->prox=aux->prox;
                    free(aux);
                    printf("meio\n");
                }
            }
        }
    }
}
int main(){
    Vet V[10];
    int i,j,k,quant;
    srand(time(NULL));
    for(i=0;i<10;i++){
        quant=rand()%10;
        quant+=5;
        printf("quant=%d\n",quant);
        V[i].quant=quant;
        V[i].list=NULL;
        for(j=0;j<quant;j++){
            printf("%d ",j+i*10);
            incluir(&(V[i].list),j+i*10);
        }
        printf("\n");
    }
    printf("\nANTES:\n");
    for(i=0;i<10;i++){
        mostrar(V[i].list);
    }
    printf("Digite um numero para retirar:");
    scanf("%d",&k);
    printf("\nDEPOIS:\n");
    for(i=0;i<10;i++){
        remover(&(V[i].list),k);
    }
    for(i=0;i<10;i++){
        mostrar(V[i].list);
    }
    return 0;
}
