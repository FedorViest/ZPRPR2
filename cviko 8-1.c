#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
#define STARTVELKOST 20
#define SUBOR "ovocie.txt"
typedef struct{
    char nazov[N];
    char vyrobca[N];
    float mnozstvo;
    float cena;
}OVOCIE;

int *vloz(OVOCIE *ovocie, OVOCIE nove_ovocie, int *nacitane, int *max_velkost){
    if (*nacitane==*max_velkost){
       ovocie = (OVOCIE*) realloc(ovocie, 2*(*max_velkost));
       *max_velkost *= 2;
    }
    int i;
    for ( i = 0; i< *nacitane; i++){
        if (strcmp(nove_ovocie.nazov, ovocie[i].nazov) < 0) {
            break;
        }
    }
    for (int j = (*nacitane)-1; j>=i; j--){
        ovocie[j+1] = ovocie[j];
    }
    printf("\n\n%d\n\n", i);
    (*nacitane)++;
    ovocie[i] = nove_ovocie;
    return nacitane;
}
void vypis(OVOCIE *ovocie, int nacitane){
    for (int i = 0; i< nacitane; i++){
        printf("Nazov=%s Vyrobca=%s Mnozstvo=%f Cena=%f\n", ovocie[i].nazov, ovocie[i].vyrobca, ovocie[i].mnozstvo, ovocie[i].cena);
    }
    putchar('\n');
}

int main(){
    char handler[N];
    int nacitane = 0;
    OVOCIE temp;
    OVOCIE *ovocie = (OVOCIE*) malloc (STARTVELKOST * sizeof(OVOCIE));
    int max_velkost = STARTVELKOST;
    while ((scanf(" %s", handler))!=EOF){
        if (!strcmp(handler, "vloz")){
            scanf(" %s %s %f %f", &(temp.nazov), &(temp.vyrobca), &(temp.mnozstvo), &(temp.cena));
            vloz(ovocie, temp, &nacitane, &max_velkost);
        }
        else if (!strcmp(handler, "vypis")){
            vypis(ovocie, nacitane);
        }
        else{
            printf("Chyba");
        }
    }
}
