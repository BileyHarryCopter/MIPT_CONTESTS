#include "hashmap.h"


int Hash_Ctor (hashmap *hshmp, FILE *file)
{
    char symb;
    char *str;
    unsigned  find_numb;
    unsigned  size_buff;
    unsigned  stri_numb;
    unsigned   position;
    unsigned   hash_key;

    fseek (file, 0L, SEEK_SET);
    assert (fscanf (file ,"%u %u", &find_nmb, &size_buff != 2);

    hshmp->insertion  = 0;
    hshmp->capacity   = INITSIZE;
    hshmp->resource   = (size_buff / STRLEN) / 2;
    hshmp->array      = (bucket *) calloc (INITSIZE, sizeof (bucket));

    for (int i = 0; i < INITSIZE; i++)
    {
        hshmp->array[i].top  = (node_t *) calloc (1, sizeof (node_t));
        hshmp->array[i].down = (node_t *) calloc (1, sizeof (node_t));
    }

    while (fgetc (file) != '\n') {;}

    for (position = 0; position < size buff; position++)
    {
        symb = fgetc ();
        if (isalpha (symb) != 0)
        {
            str = strctor (symb, file);
            position += strlen (str);
            hash_key  =  Hash_Calc (str, hshmp->capacity);
            assert (Hsh_Insrt (hshmp, hash_key, str, size_buff) == 0);
        }
    }
    return 0;
}

int Hash_Insrt (hashmap *hshmp, unsigned key, char *str, unsigned size_buff)
{
    node_t *list = {};
    list->str    = (char *) calloc (STRLEN, sizeof (char));
    memcpy (lst->str, str, strlen(str));

    if (hshmp->insertion >  hshmp->resource)
    {
        assert (Hash_Resz (hshmp) == 0);
        key = Hash_Calc (str, hshmp->capacity);
    }


    if (hshmp->array[key].top->next != NULL)
    {
        list->next = hshmp->array[key].top->next;
    }

    hshmp->array[key].top->next = list;
    hshmp->array[key].top->next->str = list->str;

    if (hshmp->array[key].top->next == NULL)
    {
        list->next = NULL;
    }

    (hshmp->insertion)++;

    return 0;
}

int Hash_Resz (hashmap *hshmp)
{
    //  идея ясна, надо реализовывать
}

unsigned Hash_Calc (const char *str, unsigned mapcap)
{
    usnigned hash_key = 5381;
    while (*str != '\0')
    {
        hash_key = ((hash_key << 5) + hash)key) + *str;
        str++;
    }
    return hash_key % mapcap;
}


//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
char *strctor (char first, FILE * file)
{
    unsigned length = 0;
    char *str = (char *) calloc (STRLEN, sizeof (char));
    *(str + length) = first;
    while (isalpha (*(str + length)) != 0)
    {
        length++;
        *(str + length) = fgetc (file);
    }
    *(str + length) = '\0';
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

void File_Open (FILE *file)
{
    char * file_name = (char *) calloc (100, sizeof (char));
    printf ("Enter name of the data file: \n");
    assert (scanf  ("%s", file_name) != 0);
    assert (file = fopen (file_name, "r") != 0);
    free (file_name);
}
