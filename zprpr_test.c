#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct prvok {

   int hodnota;

   struct prvok *dalsi;

} PRVOK;

void nacitaj(PRVOK **start, int nove_cislo){
    //Alokacia miesta
    PRVOK *aktualne = (PRVOK*) malloc(sizeof(PRVOK));
    //Zapis novej hodnoty do premennej cislo, zapisujem dopredu
    aktualne->hodnota = nove_cislo;
    aktualne->dalsi = (*start);
    (*start) = aktualne;
}

void vypis_rek(PRVOK *zac){
    if (zac != NULL){
        printf("%d", zac->hodnota);
        vypis_rek(zac->dalsi);
    }
}

void vypis(PRVOK *start){
    PRVOK *aktualne = start;
    while (aktualne != NULL){
        printf("%d ", aktualne->hodnota);
        aktualne = aktualne->dalsi;
    }
}

int main(){
    PRVOK *cisla = NULL;
    int count = 0, max, zlozka, i=1;
    printf("Zadajte pocet prvkov:\n");
    scanf("%d", &max);
    //Podmienka pre nacitavanie do zoznamu
    while (count != max){
        printf("Zadajte %d. hodnotu:\n", i);
        scanf("%d", &zlozka);
        //Volanie funkcie nacitaj
        nacitaj(&cisla, zlozka);
        //Zvysovanie poctu a indexu
        count++;
        i++;
    }
    vypis_rek(cisla);
    vypis(cisla);
    return 0;
}
