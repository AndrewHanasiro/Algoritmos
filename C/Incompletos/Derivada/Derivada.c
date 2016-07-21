#include<stdio.h>
#include<stdlib.h>
void derivada(char *func,int ini,int fim){
    int i,Nini=0,Nfim=0;
    for(i=ini;i<=fim;i++){
        if(func[i]=='(') Nini=i+1;
        if(func[i]==')') Nfim=i-1;
        if(Nini!=0&&Nfim!=0){
            derivada(func,Nini,Nfim);
            break;
        }
    }
}
int main(){
    FILE *arquivo;
    int tam,i,parenteses=0;
    char nome[50],*func;
    printf("Digite o nome do arquivo:");
    scanf("%s",nome);
    arquivo=fopen(nome,"r");
    fscanf(arquivo,"%d",&tam);
    printf("Esta funcao tem %d caracteres\n",tam);
    func=(char*)malloc(tam*sizeof(char));
    fscanf(arquivo,"%s",func);
    printf("Funcao: %s\n",func);
    for(i=0;i<tam;i++){
        if(func[i]=='(') parenteses++;
        if(func[i]==')'&&parenteses>0) parenteses--;
        else{
            printf("Abertura e fechamento de parenteses errado!\n");
            break;
        }
    }
    derivada(func,0,tam-1);
    printf("Derivada: %s\n",func);
    fclose(arquivo);
    return 0;
}
