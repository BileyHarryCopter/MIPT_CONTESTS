#include <stdio.h>
#include <assert.h>
int majority_element(const int parr[], int len);
int check (char * parr, int me);
int main ()
{
    int * Data;
    int N = 7;
    Data = (int *) calloc (100, sizeof(int));
    for (int i = 0; i < N; i ++)
        scanf("%d", &Data[i]);
    int ME = majority_element(Data, N);
    printf("ME = %d", ME);
    free(Data);
    return 0;
}

int majority_element(const int parr[], int len)
{
    int me1, me2;
    int rlen;
    int i = 0, j = 0;
    int A1[10000], A2[10000];
//    for (i = 0; i < len; i ++)
//       printf("%d ", parr[i]);
//    printf("\n");


    if (len == 2)
    {
        if (parr[0] == parr[1])
            return parr[0];
        if (parr[1] == -1)
            return -1   ;
        return -1;
    }
    rlen = len/2 + len%2;
    for (i = 0; i < len/2; i++)
    {
        A1[i] = parr[i];
    }
    for (j = 0; i < len; j++)
    {
        A2[j] = parr[i];
        i++;
    }
    j = 0;
    i = 0;
    //============================================================
    me1 = majority_element(A1, rlen);
    me2 = majority_element(A2, rlen);
//    printf("me1 = %d, me2 = %d\n", me1, me2);
    if (me1 == me2)
        return me1;
    if (me1 == -1)
        return me2;
    if (me2 == -1)
        return me1;
    return -1;
}

int check (char * parr, int me, int len)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
        if (parr[i] == me)
            cnt++;
    if (cnt > len/2)
        return 1;
    return 0;
}
