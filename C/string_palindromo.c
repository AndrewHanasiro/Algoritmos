#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *inicia(){
    char *temp=(char*)malloc(100*sizeof(char));
    fflush(stdin);
    printf("entre coma frase:");
    gets(temp);
    return temp;
}
int palindromo(char *str, int fim, int ini){
    if(ini>=fim) return 1;
    else{
        while(str[ini]==' ') ini++;
        while(str[fim]==' ') fim--;
        if(str[ini]==str[fim]) return palindromo(str,fim-1,ini+1);
        else return 0;
    }
}
int pal(char *str){
    int i,j;
    i=0;
    j=strlen(str)-1;
    while(i<strlen(str)){
        while(str[i]==' ') i++;
        while(str[j]==' ') j--;
        if(str[i]!=str[j]) return 0;
        i++;
        j--;
    }
    return 1;
}
int main(){
    char *str;
    str=inicia();
    printf("recursivo:");
    if(palindromo(str,strlen(str)-1,0)) printf("SIm\n");
    else printf("Nao\n");
    printf("iterativo:");
    if(pal(str)) printf("SIm\n");
    else printf("Nao\n");
    return 0;
}
