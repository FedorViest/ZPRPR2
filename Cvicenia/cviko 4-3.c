#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define DEFAULT_SIZE 10
#define INCREASE_VALUE 5

bool isprime(int number) {
    for (int i = 2; i < sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int resize_if_required(int* pole, int elements, int size) {
    // elements is counting from zero + resize if we are almost full
    if (elements == size-2) {
        realloc(pole, size + INCREASE_VALUE * sizeof(int));
        size += INCREASE_VALUE;
    }

    return size;
}

int main() {
    FILE *fr;
    int *pole;
    int size = DEFAULT_SIZE;
    int elements = 0;

    pole = (int *) malloc( DEFAULT_SIZE * sizeof(int));

    if ((fr = fopen("cviko4.txt", "r")) == NULL) {
        printf("Subor sa nepodarilo otvorit\n");
        return 0;
    }

    // Citam cisla zo suboru
    while (fscanf(fr, "%d", &pole[elements]) != EOF) {
        size = resize_if_required(pole, elements, size);
        elements++;
    }

    // Vypisujem nacitane pole
    for (int i = 0; i < elements; i++) {
        printf("%d ", pole[i]);
    }
    putchar('\n');

    // Spocitavam prvky
    int sum = 0;
    for (int i = 0; i < elements; i++) {
        sum += pole[i];
    }

    int najblizsie = sum;
    while (!(isprime(najblizsie))) {
        najblizsie++;
    }

    int rozdiel = najblizsie - sum;

    if (rozdiel != 0) {
        size = resize_if_required(pole, elements, size);
        pole[elements++] = rozdiel;
    }

    sum = 0;
    for (int i = 0; i < elements; i++) {
        printf("%d ", pole[i]);
        sum += pole[i];
    }

    printf("\n%d", sum);

    if (fclose(fr) == EOF)
        printf("Subor sa nepodarilo zatvorit\n");

    return 0;
}
