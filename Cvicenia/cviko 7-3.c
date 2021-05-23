// uloha7-3.c -- Fedor Viest, 4.4.2020 08:18

// vypis zamestnanca (jeho adresy) s najvyssim platom
// vypis zamestnanca (jeho adresy) s najdlhsim menom
// vyuzitie struktury v strukture
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100  // max. pocet struktur v poli
#define SUBOR "zamestnanci.txt"

// typ pre adresu
typedef struct {
  char ulica[30];
  int cislo;
} ADRESA;

// typ pre osobu (zamestnanca)
typedef struct  {
  char meno[30];
  ADRESA adresa;
  double plat;
} OSOBA;

// nacitanie zamestnancov zo suboru
int nacitaj(OSOBA zam[]) {
  int n=0;
  FILE *f;

  if((f = fopen(SUBOR, "r")) == NULL) {
    printf("Nepodarilo sa otvorit subor\n");
    return 0;
  }
  while(n<N && fscanf(f, "%s", zam[n].meno) == 1) {
    fscanf(f, "%s", zam[n].adresa.ulica);
    fscanf(f, "%d", &zam[n].adresa.cislo);
    fscanf(f, "%lf", &zam[n].plat);
    n++;
  }
  fclose(f);
  return n;
}
int vymaz(){

}

int main() {
  int i, n, kto = 0;
  double max = 0.0, pom;
  OSOBA ludia[N];

  n = nacitaj(ludia); // n je pocet prvkov pola so zamestnancami

  float num;
  scanf("%lf", &num);

  // najdenie zamestnanca s najvyssim platom
  for (i = 0; i < n; i++) {
    if((pom = ludia[i].plat) > max) {
      max = pom;
      kto = i;
    }
  }
  printf("Zamestnanec s najvyssim platom %s byva: %s %d\n",
    ludia[kto].meno, ludia[kto].adresa.ulica, ludia[kto].adresa.cislo);

  OSOBA *p_kto = ludia, *p_pom;
  int d, maxd = strlen(p_kto->meno);

  // najdenie zamestnanca s najdlhsim menom
  for (p_pom = ludia + 1; p_pom < ludia + n; p_pom++) {
    if ((d = strlen(p_pom->meno)) > maxd) {
      p_kto = p_pom;
      maxd = d;
    }
  }

  printf("Zamestnanec s najdlhsim menom %s byva: %s %d\n",
    p_kto->meno, p_kto->adresa.ulica, p_kto->adresa.cislo);
  return 0;
}
