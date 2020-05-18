// uloha9-4.c -- Fedor Viest, 6.5.2020 20:03

#include <stdio.h>
#include <stdlib.h>

typedef struct hodnoty{
    int hodnota;
    struct hodnoty *dalsia;
} HODNOTY;

HODNOTY *pridaj(HODNOTY *zac, int hodnota,int *biggest){
    HODNOTY *new = NULL;
    HODNOTY *cur = zac;
    HODNOTY *save = NULL;

    if(hodnota>*biggest){
        *biggest=hodnota;
    }

    if(zac == NULL){
        zac=malloc(sizeof(HODNOTY));
        zac->hodnota=hodnota;
        zac->dalsia=NULL;
    }
    else{
        new=malloc(sizeof(HODNOTY));
        if(*biggest==hodnota){
            while(cur->dalsia!=NULL){
                save=cur;
                cur=cur->dalsia;
            }
            cur->dalsia=new;
            new->hodnota=hodnota;
            new->dalsia=NULL;
            return zac;
        }


        while(cur->hodnota < hodnota){
            save=cur;
            cur=cur->dalsia;
        }
        if(cur==zac){
            new->hodnota=hodnota;
            new->dalsia=cur;
        }
        else if(save->dalsia == NULL){
            cur->dalsia=new;
            new->hodnota=hodnota;
            new->dalsia=NULL;
        }
        else{
            save->dalsia=new;
            new->hodnota=hodnota;
            new->dalsia=cur;
        }

    }
    if(cur==zac){
        return new;
    }
    return zac;
}
void vypisElementy(HODNOTY *zac,int biggest){
    HODNOTY *cur = zac;
    while(cur != NULL){
        printf("%d ", cur->hodnota);
        if(cur->hodnota!=biggest && cur->dalsia!=NULL)
            printf("-> ");
        cur=cur->dalsia;
    }
}
int main() {
    HODNOTY *zac = NULL;
    int cislo, biggest=0;

    while(scanf("%d",&cislo)==1){
        zac = pridaj(zac, cislo,&biggest);
        vypisElementy(zac,biggest);
        putchar('\n');
    }
    return 0;
}
