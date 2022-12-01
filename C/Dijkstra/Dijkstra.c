#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 6 //Neste caso há 6 vertices
#define Nconexo -1
#define SelfCost 0 //Pois o Custo do proprio vetice pra sí mesmo é zero
typedef struct no{
	int vertice;
	struct no *prox;
}Lista;

/*
Função que cria o grafo com peso, sendo que -1 está sendo setado incialmente, exceto do vértice pra si mesmo
*/
float ** criaGrafo(){
	int lin, col;
	float **temp;
	temp=(float**)malloc(MAX*sizeof(float*));
	for(lin=0 ; lin<MAX ; lin++){
		temp[lin] = (float*)malloc(MAX*sizeof(float));
		for(col=0 ; col<MAX ; col++){
			temp[lin][col] = Nconexo;
			if(lin==col)
				temp[lin][col] = SelfCost;
		}
	}
	return temp;
}

/*
Função que lê um arquivo chamado "grafo.txt", cuja a primeira linha contem a quantidade de aresta
as seguintes linhas são do formato "U V P" na semantica: do vértice U para V possui peso P
*/
void atribuiGrafo(float **Grafo){
	FILE *arquivo;
	int i, u, v, quantVertices;
	float peso;
	arquivo=fopen("grafo.txt","r");
	fscanf(arquivo,"%d", &quantVertices);
	for(i=0;i<quantVertices;i++){
		fscanf(arquivo,"%d %d %f", &u, &v, &peso);
		Grafo[u][v]=peso;
	}
}

/*
Função que espelha o grafo. Essa função só deve ser utilizada se as arestas são bidirecionais e únicas
entre os pares de vértices, ou seja, não duas arestas entre dois pares de vértices e além disso o peso
da aresta é o mesmo do vertétice U para V como V para U
*/
void espelhaGrafo(float **Grafo){
	int lin, col;
	for(lin=0 ; lin<MAX ; lin++){
		for(col=lin+1 ; col<MAX ; col++){
			Grafo[col][lin] = Grafo[lin][col];

		}
	}
}

/*
Função de nome auto-explicativo, portanto nem perca tempo lendo
*/
void imprimeGrafo(float **Grafo){
    int lin,col;
    for(lin=0;lin<MAX;lin++){
        for(col=0;col<MAX;col++){
            if(col==0) printf("\n");
            printf("%.1f\t",Grafo[lin][col]);
        }
    }
    printf("\n");
}

/*
Função que procura o indice que contém o menor entre aqueles que estão na lista TODOS
*/
int procuraMenorPeso(float **Grafo, int vertice,Lista *Lt){
	Lista *Temp;
	int k, indice, vetor[MAX];
	float min=99999999;
	//Criando um vetor em que 0 significa que está fora da Lista e 1 está na lista Lt
	for(k=0 ; k<MAX ; k++){
		vetor[k] = 0; //está fora da lista
	}
	//Setando o vetor percorrendo a Lista e verificando aqueles que estão na lista Lt
	for(Temp=Lt ; Temp!=NULL ; Temp=Temp->prox){
        printf("Temp->vertice:%d\n", Temp->vertice);
		vetor[Temp->vertice] = 1; //está na lista
	}
	//verificando qual menor peso entre os vizinhos do vertices, excluindo aqueles que estão na Lista Lt
	for(k=0 ; k<MAX ; k++){
		if(Grafo[vertice][k]>0 && Grafo[vertice][k]<min && vetor[k]==0){
            min = Grafo[vertice][k];
			indice = k;
            printf("min=%.2f\t indice=%d\t k=%d \n",min,indice,k);
		}
	}
	return indice;
}

/*
Insere um Vertice na Lista
*/
void insereVertice(Lista **Lt, int V){
    Lista *temp;
    temp=(Lista*)malloc(sizeof(Lista)); /*Aloca um espaço na memória*/
    temp->vertice=V;
    temp->prox=*Lt;
    *Lt=temp;
}

/*
Função que cria uma lista ligada simples que contém todos os vértice, exceto o vertice inicial
cada nó é um vértice
*/
Lista * criaListaTodos(int vertice){
	int k;
	Lista *Temp;
	Temp=NULL;
	for(k=0 ; k<MAX ; k++){
		if(k!=vertice)
			insereVertice(&Temp, k);
	}
	return Temp;
}

int vazioTodos(Lista *Todos){
    Lista *Temp;
    for(Temp=Todos ; Temp!=NULL ; Temp=Temp->prox){
        if(Temp->vertice!=-1)
            return 0;
    }
    return 1;
}

/*
Imprime um Lista
*/
void imprimeLista(Lista *Todos,char *str){
	Lista *Temp;
	printf("\nLista %s:\n",str);
	for(Temp=Todos ; Temp!=NULL ; Temp=Temp->prox){
		printf("vertice: %d\n", Temp->vertice);
	}
	printf("\n");
}

/*
Função que remove um nó da lista
*/
void removeVertice(Lista *Todos, int novoV){
	Lista *Temp;
	for(Temp=Todos ; Temp!=NULL ; Temp=Temp->prox){
		if(Temp->vertice == novoV){
			Temp->vertice=-1;
			break;
		}
	}
}

/*
Função que calcula o menor custo de todos os vértices para o vertice do parametro
*/
void Dijkstra(float **Grafo, int vertice){
	int novoV, k;
	Lista *Lt=NULL;
	Lista *Todos=NULL;
	insereVertice(&Lt,vertice);
	Todos=criaListaTodos(vertice);
	imprimeLista(Todos,"Todos");
	while(!vazioTodos(Todos)){
		imprimeGrafo(Grafo);
		imprimeLista(Lt,"Vertices");
		novoV=procuraMenorPeso(Grafo,vertice,Lt);
		for(k=0 ; k<MAX ; k++){
			if(k != vertice){
				if((Grafo[vertice][k]>Grafo[vertice][novoV]+Grafo[novoV][k] || Grafo[vertice][k]==Nconexo ) && Grafo[novoV][k]>0)
					Grafo[vertice][k] = Grafo[vertice][novoV]+Grafo[novoV][k];
			}
		}
		removeVertice(Todos,novoV);
		insereVertice(&Lt,novoV);
        //system("pause");
	}
}

/*
Função principal do programa
*/
int main(){
	float **Grafo;
	int vertice;
	Grafo = criaGrafo();
	atribuiGrafo(Grafo);
	espelhaGrafo(Grafo); //Usa se o tipo do grafo for NÃO direcionado
	for(vertice=0; vertice<MAX ; vertice++){
		Dijkstra(Grafo,vertice);
	}
	printf("GRAFO FINAL:\n");
	imprimeGrafo(Grafo);
	return 0;
}
