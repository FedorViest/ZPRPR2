// uloha9-1.c -- Fedor Viest, 6.5.2020 18:16

#include <stdio.h>
#include <stdlib.h>

typedef struct Polozka
{
  int cislo;
  struct Polozka *dalsi;
} POLOZKA;

POLOZKA *nacitaj();
void vypis(POLOZKA *prvy);

void zmaz(POLOZKA *prvy, int k)
{
  POLOZKA *current = prvy;
  if (prvy == NULL){
    return;
  }
  if (k == 0 && prvy->dalsi == NULL){
    free(prvy);
    printf("Prazdny zoznam\n");
  }
  if (k == 0  && prvy != NULL){
    POLOZKA *temp = prvy;
    prvy = prvy->dalsi;
    free(temp);
  }
  if (k == 3){
    int count = 0;
    while (current!=NULL){
      count++;
      if (count == 3){
        current->dalsi = NULL;
        free(current->dalsi);
      }
      current = current->dalsi;
    }
  }
  current = prvy;
  for (int i = 0; current->dalsi != NULL && i < k - 1 ; i++){
    if (current != NULL && current->dalsi != NULL){
      return;
    }
  }
    POLOZKA *temp = current->dalsi->dalsi;
    free(current->dalsi);
    current->dalsi = temp;
  // sem napis svoje riesenie

}

int main()
{
  int k;
  POLOZKA *prvy;
  scanf("%d", &k);
  prvy = nacitaj(); // nacitaj zoznam
  zmaz(prvy, k);
  vypis(prvy); // vypis zoznam
  return 0;
}
