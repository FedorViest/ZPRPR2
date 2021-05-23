#include <stdio.h>
#define N 20

int magicky(int pole[][N], int rozmer){
    int flag=0, sum_diagonal=0, sum_vertical=0, sum_horizontal=0;

    //diagonalne

    for (int riadok=0; riadok<rozmer; riadok++){
        for (int stlpec=0; stlpec<rozmer; stlpec++){
            if (riadok==stlpec){
                sum_diagonal+=pole[riadok][stlpec];
            }
        }
    }
    printf("\nDiagonalne: %d\n", sum_diagonal);

    //riadky

    for (int riadok=0; riadok<rozmer; riadok++){
        sum_horizontal=0;
        for (int stlpec=0; stlpec<rozmer; stlpec++){
            sum_horizontal+=pole[riadok][stlpec];
        }
        printf("\nHorizontalne %d: %d\n", riadok, sum_horizontal);
        if (sum_diagonal==sum_horizontal){
            flag=1;
        }
        else{
            flag=0;
            break;
        }
    }

    //stlpce

    for (int riadok=0; riadok<rozmer; riadok++){
        sum_vertical=0;
        for (int stlpec=0; stlpec<rozmer; stlpec++){
            sum_vertical+=pole[riadok][stlpec];
        }
        printf("\nVertikalne %d: %d\n", riadok, sum_vertical);
        if (sum_diagonal==sum_vertical)
            flag=1;
        else{
            flag=0;
            break;
        }
    }

    if (flag==1)
        return 1;
    else
        return 0;
}

int main(){
    int pole[N][N], rozmer;
    printf("Zadajte velkost stvorca:\n");
    scanf("%d", &rozmer);
    if (rozmer>N){
        printf("Zly vstup, max velkost je %d", N);
        return 0;
    }
    printf("Zadajte hodnoty stvorca:\n");
    for(int riadok=0; riadok<rozmer; riadok++){
        for(int stlpec=0; stlpec<rozmer; stlpec++){
                scanf("%d", &pole[riadok][stlpec]);

        }
    }
    printf("Vypis stvorca:\n");
    for (int riadok=0; riadok<rozmer; riadok++){
        for(int stlpec=0; stlpec<rozmer; stlpec++){
            printf("%d ", pole[riadok][stlpec]);
        }
        putchar('\n');
    }
    if (magicky(pole, rozmer))
        printf("\nStvorec je magicky\n");
    else
        printf("\nStvorec nie je magicky\n");
    return 0;
}
