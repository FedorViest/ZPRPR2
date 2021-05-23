#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100 + 1
#define SUBOR "filmy.txt"

typedef struct {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
}FULL_NAME;

typedef struct actor {
    FULL_NAME full_name;
    int born;
    struct actor *next;
}ACTOR;

typedef struct movie {
    char title[MAX_LENGTH];
    int year;
    FULL_NAME director;
    struct actor *actors;
    struct movie *next;
}MOVIE;

ACTOR *create_actor(const char *name, const char *surname, int year);
MOVIE *create_movie(const char *title, const char *director_name, const char *director_surname, int year);
ACTOR *add_actor(ACTOR *start, ACTOR *new);
MOVIE *add_movie(MOVIE *start, MOVIE *new);

MOVIE *nacitaj();
void vypis(MOVIE *movie);
MOVIE *pridaj(MOVIE *start);
MOVIE *vymaz(MOVIE *start);
void filmy(MOVIE *movie);

void herci(MOVIE *movie);
MOVIE *search_movie(MOVIE *start, char *title);
ACTOR *search_actor(ACTOR *start, FULL_NAME *fullname);

void rok(MOVIE *start);
void del_actor(ACTOR *start);
ACTOR *add_actor_alphabetically(ACTOR *start, ACTOR *new);
int compare_actors(ACTOR *a, ACTOR *b);

void print_actors(ACTOR *start);

void koniec(MOVIE *movie);
int is_empty(MOVIE *movie);

int main() {
    char handler[MAX_LENGTH];
    MOVIE *movies = NULL;
    while (1){
        //Nacitavanie prikazov
        scanf("%s", handler);
        //Vycistenie buffera
        fseek(stdin, 0, SEEK_END);
        if (strcmp(handler, "nacitaj") == 0){
            movies = nacitaj();
        }
        else if (strcmp(handler, "pridaj") == 0){
            movies = pridaj(movies);
        }
        else if (strcmp(handler, "vymaz") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                movies = vymaz(movies);
            }
        }
        else if (strcmp(handler, "vypis") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                vypis(movies);
            }
        }
        else if (strcmp(handler, "filmy") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                filmy(movies);
            }
        }
        else if (strcmp(handler, "herci") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                herci(movies);
            }
        }
        else if (strcmp(handler, "rok") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                rok(movies);
            }
        }
        else if (strcmp(handler, "koniec") == 0){
            if (is_empty(movies)){
                printf("Nie je nacitane.\n");
            }
            else {
                koniec(movies);
                break;
            }
        }
        else {
            printf("Nespravny vstup.\n");
        }
    }
    return 0;
}

//Funkcia na vytvorenie herca
ACTOR *create_actor(const char *name, const char *surname, int year){
    //Alokovanie miesta o velkosti struktury
    ACTOR *actor = (ACTOR*) malloc(sizeof(ACTOR));
    //Nastavenie mena, priezviska a datumu narodenia do struktury
    strcpy(actor->full_name.name, name);
    strcpy(actor->full_name.surname, surname);
    actor->born = year;
    //Vzdy si nastavim za poslednym zaznamom NULL
    actor->next = NULL;
    return actor;
}

MOVIE *create_movie(const char *title, const char *director_name, const char *director_surname, int year){
    //Alokacia miesta o velkosti struktury
    MOVIE *movie = (MOVIE*) malloc(sizeof(MOVIE));
    //Nacitavanie nazvu, rezisera a rok vydania do struktury
    strcpy(movie->title, title);
    strcpy(movie->director.name, director_name);
    strcpy(movie->director.surname, director_surname);
    movie->year = year;
    //Nastavenie za poslednycm zaznamom hodnotu NULL
    movie->actors = NULL;
    movie->next = NULL;
    return movie;
}

ACTOR *add_actor(ACTOR *start, ACTOR *new){
    //Osetrenie pripadu ak je struktura prazdna, returnem new
    if (start == NULL){
        return new;
    }
    //Nastavenie pointru na zaciatok
    ACTOR *current = start;
    //Kontrolujem ci sa nenachadzam na konci zoznamu
    while (current->next!=NULL){
        //Nastavenie aktualnej pozicie na dalsiu
        current = current->next;
    }
    current->next = new;
    return start;
}

MOVIE *add_movie(MOVIE *start, MOVIE *new){
    //Osetrenie pripadu ak je struktura prazdna, returnem new
    if (start == NULL) {
        return new;
    }
    //Nastavenie pointru na zaciatok
    MOVIE *current = start;
    //Check ci sa nenachadzam na konci zoznamu
    while (current->next!=NULL){
        //Nastavenie aktualnej pozicie na dalsiu
        current = current->next;
    }
    //Nastavenie "dalsej" pozicie na novu
    current->next = new;
    return start;
}

MOVIE *nacitaj(){
    FILE *file = fopen(SUBOR, "r");
    //Osetrenie otvarania suboru
    if (file == NULL){
        printf("Subor sa nepodarilo otvoit.\n");
        exit(1);
    }
    MOVIE *start = NULL;

    while (!feof(file)){
        //Zadelkarovanie premennych
        char title[MAX_LENGTH];
        int year;
        char director_name[MAX_LENGTH];
        char director_surname[MAX_LENGTH];


        fgets(title, MAX_LENGTH, file);
        //Zbavenie sa '\n'
        title[strlen(title)-1] = '\0';
        //Nacitavanie hodnot do premennych
        fscanf(file, "%d\n", &year);
        fscanf(file, "%100s %100s", director_name, director_surname);

        MOVIE *movie = create_movie(title, director_name, director_surname, year);
        //Odstranenie '\n'
        fgetc(file);
        char c;
        while ((c = fgetc(file)) == '*') {
            //Zadeklarovanie premennych
            char actor_first[MAX_LENGTH];
            char actor_last[MAX_LENGTH];
            int born = 0;
            fscanf(file, "%100s %100s %d\n", actor_first, actor_last, &born);
            //Metoda na vytvorenie herca
            ACTOR *actor = create_actor(actor_first, actor_last, born);
            //Zapisanie hercov do filmov
            movie->actors = add_actor(movie->actors, actor);
        }
        ungetc(c, file);
        //Nastavenie zaciatku na prvy film v zozname
        start = add_movie(start, movie);
    }
    //Osetrenie zatvarania suboru
    if (fclose(file) == EOF){
        printf("Subor sa nepodarilo zatvorit.\n");
        exit(1);
    }
    return start;
}

void vypis(MOVIE *movie){
    MOVIE *current = movie;
    //Cyklus na vypis informacii o filme
    while (current != NULL){
        printf("%s (%d) %s %s\n", current->title, current->year, current->director.name, current->director.surname);
        printf("\tHraju: ");
        print_actors(current->actors);
        //Nastavenie aktualnej pozicie na dalsiu
        current = current->next;
    }
}

MOVIE *pridaj(MOVIE *start) {
    //Zadeklarovanie premennych
    char title[MAX_LENGTH];
    int year;
    char director_first[MAX_LENGTH], director_last[MAX_LENGTH];
    char actor_first[MAX_LENGTH], actor_last[MAX_LENGTH];
    int born;
    //Nacitanie nazvu, roku vydania a rezisera filmu
    fgets(title, MAX_LENGTH, stdin);
    title[strlen(title) - 1] = '\0';
    scanf("%d", &year);
    scanf("%100s %100s", director_first, director_last);
    //Volanie metody na vytvorenie filmu
    MOVIE *movie = create_movie(title, director_first, director_last, year);
    movie = realloc(movie, 1 + sizeof(MOVIE));
    //Cyklus na nacitavanie hercov vo filme
    while (1) {
        scanf("%100s", actor_first);
        //Osetrenie ak je prvy znak v mene herca a zaroven dlzka prveho mena je 1 '*', cyklus skonci
        if (strlen(actor_first) == 1 && actor_first[0] == '*')
            break;
        //Nacitavanie priezviska herca a rok narodenia
        scanf("%100s %d", actor_last, &born);
        //Volanie metody na vytvorenie noveho herca a nasledne volanie funkcie na pridanie herca do filmu
        ACTOR *actor = create_actor(actor_first, actor_last, born);
        movie->actors = add_actor(movie->actors, actor);
    }
    //Osetrenie pripadu ak je start spajaneho zoznamu NULL
    start = add_movie(start, movie);
    return start;
}

MOVIE *vymaz(MOVIE *start){
    MOVIE *current = start;
    //Kontrola ci je zoznam prazdny
    if (current == NULL){
        return start;
    }
    //Nacitanie do premennej
    char del_title[MAX_LENGTH];
    fgets(del_title, MAX_LENGTH, stdin);
    del_title[strlen(del_title)-1] = '\0';
    //Porovnanie ci sa aktualny nazov rovna nacitanemu (v tomto pripade na prvej pozicii)
    if (strcmp(current->title, del_title) == 0){
        //Vytvorenie temp, aby som mohol nasledne uolnit pamat a vratit ten temp
        MOVIE *temp = current->next;
        free(current);
        return temp;
    }
    //Vsetky ostatne pripady
    while (current->next != NULL) {
        if (strcmp(current->next->title, del_title) == 0) {
            //Nastavujem temp o 2 dalej
            MOVIE *temp = current->next->next;
            //Uvolnenie pamate
            free(current->next);
            //Nastavenie nasledujuceho zaznamu podla premennej temp
            current->next = temp;
            return start;
        }
        current = current->next;
    }
    return start;
}
void filmy(MOVIE *movie){
    MOVIE *current = movie;
    //Nacitavanie do poli
    char first_name[MAX_LENGTH];
    char last_name[MAX_LENGTH];
    scanf("%100s %100s", first_name, last_name);
    while (current != NULL){
        ACTOR *current_actor = current->actors;
        //Prechadzanie medzi vsetkymi hercami pre 1 film
        while (current_actor != NULL){
            //Porovnavanie a nasledny vypis ak je podmienka splnena
            if ( (strcmp(first_name, current_actor->full_name.name) == 0) &&
                 (strcmp(last_name, current_actor->full_name.surname) == 0) ) {
                printf("%s (%d)\n", current->title, current->year);
            }
            current_actor =current_actor->next;
        }
        current = current->next;
    }
}

//Pomocna funkcia na najdenie nazvu filmu v zozname
MOVIE *search_movie(MOVIE *start, char *title){
    MOVIE *current = start;
    while (current != NULL){
        //Ak najdem, vratim tu poziciu na ktorej som nasiel
        if (strcmp(current->title, title) == 0){
            return current;
        }
        current = current->next;
    }
    //Inac vratim NULL - nenasiel som
    return NULL;
}

//Pomocna funkcia na najdenie herca v zozname hercov
ACTOR *search_actor(ACTOR *start, FULL_NAME *fullname){
    ACTOR *current = start;
    while (current != NULL){
        //Ak najdem, vratim tu poziciu na ktorej som nasiel
        if (strcmp(current->full_name.name, fullname->name) == 0 && strcmp(current->full_name.surname, fullname->surname) == 0){
            return current;
        }
        current = current->next;
    }
    //Inak vratim NULL
    return NULL;
}

void herci(MOVIE *movie){
    //Nacitanie nazvov filmov do poli
    char title_one[MAX_LENGTH];
    char title_two[MAX_LENGTH];
    fgets(title_one, MAX_LENGTH, stdin);
    title_one[strlen(title_one)-1] = '\0';
    fgets(title_two, MAX_LENGTH, stdin);
    title_two[strlen(title_two)-1] = '\0';

    //Volanie pomocnych funkcii
    MOVIE *movie_first = search_movie(movie, title_one);
    MOVIE *movie_second = search_movie(movie, title_two);
    //Kontrola ci sa nasiel zaznam o filme, ak nie vypise sa nespravny vstup
    if (movie_first == NULL || movie_second == NULL){
        printf("Zly vstup.\n");
        return;
    }
    //Nastavenie hodnoty pre prvy nacitany film
    ACTOR *current_actor = movie_first->actors;
    while (current_actor != NULL) {
        //Porovnanie ci sa rovnaju
        if (search_actor(movie_second->actors, &current_actor->full_name)) {
            if (current_actor->next != NULL) {
                printf("%s %s (%d), ", current_actor->full_name.name, current_actor->full_name.surname,
                       current_actor->born);
            }
            else
                printf("%s %s (%d)", current_actor->full_name.name, current_actor->full_name.surname, current_actor->born);
        }
        current_actor = current_actor->next;
    }
    putchar('\n');
}

//Pomocna funkcia na vyps hercov
void print_actors(ACTOR *start){
    //Nastavenie pointra na start struktury
    ACTOR *current = start;
    //Kontrola ci sa uz nenachadzam nakonci a vypis
    while (current != NULL){
        printf("%s %s (%d)", current->full_name.name, current->full_name.surname, current->born);
        if (current->next){
            printf(", ");
        }
        //Nastavenie aktualnej pozicie na dalsiu
        current = current->next;
    }
    putchar('\n');
}

//Pomocna funkcia na zistenie ci je struktura prazdna alebo nie, ak je vrati 0, ak nie 1
int is_empty(MOVIE *movie){
    int flag = 0;
    if (movie == NULL){
        flag = 1;
        return flag;
    }
    return flag;
}

//Funkcia na uvolnenie pamate
void koniec(MOVIE *movie){
    MOVIE *current = movie;
    while (current != NULL){
        //Uvolnenie pre hercov
        ACTOR *current_actor = current->actors;
        while (current_actor != NULL){
            //Zadefinujem hodnotu premennej na nasledujuceho herca a uvolnim aktualneho herca, potom nastavim
            //aktualneho herca na premennu ktora ma v sebe nasledujuceho herca
            ACTOR *temp_actor = current_actor->next;
            free(current_actor);
            current_actor = temp_actor;
        }
        //Uvolnenie pre filmy
        //Robim to iste ako pre hercov
        MOVIE *temp = current->next;
        free(current);
        current = temp;
    }
}

//Funkcia na porovnavanie hercov
int compare_actors(ACTOR *a, ACTOR *b){
    //Volanie strcmp pre 2 priezvska
    int cmp_surname = strcmp(a->full_name.surname, b->full_name.surname);
    //Ak sa rovnaju priezviska skoci do dalsej vetvy
    if (cmp_surname == 0){
        int cmp_name = strcmp(a->full_name.name, b->full_name.name);
        //Ak sa rovnaju mena skoci na roky narodenia
        if (cmp_name == 0){
            if (a->born > b->born){
                return 1;
            }
            else if (a->born < b->born){
                return -1;
            }
            else {
                return 0;
            }
        }
        //Returne bud 1 alebo -1, ak 1, tak prvy herec ma vyssiu hodnotu ako druhy
        return cmp_name;
    }
    return cmp_surname;
}

//Pomocna funkcia na pridavanie hercov abecedne do zoznamu
ACTOR *add_actor_alphabetically(ACTOR *start, ACTOR *new_actor){
    //Volanie funkcie na vytvorenie noveho zaznamu
    ACTOR *new = create_actor(new_actor->full_name.name, new_actor->full_name.surname, new_actor->born);
    //Osetrenie pripadu ak je zoznam prazdny
    if (start == NULL){
        return new;
    }
    //Ak je v zozname iba 1 herec, ktory vyhovuje poziadavkam
    if (start->next == NULL){
        int cmp_result = compare_actors(start, new);
        //Ak je > 0, to znamena ze zaznamy treba vymenit
        if (cmp_result > 0){
            new->next = start;
            return new;
        }
        //Tu netreba menit poradie
        else if (cmp_result < 0){
            start->next = new;
            return start;
        }
        free(new);
        return start;
    }
    //Osetrenie pripadu ak musim zmenit zaciatok zoznamu
    if (compare_actors(start, new) > 0){
        new->next = start;
        return new;
    }
    ACTOR *current = start;
    while (current != NULL){
        int cmp_result = compare_actors(current, new);
        //Ak je viac ako 1 zaznam a zaroven zaznamy sa nerovnaju, tak len zapisem novy zaznam na dalsiu poziciu
        if (current->next == NULL && cmp_result != 0){
            current->next = new;
            return start;
        }
        //Ak je hodnota >0, to znamena ze musim vymenit poradie dvoch zaznamov
        else if (cmp_result > 0) {
            new->next = current->next;
            current->next = new;
            return start;
        }
        current = current->next;
    }
    free(new);
    return start;
}

//Pomocna funkcia na vymazanie zoznamu
void del_actor(ACTOR *start){
    ACTOR *current = start;
    while (current != NULL){
        ACTOR *temp = current->next;
        free(current);
        current = temp;
    }
}

void rok(MOVIE *start){
    int year;
    scanf("%d", &year);
    MOVIE *current = start;
    ACTOR *actors = NULL;
    while (current != NULL) {
        //Porovnavam ci zadany rok sa rovna aktualnemu roku
        if (current->year == year) {
            ACTOR *current_actor = current->actors;
            while (current_actor != NULL) {
                //Volanie metody na pridanie herca do zoznamu abecedne
                actors = add_actor_alphabetically(actors, current_actor);
                current_actor = current_actor->next;
            }
        }
        current = current->next;
    }
    //Volanie funkcii na vypis zoznamu a zmazanie zoznamu
    print_actors(actors);
    del_actor(actors);
}
