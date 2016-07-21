#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 50
float inverso(float num, float mod){
    float i;
    for(i=1;i<mod;i++){
        if(fmod(i*num,mod)==1) return i;
    }
    return 0; /*não possui inverso*/
}
int main(){
    double inv,K,N;
    FILE *arquivo=fopen("estudo.txt","w");
    fprintf(arquivo,"N K inv\n");
    for(N=1;N<MAX;N++){
        for(K=1;K<N;K++){
            inv=inverso(K,N);
            if(inv!=0){
                printf("%.0f %.0f %.0f\n",N,K,inv);
                fprintf(arquivo,"%.0f;%.0f;%.0f\n",N,K,inv);
            }
        }
    }
    fclose(arquivo);
    return 0;
}
