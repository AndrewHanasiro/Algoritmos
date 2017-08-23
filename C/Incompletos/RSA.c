#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int *criachave(int quant_chaves);
int verificaprimo(int num);
int inverso(int K,int F);
char *criafraseC(int tam);
float *alpha2int(char *fraseC,int tam,int *quant_blocos,float N);
float *codificar(float *blocos,float K,float N,int quant_blocos);
float resto(float num, float exp, float mod);
float *decodificar(float *blocos,int *chaves,float D,float N,int quant_blocos,int quant_chaves);
int diofantino(int A,int B);
int main(){
    char *fraseC;
    int *chaves,quant_chaves,quant_blocos;
    float N=1,*blocos,F=1,K=1,D;
    int tam,i;
    printf("Quantas chaves voce deseja:");
    scanf("%d",&quant_chaves);
    chaves=criachave(quant_chaves);
    for(i=0;i<quant_chaves;i++){
        N*=chaves[i];
        F*=(chaves[i]-1);
    }
    while(fmod(F,K)==0){
        printf("Escolha um K, tal que nao divida %.0f:",F);
        scanf("%f",&K);
    }
    D=inverso(K,F);
    printf("N=%.0f,F=%.0f,K=%.0f,D=%.0f\n",N,F,K,D);
    printf("Quantos carateres tem sua frase:");
    scanf("%d",&tam);
    fraseC=criafraseC(tam);
    blocos=alpha2int(fraseC,tam,&quant_blocos,N);
    /*Codifica��o*/
    blocos=codificar(blocos,K,N,quant_blocos);
    /*Decodifica��o*/
    blocos=decodificar(blocos,chaves,D,N,quant_blocos,quant_chaves);
    return 0;
}
int *criachave(int quant_chaves){
    int i,*temp,cond;
    temp=(int*)malloc(quant_chaves*sizeof(int));
    for(i=0;i<quant_chaves;i++){
        cond=0;
        while(cond==0){
            printf("Chaves %d:",i+1);
            scanf("%d",&temp[i]);
            cond=verificaprimo(temp[i]);
        }
    }
    return temp;
}
int verificaprimo(int num){
    int i;
    for(i=2;i<num;i++){
        if(num%i==0) return 0;
    }
    return 1;
}
int inverso(int num,int mod){
    int i;
    if(num>mod)num%=mod;
    for(i=0;i<mod;i++){
        if((num*i)%mod==1) return i;
    }
    return 1;
}
char *criafraseC(int tam){
    char *temp;
    temp=(char*)malloc(tam*sizeof(char));
    printf("Digite sua frase:");
    fflush(stdin);
    gets(temp);
    return temp;
}
float *alpha2int(char *fraseC,int tam,int *quant_blocos,float N){
    int *fraseN,i,j=0,limite;
    float *temp;
    *quant_blocos=0;
    fraseN=(int*)malloc((2*tam)*sizeof(int));
    temp=(float*)malloc((2*tam)*sizeof(float));
    for(i=0;i<tam;i++){
        temp[i]=0;
    }
    /*transformand cada char em dois int, Ex: a=97 -> 9 e 7*/
    for(i=0;fraseC[i]!='\0';i++){
        if(fraseC[i]==' ') fraseC[i]=99;
        else fraseC[i]-=87; /*este -87 é por causa da tabela ASCII, transforma a=10*/
        fraseN[j]=(fraseC[i]-(fraseC[i]%10))/10; /*algarismo da unidade da letra*/
        j++;
        fraseN[j]=fraseC[i]%10;/*algarismo da dezena da letra*/
        j++;
    }
    printf("frase transformada em numeros e separada em blocos:\n");
    limite=j;
    j=0;
    for(i=0;i<limite;i++){
        /*se a colocar mais um algarismo for menor que N entao coloca, Ex N=501 e temp=48 e fraseN=1*/
        if(temp[j]*10+fraseN[i]<=N) temp[j]=temp[j]*10+fraseN[i];
        else{
            /*caso contrario coloca no proximo temp*/
            printf("%.0f-",temp[j]);
            j++;
            temp[j]=fraseN[i];
            (*quant_blocos)++;
            if(temp[j]==0){ /*se o proximo bloco come�ar com zero entao fa�a o zero separado 022 -> -0-22*/
                printf("%.0f-",temp[j]);
                j++;
                (*quant_blocos)+=1;
            }
        }
    }
    printf("%.0f-\n",temp[j]);
    (*quant_blocos)+=1;
    return temp;
}
float *codificar(float *blocos,float K,float N,int quant_blocos){
    int i;
    printf("blocos codificado:\n");
    for(i=0;i<quant_blocos;i++){
        blocos[i]=resto(blocos[i],K,N);
        printf("%.0f-",blocos[i]);
    }
    return blocos;
}
float resto(float num, float exp, float mod){
    int i;
    float prod=1;
    for(i=0;i<exp;i++){
        prod=fmod(prod*num,mod);
    }
    return prod;
}
float *decodificar(float *blocos,int *chaves,float D,float N,int quant_blocos,int quant_chaves){
    int *gX,*indX,*NX,*cX;
    int i, j;
    gX=(int*)malloc(quant_chaves*sizeof(int));
    indX=(int*)malloc(quant_chaves*sizeof(int));
    cX=(int*)malloc(quant_chaves*sizeof(int));
    NX=(int*)malloc(quant_blocos*sizeof(int));
    printf("\nBlocos decodificados:\n");
    for(j=0;j<quant_blocos;j++){
        for(i=0;i<quant_chaves;i++){
            gX[i]=fmod(D,chaves[i]-1);
            indX[i]=resto(blocos[j],gX[i],chaves[i]);
            NX[i]=N/chaves[i];
            cX[i]=inverso(NX[i],chaves[i]);
            blocos[j]+=indX[i]*NX[i]*cX[i];
            printf("Ni=%d,ri=%d,X=%d(mod%d)\n",NX[i],cX[i],indX[i],chaves[i]);
        }
        /*blocos[j]=resto(blocos[j],D,N);*/
        printf("bloco decodificado:%.0f\n",resto(blocos[j],1,N));
    }
    return blocos;
}
