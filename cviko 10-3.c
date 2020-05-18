// uloha10-3.c -- Fedor Viest, 1.5.2020 17:20

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct uzol {
    int hod;
    struct uzol *lavy;
    struct uzol *pravy;
} UZOL;

// vypis stromu: inorder
void vypisInorder(UZOL *s) {
  // sem napis svoje riesenie
  if (s==NULL){
     printf("-");
  }
  else{
     printf("(");
     vypisInorder(s->lavy);
     printf(" ");
     printf("%d", s->hod);
     printf(" ");
     vypisInorder(s->pravy);
     printf(")");

  }
}

void pridajDoStromu(UZOL *s, int  k);
UZOL *vytvorUzol(int k);

int main(void) {
   UZOL *koren;
   int k;

   koren = NULL;
   while (scanf("%d", &k) == 1) {
      if (koren == NULL) koren = vytvorUzol(k);
      else pridajDoStromu(koren, k);
   }
   vypisInorder(koren);
   return 0;
}

// pridanie uzla s hodnotou k do stromu
void pridajDoStromu(UZOL *s, int k) {
   	if (k < s->hod) {
   		if (s->lavy == NULL)
   			s->lavy = vytvorUzol(k);
   		else pridajDoStromu(s->lavy, k);
   	}
    else if (k > s->hod) {
   		if (s->pravy == NULL)
	      	s->pravy = vytvorUzol(k);
   		else pridajDoStromu(s->pravy, k);
	}
}

// vytvorenie uzla
UZOL *vytvorUzol(int k) {
   UZOL *u = (UZOL *) malloc(sizeof(UZOL));
   u->hod = k;
   u->lavy = u->pravy = NULL;
   return u;
}
