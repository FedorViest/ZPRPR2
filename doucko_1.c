#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

void vypis(int pole[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%d ", pole[i]);
    }
}
int sucet_prvkov (int pole[], int n){
    int suma=0, i;
    for (i=0; i<n; i++){
        suma+=pole[i];
    }
    return suma;

}
int najmensia(int pole[], int n){
    int mini=INT_MAX, i;
    for (i=0; i<n; i++){
        if(pole[i]<mini)
            mini=pole[i];
    }
    return mini;
}
void nasobenie(int pole[], int n, int nasobenie){
    int i;
    for (i=0; i<n; i++){
        pole[i]*=nasobenie;
    }
}

typedef struct{
    float koren1, koren2;
    bool mariesenie;

} tVysledok;

tVysledok kvadraticka(float a, float b, float c){
    tVysledok v;
    float diskriminant;
    diskriminant=b*b - 4*a*c;
    if (diskriminant<0){
        v.mariesenie=false;
        return v;
    }
    else
        v.mariesenie=true;
    v.koren1= (-b+ sqrt(diskriminant))/(2*a);
    v.koren2= (-b- sqrt(diskriminant))/(2*a);
    return v;
}
void rekurzia(int n){
    if (n<0)
        return;
    else{
        rekurzia(n-1);
        printf("%d", n);
        rekurzia(n-1);
    }

}

int main(){
    int pole[5]={1, 2, 3, 4, 5};
    int n=5, cislo=10;
    vypis(pole, n);
    printf("\n%d", sucet_prvkov(pole, n));
    printf("\n%d", najmensia(pole, n));
    nasobenie(pole, n, cislo);
    vypis(pole, n);
    tVysledok vysledok;
    vysledok=kvadraticka(1,2,-8);
    if (!vysledok.mariesenie)
        printf("Nema riesenie");
    else{
        printf("%.2f\n", vysledok.koren1);
        printf("%.2f", vysledok.koren2);
        }
    rekurzia (3);
    return 0;
}
