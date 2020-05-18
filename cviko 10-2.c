// uloha10-2.c -- Fedor Viest, 1.5.2020 17:20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clovek {
    char meno[30];
    int rocnik;
    struct clovek *dalsi, *pred;
} CLOVEK;

// obrat zoznam
CLOVEK *obratZoznam(CLOVEK *z) {
   CLOVEK *prev = NULL;
   CLOVEK *current = z;
   CLOVEK *next = NULL;
   while (current != NULL) {
      next = current->dalsi;
      current->dalsi = prev;
      prev = current;
      current = next;
   }
   z = prev;

}

// vlozenie zaznamu
CLOVEK *vlozDoUsp(CLOVEK *zac, char meno[], int rocnik){
   CLOVEK *vloz = (CLOVEK *) malloc(sizeof(CLOVEK));
   strcpy(vloz->meno, meno);
   vloz->rocnik = rocnik;
   vloz->dalsi = vloz->pred = NULL;

   // prazdny zoznam: jedinym prvkom zoznamu sa stane vkladany prvok
   if (zac == NULL) return vloz;

   // vkladanie na zaciatok zoznamu
   if (strcmp(meno, zac->meno) < 0) {
      vloz->dalsi = zac;
      zac->pred = vloz;
      return vloz;
   }

   // vkladanie na 2. - poslednu poziciu
   CLOVEK *akt = zac;
   while (akt->dalsi != NULL && strcmp(meno, akt->dalsi->meno) > 0) {
      akt = akt->dalsi;
   }
   vloz->dalsi = akt->dalsi;
   akt->dalsi = vloz;
   vloz->pred = akt;
   if (vloz->dalsi != NULL) vloz->dalsi->pred = vloz;
   return zac;
}

// vypis zoznamu
void vypisZoznam(CLOVEK *zac) {
	if (zac == NULL) {
		printf("Zoznam je prazdny.\n");
		return;
	}
   	while(zac != NULL) {
      	printf("%s %d\n", zac->meno, zac->rocnik);
      	zac = zac->dalsi;
  	}
}

int main() {

	CLOVEK *akt = NULL;
	int r;
	char meno[100];

	while (scanf("%s %d", meno, &r) == 2) {
		akt = vlozDoUsp(akt, meno, r);
	}

	akt = obratZoznam(akt);
	vypisZoznam(akt);
	return 0;
}
