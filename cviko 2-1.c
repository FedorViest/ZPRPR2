#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(){
    srand((unsigned)time(NULL));
    FILE *fr;
    fr=fopen("hadanka.txt", "r");
    char c, pole[1000];
    int slovo=0, i=0;
    int count;
    fscanf(fr, "%d", &count);

    int nahodne=rand()%(count - 1) + 1;
    for (i=0; i<count; i++){
        fscanf(fr, "%s", pole);
        if (i==nahodne)
            break;
    }
    /*printf("%d\n", slovo);
    printf("%d", nahodne);
    printf("%s\n", pole);
    /*for (i=0; i<strlen(pole); i++)
        printf("%c", pole[i]);
        */
    char slovo_pouzivatela[100];
    bool uhadol=false;
    char volba;
    char pismeno[5];
    bool maska[100]={false};
    while(!uhadol){
        scanf("%c", &volba);
        if(volba=='s'){
            scanf("%s", slovo_pouzivatela);
            if (strcmp(slovo_pouzivatela, pole)==0){
                printf("Uhadol si slovo\nSlovo bolo %s", pole);
                uhadol=true;
            }
        }
        else if(volba=='p'){
            scanf("%s", &pismeno);
            //Kontrola ci sa pismeno rovna uhadnutemu
            for (i=0; i<strlen(pole); i++){
                if (pismeno[0]==pole[i])
                    maska[i]=true;
            }
            //Vypis slova, ak je 0 vypise _
            for (i=0; i<strlen(pole); i++){
                if (maska[i]==true)
                    printf("%c", pole[i]);
                else
                    printf("_");
            }
            printf("\n");
            //Kontrola ci uz uhadol slovo po pismenach
            int sum=0;
            for (i=0; i<strlen(pole); i++){
                sum+=maska[i];
            }
            if (sum==strlen(pole)){
                printf("\nUhadol si slovo\nSlovo bolo %s", pole);
                uhadol=true;
            }
        }

    }
    pole[i]='\0';


    return 0;
}
