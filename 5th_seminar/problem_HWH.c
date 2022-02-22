#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>


#define SIZE 1000
#define SIZELEN 20


typedef struct node_t   {
    char            *str;
    struct node_t  *next;
} node_t;

typedef struct hashmap  {
    node_t       **array;
    unsigned        size;
} hashmap;

typedef struct find_str {
    char * str;
    unsigned coin;
} find_str;


char * str_ctor (char symb);
int istrcmp (char * str1, const char * str2);
void fill_strings (find_str *strings, hashmap *hshmp, unsigned find_nmb);


void print_hash (hashmap hshmp);
unsigned hash_calc (const char *str);
void coin_print (find_str *strings, unsigned find_nmb);
void hashmap_ctor (hashmap *hshmp, unsigned len_buff);
int hashmap_insrt (hashmap *hshmp, unsigned key, char *str);
unsigned hashmap_find_coin (hashmap *hshmp, unsigned key, const char * str);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    unsigned  find_nmb;
    unsigned  len_buff;
    unsigned  numb_str;
    hashmap      hshmp;
    find_str  *strings;

    assert (scanf ("%d %d", &find_nmb, &len_buff) == 2);

    hashmap_ctor (&hshmp, len_buff);

    scanf ("%u", &numb_str);

    assert (strings == NULL);

    strings = (find_str*) calloc (find_nmb, sizeof (find_str));

    //  print_hash (hshmp);

    fill_strings (strings, &hshmp, find_nmb);

    coin_print (strings, find_nmb);

    free (strings);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
unsigned hash_calc (const char *str)
{
    unsigned hash = 5381;
    while (*str != '\0')
    {
        hash = ((hash << 5) + hash) + *str;
        str++;
    }
    return hash % SIZE;
}

void hashmap_ctor (hashmap *hshmp, unsigned len_buff)
{
    char     symb = 0;
    char     *str = 0;
    unsigned   ip = 0;
    unsigned  key = 0;

    hshmp->size   = SIZE;
    hshmp->array  = (node_t **) calloc (SIZE, sizeof (node_t *));

    for (ip = 0; ip < SIZE; ip++)
    {
        hshmp->array[ip] = (node_t *) calloc (1, sizeof (node_t));
    }

    symb = getchar ();

    for (ip = 1; ip < len_buff; ip++)
    {
        symb = getchar ();
        if (isalpha (symb) != 0)
        {
            str = str_ctor (symb);
            ip += strlen (str);
            key = hash_calc (str);
            hashmap_insrt (hshmp, key, str);
            free (str);
        }
    }
}

int hashmap_insrt (hashmap *hshmp, unsigned key, char *str)
{
    node_t  *lst = (node_t *) calloc (1, sizeof (node_t));
    lst->str     = (char *) calloc (SIZELEN, sizeof (char));
    memcpy (lst->str, str, strlen(str));

    if (hshmp->array[key]->next == NULL)
    {
        hshmp->array[key]->next = lst;
        hshmp->array[key]->next->str = lst->str;
        lst->next = NULL;
    }
    else
    {
        lst->next = hshmp->array[key]->next;
        hshmp->array[key]->next = lst;
        hshmp->array[key]->next->str = lst->str;
    }
    return 0;
}

unsigned hashmap_find_coin (hashmap *hshmp, unsigned key, const char * str)
{
    unsigned coin = 0;
    node_t *top;
    top = hshmp->array[key]->next;

    if (top == NULL)
    {
        return coin;
    }

    while (top->next != NULL)
    {
        if (istrcmp (top->str, str) == 0)
        {
            coin++;
        }
        top = top->next;
    }
    if (istrcmp (top->str, str) == 0)
    {
        coin++;
    }
    return coin;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
char * str_ctor (char symb)
{
    short length = 0;
    char * str = (char *) calloc (SIZELEN, sizeof (char));

    while (isalpha (symb) != 0)
    {
        *(str + length) = symb;
        length++;
        symb = getchar();
    }

    return str;
}

int istrcmp (char * str1, const char * str2)
{
    while (isalpha (*str1) != 0)
    {
        if (tolower (*str1) != tolower (*str2))
        {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }
    return (*str1 == ' ' || *str1 == '\t' || *str1 == '\n' || *str1 == '\0') ? 0 : -1;
}

void fill_strings (find_str *strings, hashmap *hshmp, unsigned find_nmb)
{
    unsigned pos  = 0;
    char symb     = 0;
    unsigned key  = 0;

    symb = getchar ();

    for (pos = 0; pos < find_nmb; pos++)
    {
        symb = getchar ();
        strings[pos].str   = str_ctor (symb);
        key                = hash_calc (strings[pos].str);
        strings[pos].coin  = hashmap_find_coin (hshmp, key, strings[pos].str);
    }
}

void coin_print (find_str *strings, unsigned find_nmb)
{
    unsigned pos;
    for (pos = 0; pos < find_nmb; pos++)
    {
        printf ("%u ", strings[pos].coin);
    }
    printf ("\n");
}
