// uloha8-3.c -- Fedor Viest, 28.4.2020 09:23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct clovek {
  char meno[N];
  int rocnik;
  struct clovek *dalsi;
} CLOVEK;

CLOVEK *vratMeno(CLOVEK *zac, char meno[]) {
  CLOVEK *akt = zac;

  while(akt != NULL) {
    if(!strcmp(akt->meno, meno))
      return akt;
    akt = akt->dalsi;
  }
  return NULL;
}

CLOVEK *pridajNaKoniec(CLOVEK *zac, CLOVEK *vloz){
  CLOVEK *akt = zac;

  if(zac == NULL) return vloz;
  while(akt->dalsi != NULL)
    akt = akt->dalsi;
  akt->dalsi = vloz;
  return zac;
}

CLOVEK *zmazZoznam(CLOVEK *zac) {
  CLOVEK *p;
  while (zac != NULL) {
    p = zac;
    zac = zac->dalsi;
    free(p);
  }
  return NULL;
}

int main() {
  CLOVEK *zac = NULL, *vloz = NULL;
  int i, n;

  scanf("%d", &n);

  for(i=0; i<n; i++) {
    vloz = (CLOVEK *) malloc(sizeof(CLOVEK));
    scanf("%s", vloz->meno);
    scanf("%d", &vloz->rocnik);
    vloz->dalsi = NULL;
    zac = pridajNaKoniec(zac, vloz);
  }
  char meno[30];
  scanf("%s", meno);
  CLOVEK *c = vratMeno(zac, meno);
  if (c!=NULL){
    printf("%d", c->rocnik);
  }
  else{
    printf("zaznam nenajdeny\n");
  }
  zac = zmazZoznam(zac);
  return 0;
}
