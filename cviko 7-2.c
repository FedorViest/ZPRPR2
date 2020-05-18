#include <stdio.h>


typedef struct{
    int den;
    int mesiac;
    int rok;
}DATUM;

int pocet_dni(DATUM prvy_datum, DATUM druhy_datum){
    int den1 = 0, den2 = 0, rozdiel = 0, dni = 0, roky = 0;
    for (int i=0; i<prvy_datum.mesiac; i++){
        if (i == 2){
            den1+=28;
        }
        if (i%2==1 || i==8){
            den1+=31;
        }
        else{
            den1+=30;
        }
    }
    den1 += prvy_datum.den;
    //printf("\n%d\n", den1);
    for (int i=0; i<druhy_datum.mesiac; i++){
        if (i == 2){
            den2+=28;
        }
        if (i%2==1 || i==8){
            den2+=31;
        }
        else{
            den2+=30;
        }
    }
    den2 += druhy_datum.den;
    //printf("\n%d\n", den2);
    dni = den2 - den1;
    //printf("\n%d\n", dni);
    roky = druhy_datum.rok * 365 - prvy_datum.rok * 365;
    //printf("\n%d\n", roky);
    rozdiel = dni + roky;
    //printf("%d", rozdiel);
    return rozdiel;
}


int main(){
    DATUM prvy, druhy;
    int p;
    scanf("%d.%d.%d", &prvy.den, &prvy.mesiac, &prvy.rok);
    scanf("%d.%d.%d", &druhy.den, &druhy.mesiac, &druhy.rok);
    p=pocet_dni(prvy, druhy);

    if (p>0){
        printf("%d", p);
    }
    else{
        printf("Vymente datumy");
    }


    return 0;
}
