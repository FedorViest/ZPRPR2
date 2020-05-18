#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* spojRetazce(char* str1, char* str2) {

	// TODO sem doplnte svoj kod
	char *spolu;
	int n, i, p=0, q=0;
	n=strlen(str1)+strlen(str2);
	if ((spolu= (char *) malloc(n*sizeof(char)))==NULL){
        printf("Nie je dostatok pamate\n");
        exit(1);
	}
	for (i=0; i<n; i++){
        if (i%2==0 && p<strlen(str1)){
            spolu[i]=str1[p];
            p++;
        }
        else if (i%2==1 && q<strlen(str2)){
            spolu[i]=str2[q];
            q++;
        }
        else if (p<strlen(str1)){
            spolu[i]=str1[p];
            p++;
        }
        else {
            spolu[i]=str2[q];
            q++;
        }
	}
	return spolu;
	free(spolu);
}

int main() {

	char str1[100], str2[100], * res;

	scanf("%99s%99s", str1, str2);

	res = spojRetazce(str1, str2);

	printf("%s\n", res);

}
