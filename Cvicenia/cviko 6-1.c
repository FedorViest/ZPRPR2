// zliezanie kopca - najdenie cesty v mape (2D staticke pole)
// najdeme policko s najvyssou vyskou
// budeme hladat cestu (4-mi smermi) tak, aby sa robili co najmensie skoky
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SUBOR "kopec.txt"
#define N 12

// nacitanie obsahu dvojrozmerneho pola zo suboru

int scitaj_znaky(int *riadok, int *stlpec){
    char c;
    FILE *fr;
    fr=fopen(SUBOR, "r");
    *riadok=0;
    *stlpec=0;
    while ((c=getc(fr))!=EOF){
        if (c=='\n')
            (*riadok)++;
        if (c==' ')
            (*stlpec)++;
    }
    *stlpec=(*stlpec)/(*riadok)+1;
    fclose(fr);

}

int **alokuj(int *riadok, int *stlpec){
    int **mapa;
    mapa = (int **) malloc (*riadok*sizeof(int*));
    for (int i=0; i<*riadok; i++){
        mapa[i]= (int *) malloc (*stlpec*sizeof(int));
    }
    return mapa;
}
int nacitanie(int **mapa, int *riadok, int *stlpec){
    FILE *fr;
    fr=fopen(SUBOR, "r");
    for (int i=0; i<*riadok; i++){
        for (int j=0; j<*stlpec; j++){
            fscanf(fr, "%d", &mapa[i][j]);
        }
    }
    fclose(fr);
}

// najdenie maximalneho prvku: vratenie hodnot cez argumenty
void najdi_kopec(int **mapa, int *riadok, int *stlpec, int *ki, int *kj) {
	int i, j;
	*ki = *kj = 0;
	for(i=0; i<*riadok; i++)
		for(j=0; j<*stlpec; j++)
			if(mapa[i][j] > mapa[*ki][*kj]) {
				*ki = i;
				*kj = j;
				//printf("i: %d, j: %d, mapa: %d\n", *ki, *kj, mapa[*ki][*kj]);
			}
}

void vypusti(int **mapa, int *riadok, int *stlpec){
    for (int i=0; i<*riadok; i++){
        if (mapa[i]!=NULL){
            free(mapa[i]);
            //printf("1");
        }
        else
            printf("Nepodarilo sa uvolnit pamat");
    }
}


// hladanie v vypis cesty, kde sa robia lokalne o najmensie vyskove rozdiely
void zidi_kopec(int **mapa, int *riadok, int *stlpec, int ki, int kj) {
	int i, j, max;
	while (ki != 0 && ki != *riadok-1 && kj != 0 && kj != *stlpec-1) {
		max = 0;
		// sever
		if(ki-1 >=0 && mapa[ki-1][kj] > max && mapa[ki-1][kj] < mapa[ki][kj]) {
			i = ki-1;
			j = kj;
			max = mapa[i][j];
		}
		//severovychod
		if(ki-1 >=0 && mapa[ki-1][kj+1] > max && mapa[ki-1][kj+1] < mapa[ki][kj]) {
			i = ki-1;
			j = kj+1;
			max = mapa[i][j];
		}
		// vychod
		if(kj+1 <*stlpec && mapa[ki][kj+1] > max && mapa[ki][kj+1] < mapa[ki][kj]) {
			i = ki;
			j = kj+1;
			max = mapa[i][j];
		}
		//juhovyhod
		if(ki+1 >=0 && mapa[ki+1][kj+1] > max && mapa[ki+1][kj+1] < mapa[ki][kj]) {
			i = ki+1;
			j = kj+1;
			max = mapa[i][j];
		}
		// juh
		if(ki+1 <*riadok && mapa[ki+1][kj] > max && mapa[ki+1][kj] < mapa[ki][kj]) {
			i = ki+1;
			j = kj;
			max = mapa[i][j];
		}
		//juhozapad
		if(ki+1 >=0 && mapa[ki+1][kj-1] > max && mapa[ki+1][kj-1] < mapa[ki][kj]) {
			i = ki+1;
			j = kj-1;
			max = mapa[i][j];
		}
		// zapad
		if(kj-1 >=0 && mapa[ki][kj-1] > max && mapa[ki][kj-1] < mapa[ki][kj]) {
			i = ki;
			j = kj-1;
			max = mapa[i][j];
		}
		//severozapad
		if(ki-1 >=0 && mapa[ki-1][kj-1] > max && mapa[ki-1][kj-1] < mapa[ki][kj]) {
			i = ki-1;
			j = kj-1;
			max = mapa[i][j];
		}
		printf("i: %d, j: %d, ki: %d, kj: %d, vyska: %d\n", i, j, ki, kj, max);
		ki = i;
		kj = j;
		if (max==0)
            break;
	}
}

// hladanie v vypis cesty, kde sa robia lokalne o najmensie vyskove rozdiely
// rekurzivna verzia
/*void zidi_kopec_rek(int mapa[][N], int *riadok, int *stlpec, int ki, int kj) {
	int i, j, max;
	if (ki != 0 && ki != *riadok-1 && kj != 0 && kj != *stlpec-1) {
		max = 0;
		// sever
		if(ki-1 >=0 && mapa[ki-1][kj] > max && mapa[ki-1][kj] < mapa[ki][kj]) {
			i = ki-1;
			j = kj;
			max = mapa[i][j];
		}
		// vychod
		if(kj+1 <*stlpec && mapa[ki][kj+1] > max && mapa[ki][kj+1] < mapa[ki][kj]) {
			i = ki;
			j = kj+1;
			max = mapa[i][j];
		}
		// juh
		if(ki+1 <*riadok && mapa[ki+1][kj] > max && mapa[ki+1][kj] < mapa[ki][kj]) {
			i = ki+1;
			j = kj;
			max = mapa[i][j];
		}
		// zapad
		if(kj-1 >=0 && mapa[ki][kj-1] > max && mapa[ki][kj-1] < mapa[ki][kj]) {
			i = ki;
			j = kj-1;
			max = mapa[i][j];
		}
		printf("i: %d, j: %d, vyska: %d\n", i, j, max);
/*		zidi_kopec_rek(mapa, n, i, j);
	}
}*/

int main() {

	int mapa[N][N], n;
	int ki, kj;
	int riadok, stlpec;
	int **mapa2;
	scitaj_znaky(&riadok, &stlpec);
    mapa2=alokuj (&riadok, &stlpec);
    nacitanie(mapa2, &riadok, &stlpec);
    for (int i=0; i<riadok; i++){
        for (int j=0; j<stlpec; j++){
            printf("%d ", mapa2[i][j]);
        }
        putchar('\n');
    }
	najdi_kopec(mapa2, &riadok, &stlpec, &ki, &kj);
	printf("suradnice kopca: %d, %d\n", ki, kj);
	zidi_kopec(mapa2, &riadok, &stlpec, ki, kj);
	/*printf("rekurzivne:\n");
	zidi_kopec_rek(mapa, n, ki, kj);*/
    vypusti(mapa2, &riadok, &stlpec);
	return 0;
}

