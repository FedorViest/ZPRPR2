#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void zatvorky(FILE *fr){
    char c;
    int zatvorka=0;
    bool v_zatvorke=true;
    fr=fopen("zatvorky.txt", "r");
    while ((c=getc(fr))!=EOF){
        if (c=='(' || c==')')
            v_zatvorke=!v_zatvorke;
        if (v_zatvorke)
            printf("%c", c);
    }
}

int main(){
    FILE *fr;
    zatvorky(fr);
    return 0;
}
