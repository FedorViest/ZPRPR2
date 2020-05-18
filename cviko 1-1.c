/*#include <stdio.h>

int main(){
    int n, i[100], p=0, cislo=0;
    scanf("%d", &n);
    if (n>=0 && n<=10){
        for(p=0; p<n; p++)
                scanf("%d", &i[p]);
        if(i[p]*2<i[p+1])
            printf("Postupnost je spravna\n");
        else
            printf("Postupnost je nespravna\n");
    }
    printf("%d", 103177%253);

    return 0;
}*/


#include <stdio.h>
#include <limits.h>
#define MAX_DOMY 20

//Zadefinovanie premennych, pre 2D maticu,
int domy[MAX_DOMY][MAX_DOMY], navstivene[MAX_DOMY];
int pocet_domov, cena=0;

void vypis();
void min_cena(int mesto);
int problem_obchodneho_cestujuceho(int mesto);

int main(){
    while (scanf("%d",&pocet_domov) > 0){
        if (pocet_domov < 0 || pocet_domov > 20){
            printf("Zly vstup\n");
            continue;
        }
        //Vynulovanie ceny, kvoli vstupom, ak nevynulujem na zaciatku cyklu,
        //cena ostane ulozena a nasledujuca hdnota sa prirata k predoslej
        cena = 0;
        //Nacitavanie hodnot do matice
        for(int i = 0; i < pocet_domov; i++){
            for(int j = 0; j < pocet_domov; j++){
                scanf("%d", &domy[i][j]);
            }
            //Vzdy nastavim aktualne miesto na ktorom sa prave nachadzam na 0
            navstivene[i]=0;
        }
        //Volanie metody na najdenie minimalneho casu od mesta 0 (prveho mesta)
        min_cena(0);
        //Volanie metody vypis na vypisanie najmensieho casu
        vypis();
        //Pridanie '\n' kvoli prehladnosti
        putchar('\n');
    }
    return 0;
}

int problem_obchodneho_cestujuceho(int mesto){
    //Inicialiujem najblizsie mesto na nejaku vysoku hodnotu
	int najblizsie_mesto=INT_MAX;
	int min=INT_MAX, temp;
	//For cyklus na zapisanie najkratsej trasy do premennej 'min' v danom riadku
	for(int i=0; i < pocet_domov; i++){
        //Podmienka ci sa nachadzam v matici na hodnote 0 - tym padom viem ze toto je pozicia z ktorej sa chcem pohnut,
        //lebo nemozem z nejakeho domu ist do toho v ktorom som, napr. (0,0), (1,1), (2,2), ...
		if((domy[mesto][i] != 0) && (navstivene[i] == 0)){
                if(domy[mesto][i] < min){
                    min = domy[i][mesto] + domy[mesto][i];
                    temp = domy[mesto][i];
                    najblizsie_mesto = i;
                }
			}
	}
	//Tu sa zapise najnizsia hodnota do premennej cena, spolu s predoslymi riadkami
	if(min!=INT_MAX)
		cena+=temp;
	return najblizsie_mesto;
}

void min_cena(int mesto){
    //Inicializacia premennych
    int najblizsie_mesto;
	navstivene[mesto]=1;
	//Volanie funkcie pre miesto ktore sa nachadza najblizsie ku mne a ulozenie do premennej
	najblizsie_mesto=problem_obchodneho_cestujuceho(mesto);
	//Kontrola ci je najblizsie_mesto nejaka random velka hodnota, ak je, znamena to, ze este sa nenaslo a hodnota sa nastavi na 0
	//tym padom viem, ze policko na ktorom sa nachadzam je 0
	//Je to podmienka na ukoncenie rekurzie
	if(najblizsie_mesto==INT_MAX)
	{
		najblizsie_mesto=0;
		cena+=domy[mesto][najblizsie_mesto];
		return;
	}
	//Volanie rekurzie
	min_cena(najblizsie_mesto);
}

//Pomocna funkcia na vypis najmensieho casu
void vypis(){
	printf("\nCas:");
	printf("%d\n",cena);
}
