#define N 10

#include <stdio.h>
#include <stdlib.h>

int *vloz(int cislo, int *pole, int *m, int *n) {
    if (*n >= *m) {
        realloc(pole, (*n + N) * sizeof(int));
        *m = *n + N;
    }

    for (int i = *n - 1; i >= 0; i--) {
        if (i == 0 && pole[0] > cislo) {
            pole[1] = pole[0];
            pole[0] = cislo;
        }
        else if (pole[i] >= cislo)
            pole[i + 1] = pole[i];
        else {
            pole[i + 1] = cislo;
            break;
        }
    }

    *n += 1;

    return pole;
}

int main() {

    int m = 10, n = 5;

    int *pole = NULL;
    pole = (int *) malloc(10 * sizeof(int));
    pole[0] = -7;
    pole[1] = 5;
    pole[2] = 7;
    pole[3] = 9;
    pole[4] = 20;

    vloz(8, pole, &m, &n);
    vloz(-5, pole, &m, &n);
    vloz(7, pole, &m, &n);
    vloz(25, pole, &m, &n);
    vloz(4, pole, &m, &n);
    vloz(-6, pole, &m, &n);
    vloz(8, pole, &m, &n);
    vloz(-5, pole, &m, &n);
    vloz(7, pole, &m, &n);
    vloz(25, pole, &m, &n);
    vloz(4, pole, &m, &n);
    vloz(-6, pole, &m, &n);
    vloz(612, pole, &m, &n);

    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
    printf("%d\n%d", m, n);

    free(pole);
    return 0;
}
