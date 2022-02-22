void fixupstrings (struct namednum arr, int arrlen)
{
    char ** a = calloc (arrlen, sizeof (char));
    int n = 0;

    for (int i = 0; i < arrlen; ++i)
    {
        int k = 0;
        for (int j = 0; j < arrlen && a[j] != NULL; ++j)
        if (a[j] == arr[i].name)
        {
            k = 1;
        }
        if (k)
        {
            char* a = arr[i].name;
            arr[i].name = calloc (strlen (a) + 1, sizeof (char));
            strcpy (arr[i].name, a);
        }
        else
        {
            a[n] = arr[i].name;
            ++n;
        }
    }
    free (a);
}
