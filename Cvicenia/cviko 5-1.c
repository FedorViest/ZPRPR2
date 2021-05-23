#include <stdio.h>
#include <stdlib.h>
#define K 4

int porovnaj_mod(const void *a, const void *b){
    if ((*(int*)a%K) < (*(int*)b%K))
        return -1;
    else if ((*(int*)a%K) == (*(int*)b%K))
        return 0;
    else
        return 1;
}
int main(){
    int pole[100], i=0;
    while (scanf("%d", &pole[i++])==1){

    }
    i--;
    qsort(pole, i, sizeof(int), porovnaj_mod);
    for (int j=0; j<i; j++){
        printf("%d ", pole[j]);
    }
    putchar('\n');
    return 0;
}
