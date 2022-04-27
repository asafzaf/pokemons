// by asaf zafrir and rony zrihen

#include "pokemon_asaf_and_rony.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REMOVE_ENTER(c) (c) == '\n' ? (c) = '\0' : (c)

int last_index = 0;

int main(int argc, char *argv[])
{
    int last_index = 0;
    int IDcount = 1000;
    int last_oak = 0;
    pokemon *all_pokemon = NULL;
    char buff[BUFSIZE];
    trainer trainer;
    trainer = create_change_trainer(buff, 0);

    FILE *pokefile;

    all_pokemon = import_file(all_pokemon, &last_index, argv[1]);
    if (all_pokemon == NULL)
    {
        return 0;
    }
    // print_pokebank(all_pokemon, last_index);

    for (;;) /////////////////// the menu \\\\\\\\\\\\\\\\\\\\\\/
    {
        printf("\n-------------------------------------------\n             HELLO  %s %s !\n-------------------------------------------\n", trainer.firstName, trainer.lastName);
        printf("\n-------------------------------------------\n             CHOOSE AN OPTION:       \n-------------------------------------------\n");
        printf("1- Change Name      6- Capture Pokemon\n2- Upload           7- Switch Pokemons\n3- printpoke.       8- Release Pokemon\n4- Output by type   9- Print Trainer pokemons\n5- output sort...   10- Print Oak pokemons\n");
        printf("                0- Exit\n\n");
        int choise;
        char c;
        scanf("%d", &choise);
        c = getchar();
        switch (choise)
        {
        case 1: // change trainer name
        {
            trainer = create_change_trainer(buff, 1);
            break;
        }
        case 2: // load new list of pokemons (other gens)
        {
            pokemon *temp;
            temp = import_file(all_pokemon, &last_index, buff); // make free function!!!!
            if (temp == NULL)
            {
                printf("Something went wrong, file wasn't loaded\n");
            }
            all_pokemon = temp;
            print_pokebank(all_pokemon, last_index);
            break;
        }
        case 3: // print pokemons by types + count the list
        {
            printf("Please enter pokemon type: ");
            fgets(buff, BUFSIZE, stdin);
            REMOVE_ENTER(buff[strlen(buff) - 1]);
            print_by_type(buff, all_pokemon, last_index);

            break;
        }
        case 4: // export pokemons by type to new file
        {
            export_type(all_pokemon, last_index);
            break;
        }
        case 5: // export by a-z (you choosing the row) to new file
        {
            export_alphabet(all_pokemon, last_index);
            printf("\ncase 5 has finnished\n");
            break;
        }
        case 6: // cpture new pokemon
        {
            capture(all_pokemon, &trainer, last_index, &IDcount, &last_oak);
            break;
        }
        case 7: // switch between pokemons
        {
            switch_pokemons(&trainer, last_index, &last_oak);
            break;
        }
        case 8: // release pokemon
        {
            release_pokemon(&trainer, last_index, &last_oak);
            break;
        }
        case 9: // print all pokemons the held by the trainer
        {
            print_held(trainer.pokemonsHeldByTheTrainer);
            break;
        }
        case 10: // print all pokemons that at prof. oak
        {
            print_oak(trainer.pokemonsInBank, last_oak);
            break;
        }
        case 0: // Exit from program
            return 0;
        }
    }
}

/*/////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\*\
<------=================FUNTIONS=================----->
\*\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////*/

//----------------------------trainer functions----------------------------//

trainer create_change_trainer(char *buff, int choice)
{
    trainer new_trainer;
    if (choice == 1)
    {
        free(new_trainer.firstName);
        free(new_trainer.lastName);
    }

    printf("Please enter your first name: ");
    fgets(buff, BUFSIZE, stdin);
    new_trainer.firstName = (char *)malloc(strlen(buff) + 1);
    REMOVE_ENTER(buff[strlen(buff) - 1]);
    strcpy(new_trainer.firstName, buff);

    printf("\nPlease enter your last name: ");
    fgets(buff, BUFSIZE, stdin);
    new_trainer.lastName = (char *)malloc(strlen(buff) + 1);
    REMOVE_ENTER(buff[strlen(buff) - 1]);
    strcpy(new_trainer.lastName, buff);

    if (choice == 0)
    {
        for (int i = 0; i < MAXHELDBYTRAINER; ++i)
        {
            new_trainer.pokemonsHeldByTheTrainer[i].ID = 0;
            new_trainer.pokemonsHeldByTheTrainer[i].number = '\0';
            new_trainer.pokemonsHeldByTheTrainer[i].name = '\0';
            new_trainer.pokemonsHeldByTheTrainer[i].type1 = '\0';
            new_trainer.pokemonsHeldByTheTrainer[i].type2 = '\0';
            new_trainer.pokemonsInBank = '\0';
        }
    }
    return new_trainer;
}

void capture(pokemon *pokebank, trainer *train, int lastindex, int *IDcount, int *last_oak)
{
    char buff[BUFSIZE];
    int place;
    int pokemonindex;
    printf("Please enter pokemon name :");
    fgets(buff, BUFSIZE, stdin);
    REMOVE_ENTER(buff[strlen(buff) - 1]);
    pokemonindex = is_Exist_In_Bank(pokebank, lastindex, buff);
    // printf("Do you want to captue %s %s ?" , pokebank[i].number, pokebank[i].name, pokebank[i]);
    place = searchforspace(train->pokemonsHeldByTheTrainer);
    if (pokemonindex != -1)
    {
        if (place == -1) // prof oak - fuuuuuuuuuuuuuckkk prof oakkkkkkkkkkkkkkkk
        {
            pokemon *new_pokemon;
            new_pokemon = Add_pokeslot(train->pokemonsInBank, last_oak);
            if (new_pokemon == NULL)
            {
                printf("ERROR\n");
            }
            pokemon poke = pokebank[pokemonindex];
            char **new = (char **)malloc(STRARR * sizeof(char *));
            new[NUMBR] = (char *)malloc((strlen(poke.number) + 1) * sizeof(char));
            if (new[NUMBR] == NULL)
            {
                free(new[NUMBR]);
                printf("asd\n");
                return;
            }
            printf("IM HERE\n");
            new[NAME] = (char *)malloc((strlen(poke.name) + 1) * sizeof(char));
            if (new[NUMBR] == NULL)
            {
                free(new[NUMBR]);
                printf("asd\n");
                return;
            }
            new[TYPE1] = (char *)malloc((strlen(poke.type1) + 1) * sizeof(char));
            if (new[NUMBR] == NULL)
            {
                free(new[NUMBR]);
                printf("asd\n");
                return;
            }
            new[TYPE2] = (char *)malloc((strlen(poke.type2) + 1) * sizeof(char));
            if (new[NUMBR] == NULL)
            {
                free(new[NUMBR]);
                printf("asd\n");
                return;
            }

            //////////////////copyyyyyy

            strcpy(new[NUMBR], poke.number);
            strcpy(new[NAME], poke.name);
            strcpy(new[TYPE1], poke.type1);
            strcpy(new[TYPE2], poke.type2);

            train->pokemonsInBank = new_pokemon;
            train->pokemonsInBank[*last_oak].ID = ++(*IDcount);
            train->pokemonsInBank[*last_oak].number = new[NUMBR];
            train->pokemonsInBank[*last_oak].name = new[NAME];
            train->pokemonsInBank[*last_oak].type1 = new[TYPE1];
            train->pokemonsInBank[*last_oak].type2 = new[TYPE2];

            printf("\n%s (%s) was captured! placed in proff. Oak! , id - %d\n", train->pokemonsInBank[*last_oak].name, train->pokemonsInBank[*last_oak].number, train->pokemonsInBank[*last_oak].ID);
            printf("You have %d pokemons at Proffessor Samuel Oak.\n", (*last_oak) + 1);
        }
        else // capture to the hand
        {
            train->pokemonsHeldByTheTrainer[place].ID = ++(*IDcount);
            train->pokemonsHeldByTheTrainer[place].number = pokebank[pokemonindex].number;
            train->pokemonsHeldByTheTrainer[place].name = pokebank[pokemonindex].name;
            train->pokemonsHeldByTheTrainer[place].type1 = pokebank[pokemonindex].type1;
            train->pokemonsHeldByTheTrainer[place].type2 = pokebank[pokemonindex].type2;
            printf("\n%s (%s) was captured! placed in bag - slot %d, id - %d\n", train->pokemonsHeldByTheTrainer[place].name, train->pokemonsHeldByTheTrainer[place].number, place + 1, train->pokemonsHeldByTheTrainer[place].ID);

            // printf(9"test:\n ID- %d\n #- %s\nname- %s\ntype1- %s\ntype2- %s", pokemonsHeldByTheTrainer[place].ID, pokemonsHeldByTheTrainer[place].)
        }
    }
    else
        printf("No such a pokemon");
}

int searchforspace(pokemon *pokemonsHeldByTheTrainer)
{
    for (int i = 0; i < MAXHELDBYTRAINER; ++i)
    {
        if (pokemonsHeldByTheTrainer[i].ID == 0)
        {
            return i;
        }
    }
    return -1;
}

void switch_pokemons(trainer *train, int lastindex, int *last_oak)
{
    int depositID, importID;
    printf("Please enter Pokemon ID to deposit (To Oak):");
    scanf("%d", &depositID);
    printf("Please enter Pokemon ID to import (From Oak):");
    scanf("%d", &importID);
    pokemon *heldpoke, *oakpoke;
    pokemon temp;

    for (int i = 0; i < MAXHELDBYTRAINER; ++i) // search for pokemon to deposit (hend -> Oak)
    {
        if (train->pokemonsHeldByTheTrainer[i].ID == depositID) // if ID match - move pokemon from hend to temp
        {
            heldpoke = &(train->pokemonsHeldByTheTrainer[i]);
        }
        else
            printf("No pokemon to Deposit");
    }
    for (int j = 0; j < *last_oak; ++j) // search for pokemon to import (Oak -> hend)
    {
        if (train->pokemonsInBank[j].ID == importID) // if ID match - move pokemon from Oak to hand
        {
            oakpoke = &(train->pokemonsInBank[j]);
        }
        else
            printf("No pokemon to Import");
    }
    swap_location(heldpoke, oakpoke);
    printf("\nThe pokemons switched!\n");
}

void swap_location(pokemon *des, pokemon *src)
{
    int tt;
    tt = des->ID;
    des->ID = src->ID;
    src->ID = tt;
    char *temp;
    temp = des->name;
    des->name = src->name;
    src->name = temp;
    temp = des->number;
    des->number = src->number;
    src->number = temp;
    temp = des->type1;
    des->type1 = src->type1;
    src->type1 = temp;
    temp = des->type2;
    des->type2 = src->type2;
    src->type2 = temp;
    return;
}

void release_pokemon(trainer *train, int lastindex, int *last_oak)
{
    int tempID;
    printf("Please enter Pokemon ID :");
    scanf("%d", &tempID);

    for (int i = 0; i < MAXHELDBYTRAINER; ++i)
    {
        if (train->pokemonsHeldByTheTrainer[i].ID == tempID)
        {
            printf("\n%s (%s) was released! - from slot %d, id - %d\n", train->pokemonsHeldByTheTrainer[i].name, train->pokemonsHeldByTheTrainer[i].number, i + 1, train->pokemonsHeldByTheTrainer[i].ID);
            train->pokemonsHeldByTheTrainer[i].ID = 0;
            train->pokemonsHeldByTheTrainer[i].number = '\0';
            train->pokemonsHeldByTheTrainer[i].name = '\0';
            train->pokemonsHeldByTheTrainer[i].type1 = '\0';
            train->pokemonsHeldByTheTrainer[i].type2 = '\0';
            break;
        }
    }
    for (int i = 0; i < *last_oak; ++i)
    {
        if (train->pokemonsInBank[i].ID == tempID)
        {
            printf("\n%s (%s) was released! - from Prof Oak. ! , id - %d\n", train->pokemonsInBank[i].name, train->pokemonsInBank[i].number, train->pokemonsInBank[i].ID);
            train->pokemonsInBank[*last_oak].ID = 0;
            free(train->pokemonsInBank[i].number);
            free(train->pokemonsInBank[i].name);
            free(train->pokemonsInBank[i].type1);
            free(train->pokemonsInBank[i].type2);
            free(&(train->pokemonsInBank[i]));
            pokemon temp;

            for (int j = i + 1; j < *last_oak; ++j) // continue with sort
            {
                train->pokemonsInBank[i].ID = train->pokemonsInBank[j].ID;
                train->pokemonsInBank[i].number = train->pokemonsInBank[j].number;
                train->pokemonsInBank[i].name = train->pokemonsInBank[j].name;
                train->pokemonsInBank[i].type1 = train->pokemonsInBank[j].type1;
                train->pokemonsInBank[i].type2 = train->pokemonsInBank[j].type2;
            }
        }
    }
}

//----------------------------pokemons functions----------------------------//
int is_Exist_In_Bank(pokemon *pokebank, int last_index, char str[])
{
    int i;
    for (i = 0; i < last_index; i++)
    {
        if (!(strcmp(pokebank[i].number, str)) ||
            (!(strcmp(pokebank[i].name, str))))
        {
            return i; //  Num of index
        }
    }
    return -1;
}

//----------------------------file import functuions----------------------------//

char **load2arr(char **s, char buff[], int last_index, pokemon *pokebank)
{

    int i = 0;
    char *token = strtok(buff, " ");
    while (token != NULL)
    {
        if (i <= NAME && last_index)
        {
            if (is_Exist_In_Bank(pokebank, last_index, token) != -1)
            {
                printf("\"%s\" already exists in bank\n", token);
                i == NAME ? free(s[NAME]) : NULL;
                return s = NULL;
            }
        }
        s[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(s[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    if (i == TYPE2)
    {
        s[TYPE2] = "-";
    }
    return s;
}

pokemon *import_file(pokemon *pokebank, int *lastindex, char buff[])
{
    char file_name[BUFSIZE];
    int file_name_size;
    int counter; // user gets 3 tries to enter file name
    FILE *import;

    if (pokebank == NULL)
    {
        import = fopen(buff, "r");
        if (import == NULL)
        {
            printf("\"%s\" Was not found", buff);
            return NULL;
        }
        printf("Loading \"%s\"\n", buff);
    }
    else
    {
        for (counter = 0; counter < COUNTERLIMIT; counter++)
        {

            counter > 0 ? printf("Please try again: ") : printf("Please enter file path: ");
            fgets(file_name, BUFSIZE, stdin);
            file_name_size = strlen(file_name);
            REMOVE_ENTER(file_name[file_name_size - 1]); // cleaning up the \n off the string
            import = fopen(file_name, "r");

            if (import == NULL)
            {
                if (counter == COUNTERLIMIT - 1)
                {
                    printf("Out of tries\n");
                    return NULL;
                }
                printf("\"%s\" Was not found", file_name);
            }
            printf("Loading \"%s\"", file_name);
            break;
        }
    }
    pokemon *temp;
    while (fgets(buff, BUFSIZE, import) != NULL)
    {

        int bufflen = strlen(buff);
        REMOVE_ENTER(buff[bufflen - 1]);                     // removing \n from the last word of the line
        char **s = (char **)malloc(STRARR * sizeof(char *)); // creating dymanic array of strings
        if (s == NULL)
        {
            printf("An error has occutted");
            return pokebank;
        }

        s = load2arr(s, buff, *lastindex, pokebank);
        if (s == NULL)
        {
            printf("cleaning up space\n");
            free(s);
            continue;
        }
        temp = Add_pokeslot(pokebank, lastindex);
        if (temp == NULL)
        {
            printf("ERROR\n");
            return NULL;
        }
        pokebank = temp;
        pokebank[*lastindex].number = s[NUMBR];
        pokebank[*lastindex].name = s[NAME];
        pokebank[*lastindex].type1 = s[TYPE1];
        pokebank[*lastindex].type2 = s[TYPE2];
    }

    fclose(import);
    return pokebank;
}

void print_2_export(FILE *export, pokemon *organizer, int last_index)
{
    for (int i = 0; i < last_index + 1; i++)
    {
        fprintf(export, "%-3d|| \t\t|%-5s \t|%-10s \t|%-10s \t|%-10s|\n", i + 1, organizer[i].number, organizer[i].name, organizer[i].type1, organizer[i].type2);
    }
}

void load2organizer(pokemon *pokebank, pokemon *organizer, int last_index)
{
    for (int i = 0; i < last_index + 1; i++)
    {
        organizer[i] = pokebank[i];
    }
}

//----------------------------exporting to files----------------------------//

void export_type(pokemon *pokebank, int last_index)
{

    FILE *export;
    char buff[BUFSIZE];
    printf("Please enter file name: ");
    fgets(buff, BUFSIZE, stdin);
    REMOVE_ENTER(buff[strlen(buff) - 1]);
    export = fopen(buff, "a");
    fprintf(export, "\t\t---============|%s|============---\n", buff);

    printf("What type would you like to export? ");
    fscanf(stdin, "%s", buff);
    int count = 0;
    for (int i = 0; i < last_index + 1; i++)
    {
        if (!strcmp(pokebank[i].type1, buff) || !strcmp(pokebank[i].type2, buff))
        {
            fprintf(export, "%d.\t\t|%s|\t%s\t%s\t%s\n", ++count, pokebank[i].number, pokebank[i].name, pokebank[i].type1, pokebank[i].type2);
        }
    }
    fclose(export);
}

void export_alphabet(pokemon *pokebank, int last_index)
{
    FILE *export;
    int choice = -1;
    char buff[BUFSIZE];
    char *columns[4] = {"number", "name", "type1", "type2"};
    pokemon *organizer;
    organizer = (pokemon *)malloc((last_index + 1) * sizeof(pokemon)); // remember to delete me after use
    if (organizer == NULL)
    {
        printf("An error has occurred\n");
        return;
    }

    printf("Please enter by which column you wish to order: ");
    fscanf(stdin, "%s", &buff);
    for (int i = 0; i <= TYPE2; i++)
    {
        if (!strcmp(columns[i], buff))
        {
            choice = i;
            break;
        }
    }
    if (choice == -1)
    {
        printf("\nNo such column\n");
        return;
    }
    else
    {
        export = fopen(buff, "a");
        fprintf(export, "\t\t\t\t\t---=====Orderd by %s====---\n\n\n", buff);
        fprintf(export, "            |%-5s |%-10s \t|%-10s |%-10s| \n", "Number", "Name", "Type1", "Type2");
        fprintf(export, "================================================================\n");
        printf("\nOpening file\n");
    }

    switch (choice)
    {
    case NUMBR:
    {
        print_2_export(export, pokebank, last_index);
        // fclose(export);
        break;
    }
    case NAME:
    {
        load2organizer(pokebank, organizer, last_index);
        int i;
        int j;
        pokemon *temp = (pokemon *)malloc(sizeof(pokemon));
        if (temp == NULL)
            return;
        for (i = 0; i < last_index + 1; i++)
        {
            for (j = i; j < last_index + 1; j++)
            {
                if (strcmp(organizer[i].name, organizer[j].name) > 0)
                {
                    *temp = organizer[i];
                    organizer[i] = organizer[j];
                    organizer[j] = *temp;
                }
            }
        }
        // freebank(temp,0);
        print_2_export(export, organizer, last_index);
        // fclose(export);
        break;
    }
    case TYPE1:
    {

        load2organizer(pokebank, organizer, last_index);
        int i;
        int j;
        pokemon *temp = (pokemon *)malloc(sizeof(pokemon));
        if (temp == NULL)
            return;
        for (i = 0; i < last_index + 1; i++)
        {
            for (j = i; j < last_index + 1; j++)
            {
                if (strcmp(organizer[i].type1, organizer[j].type1) > 0)
                {
                    *temp = organizer[i];
                    organizer[i] = organizer[j];
                    organizer[j] = *temp;
                }
            }
        }
        // free(temp);
        print_2_export(export, organizer, last_index);
        // fclose(export);
        break;
    }
    case TYPE2:
    {
        load2organizer(pokebank, organizer, last_index);
        int i;
        int j;
        pokemon *temp = (pokemon *)malloc(sizeof(pokemon));
        if (temp == NULL)
            return;
        for (i = 0; i < last_index + 1; i++)
        {
            for (j = i; j < last_index + 1; j++)
            {
                if (strcmp(organizer[i].type2, organizer[j].type2) > 0)
                {
                    *temp = organizer[i];
                    organizer[i] = organizer[j];
                    organizer[j] = *temp;
                }
            }
        }
        // freebank(temp,0);
        print_2_export(export, organizer, last_index);
        // fclose(export);
        break;
    }
    default:
    {

        // free(organizer);
        break;
    }
    }
    fclose(export);

    // freebank(organizer, last_index);
}

//----------------------------printing functions----------------------------//

void print_pokebank(pokemon *bank, int last_index)
{
    for (int j = 0; j <= last_index; j++)
    {

        printf("\n%s ", bank[j].number);
        printf("%s ", bank[j].name);
        printf("%s ", bank[j].type1);
        if (bank[j].type2 != NULL)
        {
            printf("%s ", bank[j].type2);
        }
    }
}

void print_held(pokemon *pokemonsHeldByTheTrainer)
{
    printf("Pokemons held by trainer:\nID:          #           NAME:           type1:          type2:\n");
    for (int i = 0; i < MAXHELDBYTRAINER; ++i)
    {
        printf("%d          ", pokemonsHeldByTheTrainer[i].ID);
        printf("%s          ", pokemonsHeldByTheTrainer[i].number);
        printf("%s          ", pokemonsHeldByTheTrainer[i].name);
        printf("%s          ", pokemonsHeldByTheTrainer[i].type1);
        printf("%s          ", pokemonsHeldByTheTrainer[i].type2);
        printf("\n");
    }
}

void print_oak(pokemon *pokmonsInBank, int last_oak)
{
    printf("Pokemons at Proffesor Oak. :\nID:          #           NAME:           type1:          type2:\n");
    for (int i = 0; i < last_oak + 1; ++i)
    {
        printf("%d          ", pokmonsInBank[i].ID);
        printf("%s          ", pokmonsInBank[i].number);
        printf("%s          ", pokmonsInBank[i].name);
        printf("%s          ", pokmonsInBank[i].type1);
        printf("%s          ", pokmonsInBank[i].type2);
        printf("\n");
    }
}

int print_by_type(char *type, pokemon *pokebank, int lastindex)
{
    int count = 0;
    int i = 0;
    while (i <= lastindex + 1)
    {

        if (!strcmp(pokebank[i].type1, type) || !strcmp(pokebank[i].type2, type))
        {
            printf("%d.     %s %s %s %s\n", count++, pokebank[i].number, pokebank[i].name, pokebank[i].type1, pokebank[i].type2);
        }

        i++;
    }
    if (!count)
    {
        printf("couldn't find the type you were looking for\n");
    }
    return count;
}

//----------------------------mrmory functions----------------------------//

pokemon *Add_pokeslot(pokemon *pokebank, int *lastindex)
{
    pokemon *temp;
    if (pokebank == NULL)
    {
        pokebank = (pokemon *)malloc(sizeof(pokemon));
    }
    else
    {
        temp = (pokemon *)realloc(pokebank, (++(*lastindex) + 1) * sizeof(pokemon));
        if (temp == NULL)
        {
            printf("An error has occurred");
            return NULL;
        }
        pokebank = temp; // realloc was successful
    }
    return pokebank;
}

pokemon *remove_pokeslot(pokemon *pokebank, int *lastindex)
{
    printf("enter\n");
    pokemon *temp;
    temp = (pokemon *)realloc(pokebank, (--(*lastindex)) * sizeof(pokemon));
    if (temp == NULL)
    {
        printf("An error has occurred");
        return NULL;
    }
    pokebank = temp; // realloc was successful
}

int malloc_check(void *ptr)
{
    if (ptr == NULL)
    {
        printf("An error has occurred!\n");
        return FALSE;
    }
    return TRUE;
}

void freebank(pokemon *bank, int last_index)
{
    for (int i = 0; i < last_index + 1; i++)
    {
        free(bank[i].number);
        free(bank[i].name);
        free(bank[i].type1);
        free(bank[i].type2);
    }
    free(bank);
}