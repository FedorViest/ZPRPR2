#include <stdio.h>
#include <string.h>
#define N 100

int main(){
    FILE *fr;
    FILE *fw;
    FILE *r;
    int prve[N], druhe[N], vysledne[2*N], dlzka1, dlzka2, n, iindex=0, jindex=0, spolu, i;
    fr=fopen("cisla1.txt", "r");
    fw=fopen("cisla2.txt", "r");
    r=fopen("vysledok.txt", "w");
    while ((fscanf(fr, "%d", prve))!=EOF){
        printf("%s ", prve);
    }
    while ((fscanf(fw, "%d", druhe))!=EOF){
        printf("%s ", druhe);
    }
    dlzka1=sizeof(prve)/sizeof(prve[0]);
    dlzka2=sizeof(druhe)/sizeof(druhe[0]);
    n=dlzka1+dlzka2;

    for (spolu=0; spolu<n; i++){
        if(iindex>=dlzka1 || jindex>=dlzka2)
            break;
        if(prve[iindex]<druhe[jindex]){
            vysledne[spolu]=prve[iindex];
            iindex++;
        }
        else{
            vysledne[spolu]=druhe[jindex];
            jindex++;
        }
    }
    for (int i=0; i<n; i++){
        printf("%d ", vysledne[i]);
    }



    return 0;
}
