#include<stdio.h>
#include<string.h>
int main(){
    int count;
    char word1[50],word2[50];
    FILE *arq1,*arq2;
    arq1=fopen("arquivo1.txt","r");
    arq2=fopen("arquivo2.txt","r");
    while(!feof(arq1)){
        count=0;
        fscanf(arq1,"%s",word1);
        while(!feof(arq2)){
            fscanf(arq2,"%s",word2);
            if(strcmp(word1,word2)==0) count++;
        }
        rewind(arq2);
        printf("Existe %d palavras %s\n",count,word1);
    }
    return 0;
}

