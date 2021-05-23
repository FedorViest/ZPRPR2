// nacitanie najviac N prvych roznych slov do N-prvkoveho pola ukazovatelov na retazce
// v N-prvkovom poli celych cisel si pamatame pocty vyskytov
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20		// maximalna dlzka slovnika
#define NSLOVA 100 	// maximalna dlzka slova
#define SUBOR "slova.txt"

int nacitaj(char *slovnik[], int pocet[], int *vyskyt[]) {
	int i, n = 0;
	char *p, slovo[NSLOVA];
	FILE *f;
	int index_slova=0;

	for(i=0; i<N; i++) {
		pocet[i] = 0;
		slovnik[i] = NULL;
	}

	if((f = fopen(SUBOR, "r")) == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 0;
	}
	while(fscanf(f, "%s", slovo) == 1) {
		//printf("%s\n", slovo);
		for(i=0; i<n; i++)
			if(!strcmp(slovnik[i], slovo))
				break;
        index_slova++;
        // slovo sa v slovniku nachadza
		if(i < n){
			pocet[i]++;
			//Reallocujem  pocetnost slova v texte
			vyskyt[i]=(int*)realloc(vyskyt[i], pocet[i]*sizeof(int));
			//Davam vyskyt na poziciu na ktorej je slovo
			vyskyt[i][pocet[i]-1]=index_slova;
		}
		else if(n<N){
			int len = strlen(slovo);
			p = (char *) malloc(len+1);
			strcpy(p, slovo);
			slovnik[n] = p;
			pocet[n] = 1;
			//Zvysujem vyskyto 1 vzdy ked sa tam nachadza este raz
			vyskyt[n]=(int *) malloc(1*sizeof(int));
			vyskyt[n][0]=index_slova;
			n++;
		}
	}

	fclose(f);
	for(i=n; i<N; i++) {
		slovnik[i] = NULL;
		pocet[i] = 0;
	}
 	return n;
}

void uvolni(char *slovnik[], int **vyskyt, int n) {
	int i;
	for (i=0; i<N; i++){
		if (slovnik[i] != NULL){
			free(slovnik[i]);
		}
	}
	for (i=0; i<n; i++){
        free(vyskyt[i]);
	}
    free(vyskyt);
}

int main() {
	char *slovnik[N];
	int pocet[N];
	int i, n;
	int *vyskyt[N];
	n = nacitaj(slovnik, pocet, vyskyt);
	for(i=0; i<n; i++){
		printf("%s (%d): ", slovnik[i], pocet[i]);
		for (int j=0; j<pocet[i]; j++){
            printf("%d ", vyskyt[i][j]);
		}
		putchar('\n');
	}
	uvolni(slovnik, vyskyt, n);
	return 0;
}
