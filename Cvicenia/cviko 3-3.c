#include <stdio.h>

void nahrad(char str[]){
    char c;
    int i;
    if (str[0]=='\0')
        return;
    else{
        if (!((str[0]>='a' && str[0]<='z') || (str[0]>='A' && str[0]<='Z'))){
            str[0]='*';
        }
        nahrad(str+1);
    }

}

int main(){
    char pole[1000];
    scanf("%s", &pole);
    /*printf("%s\n", pole);
    printf("Nahradeny string:\n");*/
    nahrad(pole);
    printf("%s", pole);
    printf("\n");

    return 0;
}
