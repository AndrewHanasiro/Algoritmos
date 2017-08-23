#include <stdio.h>
#include <stdlib.h>

int **graph(int n){
	int i,j,k,v**temp,n_vert;
	FILE *fp;
	temp=(int**)malloc(n*sizeof(int*));
	if(fp=fopen("graph.txt","r")==NULL){
		printf("erro ao abrir arquivo");
		exit(-1);
	}
	for(i=0;i<n;i++){
		temp[i]=(int*)malloc(n*sizeof(int));
	}
	fscanf(fp,"%d",&n_vert);
	for(v=0.;v<n_vert;v++){
		fscanf(fp,"%d %d %d",&i,&j,&k);
		temp[i][j]=k;
	}
	return temp;
}

int *heuristic(int n){
	int *temp;
	FILE *fp;
	if(fp=fopen("heuristic.txt","r")==NULL){
		printf("erro ao abrir arquivo");
		exit(-1);
	}
	temp(int*)malloc(n*sizeof(int));
	fscanf(fp,"%d",&n_vert);
	for(v=0.;v<n_vert;v++){
		fscanf(fp,"%d",&k);
		temp[v]=k;
	}
	return temp;

}

void A_star(int **G, int *H){
	
}
int main(){
	int **G,*H;
	G=graph(6)
	H=heuristic(6);
	A_star(G,H);
	return 0;
}