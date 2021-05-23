// uloha11-1.c -- Fedor Viest, 1.5.2020 17:20

#include <stdio.h>
#include <stdlib.h>

typedef struct cislo {
  int hod;
  struct cislo *dalsi;
} CISLO;

int opakuju(CISLO *z) {
  int count = 0;
  CISLO *current = z;
  while (current->dalsi != NULL){
	  CISLO *ptr = current->dalsi;
	  while (ptr != NULL){
		  if (current->hod == ptr->hod){
			  count++;
			  break;
		  }
		  ptr = ptr->dalsi;
	  }
	  current = current->dalsi;
  }
	return count;
}

CISLO *nacitaj() {
	CISLO *z = NULL, *p;
	int h;
	while (scanf("%d", &h) == 1) {
		if (z == NULL) {
			z = (CISLO *) malloc(sizeof(CISLO));
			p = z;
		}
		else {
			p->dalsi = (CISLO *) malloc(sizeof(CISLO));
			p = p->dalsi;
		}
		p->hod = h;
		p->dalsi = NULL;
	}
	return z;
}


int main() {
	CISLO *zoznam;
	zoznam = nacitaj();
	if (opakuju(zoznam))
		printf("Opakovanie\n");
	else
		printf("Prvky sa neopakuju\n");

	return 0;
}
