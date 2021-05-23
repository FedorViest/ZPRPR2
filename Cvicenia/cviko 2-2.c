#include <stdio.h>

void vloz(int cislo, int pole[],int *n )
{
 int i;
 for (i = *n-1 ; i >= 0; i--)
 {
 if (cislo>pole[i] )
 break;
 pole[i+1] = pole[i];
 }
 pole[i+1] = cislo;
 (*n)++;
}




int main(){
    int cislo, n, i;
    scanf("%d", &n);
    int pole[n];
    for (i=0; i<n; i++){
        scanf("%d", &pole[i]);
    }
    scanf("%d", &cislo);
    vloz(cislo, pole, &n);
    for (i=0; i<n; i++){
        printf("%d ", pole[i]);
    }
    printf("\n");
    return 0;
}
