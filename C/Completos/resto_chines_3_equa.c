#include<stdio.h>
#include<stdlib.h>
int mdc(int a,int b,int c){/*c>=b>=a*/
    int nume,divi,resto;
    /*testando mdc(b,c)*/
    nume=c;
    divi=b;
    resto=nume%divi;
    while(resto!=0){
        nume=divi;
        divi=resto;
        resto=nume%divi;
    }
    if(divi!=1) return 0;
    /*testando mdc(a,b)*/
    nume=b;
    divi=a;
    resto=nume%divi;
    while(resto!=0){
        nume=divi;
        divi=resto;
        resto=nume%divi;
    }
    if(divi!=1) return 0;
    /*testando mdc(a,c)*/
    nume=c;
    divi=a;
    resto=nume%divi;
    while(resto!=0){
        nume=divi;
        divi=resto;
        resto=nume%divi;
    }
    if(divi!=1) return 0;
    else return 1;
}
int main(){
    int i,j,k,num,temp,mod[3],a[3],***table,max=1;
    for(i=0;i<3;i++){
        printf("Digite a e m da equacao X=a(mod m):");
        scanf("%d %d",&a[i],&mod[i]);
        if(mod[i]<0) mod[i]=-mod[i];
        if(a[i]>=mod[i]) a[i]%=mod[i];
        if(a[i]<0){
            while(a[i]<0) {a[i]+=mod[i];};
        }
        max*=mod[i];
    }
    /*colocando mod em ordem*/
    while(mod[0]>mod[1]||mod[1]>mod[2]){
        if(mod[0]>mod[1]){
            temp=mod[0];
            mod[0]=mod[1];
            mod[1]=temp;
            temp=a[0];
            a[0]=a[1];
            a[1]=temp;
        }
        if(mod[1]>mod[2]){
            temp=mod[1];
            mod[1]=mod[2];
            mod[2]=temp;
            temp=a[1];
            a[1]=a[2];
            a[2]=temp;
        }
    }
    if(mdc(mod[0],mod[1],mod[2])){/*vendo se mdc(a,b,c)=1*/
        /*alocando*/
        table=(int***)malloc(mod[0]*sizeof(int**));
        for(i=0;i<mod[0];i++){
            table[i]=(int**)malloc(mod[1]*sizeof(int*));
            for(j=0;j<mod[1];j++){
                table[i][j]=(int*)malloc(mod[2]*sizeof(int));
            }
        }
        /*atribuindo*/
        i=0;
        j=0;
        k=0;
        for(num=0;num<max;num++){
            table[i][j][k]=num;
            i++;
            j++;
            k++;
            if(i==mod[0]) i=0;
            if(j==mod[1]) j=0;
            if(k==mod[2]) k=0;
        }
        /*imprimindo*/
        for(i=0;i<mod[0];i++){
            for(j=0;j<mod[1];j++){
                if(j==0) printf("\n----------tabela %d-------------",i);
                for(k=0;k<mod[2];k++){
                    if(k==0) printf("\n");
                    printf(" %3d |",table[i][j][k]);
                }
            }
        }
        /*Imprimindo resultado*/
        printf("\nsolucao para as equacoes:\n");
        for(i=0;i<3;i++){
            printf("X=%d(mod%d)\n",a[i],mod[i]);
        }
        printf("X=%d\n",table[a[0]][a[1]][a[2]]);
        /*liberando memoria*/
        for(i=0;i<mod[0];i++){
            for(j=0;j<mod[1];j++){
                free(table[i][j]);
            }
        }
        for(i=0;i<mod[0];i++){
            free(table[i]);
        }
        free(table);
    }
    else printf("\nO mdc(%d,%d,%d) tem que ser igual a 1",mod[0],mod[1],mod[2]);
    return 0;
}
