#include <stdio.h>

void vloz(int cislo, int pole[], int n){
    int temp;
    if (n<=0){
        pole[0]=cislo;
        return;
    }
    else{
        if (cislo>pole[0]){
            vloz(cislo, pole+1, n-1);
        }
        else{
            temp=pole[0];
            pole[0]=cislo;
            vloz(temp, pole+1, n-1);

        }
    }
}
int main(){
    int pole[100]={-45, -15, 0, 28, 56, 685};
    for (int i=0; i<6; i++)
        printf("%d ", pole[i]);
    vloz(45, pole, 6);
    for (int i=0; i<7; i++)
        printf("%d ", pole[i]);
    printf("\n");
    return 0;
}
