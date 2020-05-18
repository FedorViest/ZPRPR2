#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUBOR "osemsmerovka.txt"

int nacitanie_suboru(FILE *fr, int *riadok, int *stlpec, char **pole){
    char medzera;
    if ((fr=fopen(SUBOR, "r"))==NULL){
        printf("Subor sa nepodarilo otvort.\n");
        return 0;
    }
    fscanf(fr, "%d%c%d", &riadok, &medzera, &stlpec);
    printf("%d%c%d\n", riadok, medzera, stlpec);

    if (fclose(fr)==EOF){
        printf("Subor sa nepodarilo zatovrit.\n");
        return 0;
    }
}


int main(){
    FILE *f;
    char **pole;
    int riadok, stlpec;
    nacitanie_suboru (f, &riadok, &stlpec, pole);
    return 0;
}
