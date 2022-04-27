#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STARTSIZE 151
#define BUFSIZE 1024
#define STRARR 4
#define TRUE 1
#define FALSE !TRUE
#define COUNTERLIMIT 3
#define MAXHELDBYTRAINER 6
#define REMOVE_ENTER(c) (c) == '\n' ? (c) = '\0' : (c)

enum pokestruct
{
    NUMBR,
    NAME,
    TYPE1,
    TYPE2
};

typedef struct pokemon
{
    int ID; // A number given to Pokémons to be recognized by serial int
    char *number; //It starts with #
    char *name;
    char *type1;
    char *type2; // Can be NULL for some Pokémons
} pokemon;

typedef struct trainer
{
    char *firstName;
    char *lastName;
    pokemon *pokemonsInBank;             // The number of Pokémons the trainer have
    pokemon pokemonsHeldByTheTrainer[6]; // The Pokémons currently held by the trainer
} trainer;

//----trainer functions----//
trainer create_change_trainer(char *buff, int choice);
void capture(pokemon *pokebank, trainer *train, int lastindex, int *IDcount, int *last_oak);
int searchforspace(pokemon *pokemonsHeldByTheTrainer);
void switch_pokemons(trainer *train, int lastindex, int *last_oak);
void swap_location(pokemon *des, pokemon *src);
void release_pokemon(trainer *train, int lastindex, int *last_oak);

//----pokemons functions----//
int is_Exist_In_Bank(pokemon *pokebank, int last_index, char str[]);

//----file import functions----//
char **load2arr(char **s, char buff[], int last_index, pokemon *pokebank);
pokemon *import_file(pokemon *pokebank, int *lastindex, char buff[]);
void print_2_export(FILE *export, pokemon *organizer, int last_index);
void load2organizer(pokemon *pokebank ,pokemon *organizer, int last_index);

//----exporting to files----//
void export_type(pokemon *pokebank, int last_index);
void export_alphabet(pokemon *pokebank, int last_index);

//----printing functuions----//
void print_pokebank(pokemon *bank, int last_index);
void print_held(pokemon *pokemonsHeldByTheTrainer);
void print_oak(pokemon *pokmonsInBank, int last_oak);
int print_by_type(char *type, pokemon *pokebank, int lastindex);

//----mrmory functions----//
pokemon *Add_pokeslot(pokemon *pokebank, int *lastindex);
pokemon *remove_pokeslot(pokemon *pokebank, int *lastindex);
int malloc_check(void *ptr);
void freebank(pokemon *bank, int last_index);