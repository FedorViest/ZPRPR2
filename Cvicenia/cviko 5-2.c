#include <stdio.h>
#include <ctype.h>


int number(char c){
    if (isdigit(c))
        return 1;
    else
        return 0;
}

int small_letter(char c){
    if (islower(c))
        return 1;
    else
        return 0;
}

int large_letter(char c){
    if (isupper(c))
        return 1;
    else
        return 0;
}

int white_char(char c){
    if (isspace(c) || iscntrl(c))
        return 1;
    else
        return 0;
}
int zisti(FILE *fr, int (*pointer)(char)){

    if ((fr=fopen("znaky.txt", "r"))==NULL){
        printf("Subor sa nepodarilo otvorit\n");
        return 0;
    }
    char c;
    int count=0;
    while ((c=getc(fr))!=EOF){
        if (pointer(c))
            count++;
    }
    if ((fclose(fr))==EOF){
        printf("Subor sa nepodarilo zatvorit\n");
        return 0;
    }
    return count;
}

int main(){
    FILE *fr;
    int count;
    int (*pointer)(char);
    char c, medzera;

    scanf("%d%c", &count, &medzera);
    for (int i=0; i<count; i++){
        scanf("%c%c", &c, &medzera);
        switch (c){
            case 'b':{
                printf("%d\n", zisti(fr, white_char));
                break;
            }
            case 'm':{
                printf("%d\n", zisti(fr, small_letter));
                break;
            }
            case 'v':{
                printf("%d\n", zisti(fr, large_letter));
                break;
            }
            case 'c':{
                printf("%d\n", zisti(fr, number));
                break;
            }
        }
    }
    return 0;
}
