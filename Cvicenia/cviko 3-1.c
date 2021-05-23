#include <stdio.h>
#include <string.h>

int main(){
    char sprava[100];
    char sifra[100];
    char posun[100];
    int i;
    int j;
    scanf("%s", sprava);
    scanf("%s", sifra);
    for (i=0; i<strlen(sprava); i++){
        posun[i]=sifra[i%strlen(sifra)];
    }
    for (i=0; i<strlen(sprava); i++){
        int kluc=sprava[i]+(posun[i]-'A')%26;
        j=kluc;
        sprava[i]=kluc;
        if (sprava[i]>'Z')
            sprava[i]=kluc-'Z'%'A'-1;
        printf("%c", sprava[i]);
    }
    printf("\n");

    return 0;
}
